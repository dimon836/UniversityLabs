//
// Created by Dima Halych on 18.06.2021.
//

#include "LexerError.h"


LexerError::LexerError( const std::string& message ) :
	_message(std::move("LexerError: " + message)) {}

const char* LexerError::what() const noexcept {
	return _message.c_str();
}