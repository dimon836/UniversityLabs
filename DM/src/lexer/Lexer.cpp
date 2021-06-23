//
// Created by Dima Halych on 18.06.2021.
//

#include <istream>
#include <iostream>
#include <sstream>
#include <utility>
#include <iomanip>
#include <memory>
#include "Lexer.h"
#include "BoolConstToken.h"
#include "IntConstToken.h"
#include "RealConstToken.h"
#include "../logger.h"
#include "IdentifierToken.h"


using ClassOfChar = Lexer::ClassOfChar;

const std::map<ClassOfChar, std::string> Lexer::charClasses = {
	{ Letter, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" },
	{ Digit, "0123456789" },
	{ Whitespace, " \t" },
	{ Newline, "\r\n" },
	{ Dot, "." },
	{ Semicolon, ";" },
	{ Parenthesis, "{}()" },
	{ Operators, "+-!=*/<>&|" },
	{ Comma, "," },
};

const std::map<std::pair<unsigned int, ClassOfChar>, unsigned int> Lexer::stateTransitionFn = {
	// Identifiers, Keywords or BoolConsts
	{{ 0, Letter }, 1 },
	{{ 1, Letter }, 1 },
	{{ 1, Digit }, 1 },
	{{ 1, Other }, 2 },

	// UnsignedReal
	{{ 0, Digit }, 3 },
	{{ 3, Digit }, 3 },
	// if UnsignedInt
	{{ 3, Other }, 8 },
	{{ 3, Dot }, 4 },
	{{ 4, Digit }, 4 },
	{{ 4, Other }, 5 },
	{{ 0, Dot }, 6 },
	{{ 6, Digit }, 4 },

	// Whitespace
	{{ 0, Whitespace }, 0 },

	// Comma
	{{ 0, Comma }, 14 },

	// NewLine
	{{ 0, Newline }, 9 },
	{{ 9, Newline }, 9 },

	// EOF
	{{ 0, FEOF }, 0 },

	// Semicolon
	{{ 0, Semicolon }, 10 },

	// Parenthesis
	{{ 0, Parenthesis }, 11 },

	// Operators
	{{ 0, Operators }, 12 },
	{{ 12, Operators }, 12 },
	{{ 12, Other }, 13 },

	// Unexpected
	{{ 0, Other }, 101 },
};

const std::map<
	unsigned int,
	std::function<void( std::istream& in,
	                    const std::string& lexeme,
	                    char currChar,
	                    unsigned int&
	                    currLine,
	                    Lexer& instance
	)>
> Lexer::finalStateProcessingFunctions = {
	// Identifiers, Keywords or BoolConsts
	{ 2,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    std::shared_ptr<Token> token = Token::getLanguageToken(lexeme);
	    if (token->is(Token::Unexpected)) {
		    // token is not Language-in, its identifier
		    auto it = std::find_if(instance.identifiers.begin(), instance.identifiers
		                                                                 .end(), [lexeme]( auto identifier ) {
			  return identifier->lexeme() == lexeme;
		    });
		    if (it == instance.identifiers.end()) {
			    // not found identifier in table
			    auto identifier = std::make_shared<IdentifierToken>(lexeme, it - instance.identifiers.begin());
			    instance.identifiers.push_back(identifier);
			    token = identifier;
		    }
		    else {
			    token = *it;
		    }

	    }
	    instance.tokens.emplace_back(currLine, token);
	    in.unget();
	  }
	},

	// RealConst
	{ 5,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    if (std::string{ currChar } == charClasses.at(ClassOfChar::Dot)) {
		    // TODO: set next token to Unexpected
		    std::cout << "Invalid suffix on real constant!" << std::endl;
		    instance.isLastLexSuccess = false;
	    }
	    std::shared_ptr<Token> token = std::make_shared<RealConstToken>(lexeme);
	    instance.tokens.emplace_back(currLine, token);
	    in.unget();
	  }
	},

	// IntConst
	{ 8,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    std::shared_ptr<Token> token = std::make_shared<IntConstToken>(lexeme);
	    instance.tokens.emplace_back(currLine, token);
	    in.unget();
	  }
	},

	// Newline
	{ 9,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    currLine++;
	  }
	},

	// Semicolon
	{ 10,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    instance.tokens
	            .emplace_back(currLine, std::make_shared<Token>(Token::Type::Semicolon, std::string{ currChar }));
	  }
	},

	// Parenthesis
	{ 11,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    instance.tokens.emplace_back(currLine, Token::getLanguageToken(std::string{ currChar }));
	  }
	},

	// Operators
	{ 13,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    std::shared_ptr<Token> token = Token::getLanguageToken(lexeme);
	    if (token->is(Token::Unexpected)) {
		    // operator token not found
		    std::cerr.flush();
		    std::cerr << "Unexpected Operator token \"" << lexeme << "\" on line " << currLine << std::endl;
		    std::cerr << "Did you mean \"" << Token::getClosestLanguageToken(lexeme) << "\"?" << std::endl;
		    instance.isLastLexSuccess = false;
	    }
	    instance.tokens.emplace_back(currLine, token);
	    in.unget();
	  }
	},

	// Other junk
	{ 14,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int& currLine, Lexer& instance ) {
	    std::shared_ptr<Token> token = Token::getLanguageToken(std::string{ lexeme + currChar });
	    if (token->is(Token::Unexpected)) {
		    // operator token not found
		    std::cerr.flush();
		    std::cerr << "Unexpected token \"" << lexeme << "\" on line " << currLine << std::endl;
		    std::cerr << "Did you mean \"" << Token::getClosestLanguageToken(lexeme) << "\"?" << std::endl;
		    instance.isLastLexSuccess = false;
	    }
	    instance.tokens.emplace_back(currLine, token);
	  }
	},

	// Error state
	{ 101,
	  []( std::istream& in, const std::string& lexeme, char currChar, unsigned int currLine, Lexer& instance ) {
	    std::cerr.flush();
	    std::cerr << "Unexpected token \"" << lexeme + currChar << "\" at line " << currLine << std::endl;
	    instance.tokens.emplace_back(currLine, std::make_shared<Token>(Token::Type::Unexpected, lexeme + currChar));
	    instance.isLastLexSuccess = false;
	    if (currChar == EOF)
		    std::cout << "Its EOF!" << std::endl;
	  }
	},
};

Lexer::LineToken::LineToken( unsigned int line, std::shared_ptr<Token> token ) : line(line), token(std::move(token)) {}

Lexer::LineToken::LineToken( unsigned int line ) : line(line) {}

Lexer::Lexer() {}

bool Lexer::lex( std::istream& inpStream ) noexcept {
	unsigned int currLine = 1;
	std::stringstream lexeme;
	for (char ch; (ch = inpStream.get());) {
		ClassOfChar charClass = classOfChar(ch);
		log("Lexer: ") << "class = " << charClass;
		log() << " | char = \"" << ch;
		log() << "\" | state = " << this->currState << std::endl;
		try {
			this->currState = stateTransitionFn.at(std::make_pair(this->currState, charClass));
			log("Lexer: ") << "Changed state to: " << this->currState << std::endl;
		}
		catch (std::exception& e) {
			try {
				this->currState = stateTransitionFn.at(std::make_pair(this->currState, Other));
				log("Lexer: ") << "Changed state by Other to: " << this->currState << std::endl;
			}
			catch (...) {
				std::cerr << "No state to go from " << this->currState << std::endl;
				this->isLastLexSuccess = false;
				return false;
			}
		}
		bool isStateFinal = finalStateProcessingFunctions.count(this->currState) > 0;
		if (isStateFinal) {
			// call processing fn
			log("Lexer: ") << "State " << this->currState << " is final, calling processing func" << std::endl;

			finalStateProcessingFunctions.at(this->currState)(inpStream, lexeme.str(), ch, currLine, *this);
			this->currState = initialState;
			lexeme.str(std::string{});
		}
		else if (this->currState == initialState) {
			lexeme.str(std::string{});
		}
		else {
			lexeme.put(ch);
			log("Lexer: ") << "Changed lexeme to: " << lexeme.str() << std::endl;
		}
		if (ch == EOF)
			break;
	}

	return this->isLastLexSuccess;
}

ClassOfChar Lexer::classOfChar( char ch ) {
	if (ch == EOF)
		return FEOF;
	for (int charClassInt = 0; charClassInt < ClassOfChar::Other; charClassInt++) {
		auto cls = static_cast<ClassOfChar>(charClassInt);
		if (charClasses.at(cls).find(ch) != std::string::npos)
			return cls;
	}
	return Other;
}

void Lexer::printTokenTable() {
	for (const auto& lineToken : this->tokens) {
		std::cout << std::setw(3) << lineToken.line << " | " << "type: " << lineToken.token->type()
		          << "\tlexeme: " << lineToken.token->lexeme();
		if (lineToken.token->is(Token::Type::BoolConst)) {
			std::cout << "\tactual: " << *std::static_pointer_cast<BoolConstToken::CTYPE>(lineToken.token->actual());
		}
		else if (lineToken.token->is(Token::Type::RealConst)) {
			std::cout << "\tactual: " << *std::static_pointer_cast<RealConstToken::CTYPE>(lineToken.token->actual());
		}
		else if (lineToken.token->is(Token::Type::IntConst)) {
			std::cout << "\tactual: " << *std::static_pointer_cast<IntConstToken::CTYPE>(lineToken.token->actual());
		}
		else if (lineToken.token->is(Token::Type::Identifier)) {
			std::cout << "\tid: " << std::dynamic_pointer_cast<IdentifierToken>(lineToken.token)->id();
		}
		std::cout << std::endl;
	}
}

const std::vector<Lexer::LineToken>& Lexer::getTokens() const {
	return tokens;
}

const std::vector<std::shared_ptr<IdentifierToken>>& Lexer::getIdentifiers() const {
	return identifiers;
}
