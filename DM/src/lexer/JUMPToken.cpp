//
// Created by Dima Halych on 18.06.2021.
//

#include "JUMPToken.h"


JUMPToken::JUMPToken()
	: Token(Token::Keyword, "JUMP") {}

std::string JUMPToken::toString() {
	return Token::toString() + "(" + std::to_string(this->jumpToIdx) + ")";
}
