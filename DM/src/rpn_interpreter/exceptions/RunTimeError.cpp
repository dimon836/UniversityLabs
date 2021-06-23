//
// Created by Dima Halych on 20.06.2021.
//

#include "RunTimeError.h"


RunTimeError::RunTimeError( const std::string& message ) :
	_message(std::move("RunTimeError: " + message)) {}

const char* RunTimeError::what() const noexcept {
	return _message.c_str();
}