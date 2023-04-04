#include <iostream>

#include <cstring>
#include <string>

#include "exception.h"

Exception::Exception(const std::string& message_error) {
	message_error_ = message_error;
}
std::string Exception::what() const {
	return message_error_;
}

LogicError::LogicError(const std::string& message_error) {
	message_error_ = message_error;
}
std::string LogicError::what() const {
	return message_error_;
}
RuntimeError::RuntimeError(const std::string& message_error) {
	message_error_ = message_error;
}
std::string RuntimeError::what() const {
	return message_error_;
}
BadAlloc::BadAlloc(const std::string& message_error) {
	message_error_ = message_error;
}
std::string BadAlloc::what() const {
	return message_error_;
}

InvalidArgument::InvalidArgument(const std::string& message_error) {
	message_error_ = message_error;
}
std::string InvalidArgument::what() const {
	return message_error_;
}
DomainError::DomainError(const std::string& message_error) {
	message_error_ = message_error;
}
std::string DomainError::what() const {
	return message_error_;
}
LengthError::LengthError(const std::string& message_error) {
	message_error_ = message_error;
}
std::string LengthError::what() const {
	return message_error_;
}
OutOfRange::OutOfRange(const std::string& message_error) {
	message_error_ = message_error;
}
std::string OutOfRange::what() const {
	return message_error_;
}

RangeError::RangeError(const std::string& message_error) {
	message_error_ = message_error;
}
std::string RangeError::what() const {
	return message_error_;
}
OverflowError::OverflowError(const std::string& message_error) {
	message_error_ = message_error;
}
std::string OverflowError::what() const {
	return message_error_;
}
UnderflowError::UnderflowError(const std::string& message_error) {
	message_error_ = message_error;
}
std::string UnderflowError::what() const {
	return message_error_;
}
