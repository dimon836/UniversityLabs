//
// Created by Dima Halych on 18.06.2021.
//

#ifndef _LEXER_H_
#define _LEXER_H_

#include <map>
#include <vector>
#include <functional>
#include <memory>
#include "Token.h"
#include "IdentifierToken.h"


class Lexer
{
  public:
	enum ClassOfChar
	{
		Letter,
		Digit,
		Whitespace,
		Newline,
		Dot,
		Semicolon,
		Parenthesis,
		Operators,
		Comma,
		FEOF,
		Other
	};
	static const std::map<ClassOfChar, std::string> charClasses;

	struct LineToken
	{
		std::shared_ptr<Token> token;
		unsigned int line;

		explicit LineToken( unsigned int, std::shared_ptr<Token> token );
		explicit LineToken( unsigned int );
	};

	static const std::map<std::pair<unsigned int, ClassOfChar>, unsigned int> stateTransitionFn;
	static const std::map<
		unsigned int,
		std::function<void( std::istream&, const std::string&, char, unsigned int&, Lexer& )>
	> finalStateProcessingFunctions;

	std::vector<LineToken> tokens;
	std::vector<std::shared_ptr<IdentifierToken>> identifiers;

	bool isLastLexSuccess = true;
	static const unsigned int initialState{ 0 };
	unsigned int currState{ initialState };

  public:
	Lexer();

	bool lex( std::istream& ) noexcept;
	static ClassOfChar classOfChar( char );
	void printTokenTable();

	const std::vector<LineToken>& getTokens() const;
	const std::vector<std::shared_ptr<IdentifierToken>>& getIdentifiers() const;

};

#endif //_LEXER_H_
