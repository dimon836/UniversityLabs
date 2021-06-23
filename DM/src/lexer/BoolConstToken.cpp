//
// Created by Dima Halych on 18.06.2021.
//

#include <iostream>
#include "BoolConstToken.h"
#include "exceptions/LexerError.h"


BoolConstToken::BoolConstToken( const std::string& lexeme )
	: Token(Token::Type::BoolConst, lexeme) {
	if (lexeme == "true") {
		_actual = std::make_shared<CTYPE>(true);
	}
	else if (lexeme == "false") {
		_actual = std::make_shared<CTYPE>(false);
	}
	else {
		this->_type = Unexpected;
		throw LexerError{ "Unexpected BoolConstToken" };
	}
}

BoolConstToken::BoolConstToken( const BoolConstToken::CTYPE& actual ) :
	Token(Token::Type::BoolConst, std::to_string(actual)),
	_actual(std::make_shared<CTYPE>(actual)) {}
