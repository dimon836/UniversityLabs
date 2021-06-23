//
// Created by Dima Halych on 19.06.2021.
//

#include "SyntaxError.h"

#include <utility>


SyntaxError::SyntaxError( const std::string& message ) :
	_message(std::move("SyntaxError: " + message)) {}

const char* SyntaxError::what() const noexcept {
	return _message.c_str();
}