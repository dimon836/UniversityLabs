//
// Created by Dima Halych on 18.06.2021.
//

#include "JFToken.h"


JFToken::JFToken()
	: Token(Token::Keyword, "JF") {}

std::string JFToken::toString() {
	return Token::toString() + "(" + std::to_string(this->jumpToIdx) + ")";
}
