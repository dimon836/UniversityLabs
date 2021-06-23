//
// Created by Dima Halych on 19.06.2021.
//

#include "Parser.h"
#include "exceptions/SyntaxError.h"
#include <iostream>
#include <iomanip>
#include "../logger.h"
#include "../lexer/JFToken.h"
#include "../lexer/JUMPToken.h"


Parser::Parser() {}

const std::vector<std::string> Parser::_types = { "integer", "real", "bool" };

bool Parser::parse( const std::vector<Lexer::LineToken>& tokens,
                    const std::vector<std::shared_ptr<IdentifierToken>>& identifiers ) {
	this->_currToken = tokens.begin();
	this->_tokens = tokens;
	this->_identifiers = identifiers;
	try {
		return this->parseProgram();
	}
	catch (const SyntaxError& error) {
		std::cerr << error.what() << std::endl;
		if (_currToken != _tokens.end()) {
			std::cerr << "\t\t at " << std::setw(3) << _currToken->line
			          << " | \"" << _currToken->token->lexeme() << "\"" << std::endl;
		}
		return false;
	}
}

bool Parser::parseProgram() {

	parseKeyword("program");
	parseIdentifierById(0);
	parseToken(Token::LeftCurly);
	parseStatementList();
	parseToken(Token::RightCurly);

	return true;
}

bool Parser::parseKeyword( const std::string& keyword ) {
	if (this->_currToken == this->_tokens.end()) {
		throw SyntaxError{ "Unexpected end of program" };
	}

	std::shared_ptr<Token> token = this->_currToken->token;
	if (token->is_not(Token::Keyword) || token->lexeme() != keyword) {
		throw SyntaxError{
			"Expected keyword \"" + keyword + "\", got \"" + token->lexeme() +
			"\" (type " + std::to_string(token->type()) + ") instead."
		};
	}
	++this->_currToken;

	return true;
}

bool Parser::parseIdentifierById( unsigned int id ) {
	if (this->_currToken == this->_tokens.end()) {
		throw SyntaxError{ "Unexpected end of program" };
	}

	std::shared_ptr<Token> token = this->_currToken->token;
	if (token->is_not(Token::Identifier)) {
		throw SyntaxError{ "Expected identifier, got " + std::to_string(token->type()) };
	}
	++this->_currToken;

	return true;
}

bool Parser::parseIdentifier() {
	if (this->_currToken == this->_tokens.end()) {
		throw SyntaxError{ "Unexpected end of program" };
	}

	std::shared_ptr<Token> token = this->_currToken->token;
	if (token->is_not(Token::Identifier)) {
		throw SyntaxError{ "Expected identifier, got " + std::to_string(token->type()) };
	}
	this->postfixTokens.push_back(*_currToken);

	++this->_currToken;

	return true;
}

bool Parser::parseToken( Token::Type type ) {
	if (this->_currToken == this->_tokens.end()) {
		throw SyntaxError{ "Unexpected end of program" };
	}

	std::shared_ptr<Token> token = this->_currToken->token;
	if (token->is_not(type)) {
		throw SyntaxError{ "Expected " + std::to_string(type) + ", got " + std::to_string(token->type()) };
	}
	++this->_currToken;

	return true;
}

bool Parser::parseStatementList() {
	while (parseStatement()) {

	}
	return true;
}

bool Parser::parseStatement() {
	switch (_currToken->token->type()) {
	case Token::Identifier: {
		parseAssign();
		parseToken(Token::Semicolon);
		break;
	}
	case Token::Keyword: {
		// Inp, Out or Initialization
		if (_currToken->token->lexeme() == "write") {
			parseOut();
			parseToken(Token::Semicolon);
		}
		else if (_currToken->token->lexeme() == "read") {
			parseInp();
			parseToken(Token::Semicolon);
		}
		else if (_currToken->token->lexeme() == "if") {
			parseIfStatement();
		}
		else if (_currToken->token->lexeme() == "for") {
			parseForStatement();
		}
		else if (
			_currToken->token->lexeme() == "integer" ||
			_currToken->token->lexeme() == "real" ||
			_currToken->token->lexeme() == "bool"
			) {
			// push init type (int, real, bool)
			parseInitialization();
			parseToken(Token::Semicolon);
		}
		else {
			throw SyntaxError{ "expected \"}\"" };
		}
		break;
	}
	case Token::RightCurly: {
		// end of program
		return false;
	}
	default:
		throw SyntaxError{ "Unknown token in Statement" };
	}
	return true;
}

bool Parser::parseAssign() {
	// Assign
	parseIdentifier();
	parseToken(Token::Assign);
	auto assignToken = std::prev(_currToken);
	parseBoolExpr();
	this->postfixTokens.push_back(*assignToken);
	return true;
}

bool Parser::parseBoolExpr() {
	parseBoolTerm();
	while (_currToken->token->is(Token::Or)) {
		auto parsedToken = *_currToken;
		++_currToken;
		parseBoolTerm();
		this->postfixTokens.emplace_back(parsedToken);
	}
	return true;
}

bool Parser::parseBoolTerm() {
	parseBoolFactor();
	while (_currToken->token->is(Token::And)) {
		auto parsedToken = *_currToken;
		++_currToken;
		parseBoolFactor();
		this->postfixTokens.emplace_back(parsedToken);
	}
	return true;
}

bool Parser::parseBoolFactor() {
	std::shared_ptr<Lexer::LineToken> notToken;
	if (_currToken->token->is(Token::Not)) {
		notToken = std::make_shared<Lexer::LineToken>(*_currToken);
		++_currToken;
		parseBoolFactor();
	}
	if (_currToken->token->is_one_of(
		Token::Identifier, Token::IntConst, Token::RealConst, Token::BoolConst,
		Token::Sub,
		Token::LeftParen, Token::RightParen
	)) {
		parseBoolRelation();
	}
	else {
		throw SyntaxError{ "expected expression" };
	}
	if (notToken) {
		this->postfixTokens.emplace_back(*notToken);
	}
	return true;
}

bool Parser::parseBoolRelation() {
	parseExpression();
	if (_currToken->token->is_one_of(
		Token::LessThan,
		Token::LessOrEqualTo,
		Token::EqualTo,
		Token::NotEqual,
		Token::GreaterOrEqualTo,
		Token::GreaterThan)
		) {
		auto parsedToken = *_currToken;
		++_currToken;
		parseExpression();
		this->postfixTokens.emplace_back(parsedToken);
	}
	return true;
}

bool Parser::parseExpression() {
	// Term
	parseTerm();
	// { AddOp Term }
	while (_currToken->token->is_one_of(Token::Add, Token::Sub)) {
		auto parsedToken = _currToken;
		++_currToken;
		parseTerm();
		this->postfixTokens.push_back(*parsedToken);
	}
	return true;
}

bool Parser::parseTerm() {
	parseFactor();
	while (_currToken->token->is_one_of(Token::Multiply, Token::Division, Token::IntDivision)) {
		auto parsedToken = _currToken;
		++_currToken;
		parseFactor();
		this->postfixTokens.push_back(*parsedToken);
	}
	return true;
}

bool Parser::parseFactor() {
	parseFirstExpr();
	while (_currToken->token->is(Token::Power)) {
		auto parsedToken = _currToken;
		++_currToken;
		parseFactor();
		this->postfixTokens.push_back(*parsedToken);
	}
	return true;
}

bool Parser::parseFirstExpr() {
	unsigned int signLine = -1;
	// [Sign]
	if (_currToken->token->is(Token::Sub)) {
		signLine = _currToken->line;
		++_currToken;
	}
	if (_currToken->token->is_one_of(Token::IntConst, Token::RealConst, Token::BoolConst)) {
		this->postfixTokens.push_back(*_currToken);
		++_currToken;
	}
	else if (_currToken->token->is(Token::Identifier)) {
		parseIdentifier();
	}
	else if (_currToken->token->is(Token::LeftParen)) {
		parseToken(Token::LeftParen);
		parseBoolExpr();
		parseToken(Token::RightParen);
	}
	else {
		throw SyntaxError{ "Expected const, ident or Expression" };
	}
	if (signLine > -1) {
		this->postfixTokens.emplace_back(signLine, std::make_shared<Token>(Token::Type::Sign, "@"));
	}
	return true;
}

bool Parser::parseType() {
	if (std::find(_types.begin(), _types.end(), _currToken->token->lexeme()) == _types.end()) {
		// token is not Type
		throw SyntaxError{ "Expected type in Initialization; got \"" + _currToken->token->lexeme() + "\" instead." };
	}
	++_currToken;
	return true;
}

bool Parser::parseInitialization() {
	parseType();
	auto typeToken = std::prev(_currToken);
	parseIdentDecl(*typeToken);
	while (_currToken->token->is(Token::Comma)) {
		++_currToken;
		parseIdentDecl(*typeToken);
	}
	return true;
}

bool Parser::parseIdentDecl( const Lexer::LineToken& typeToken ) {
	this->postfixTokens.push_back(typeToken);
	parseIdentifier();
	if (_currToken->token->is(Token::Assign)) {
		parseToken(Token::Assign);
		auto assignToken = std::prev(_currToken);
		parseBoolExpr();
		this->postfixTokens.push_back(*assignToken);
	}
	return true;
}

bool Parser::parseInp() {
	parseKeyword("read");
	Lexer::LineToken readToken = *prev(_currToken);
	parseToken(Token::LeftParen);
	parseIdentList(readToken);
	parseToken(Token::RightParen);
	return true;
}

bool Parser::parseOut() {
	parseKeyword("write");
	Lexer::LineToken printToken = *prev(_currToken);
	parseToken(Token::LeftParen);
	parseIdentList(printToken);
	parseToken(Token::RightParen);
	return true;
}

bool Parser::parseIdentList( const Lexer::LineToken& insertToken ) {
	parseBoolExpr();
	this->postfixTokens.emplace_back(insertToken);
	while (_currToken->token->is(Token::Comma)) {
		++_currToken;
		parseBoolExpr();
		this->postfixTokens.emplace_back(insertToken);
	}
	return true;
}

bool Parser::parseDoBlock() {
	if (_currToken->token->is(Token::LeftCurly)) {
		// StatementList
		parseToken(Token::LeftCurly);
		parseStatementList();
		parseToken(Token::RightCurly);
	}
	else {
		// Statement only
		parseStatement();
	}

	return true;
}

bool Parser::parseIfStatement() {
	parseKeyword("if");
	parseToken(Token::LeftParen);
	parseBoolExpr();
	parseToken(Token::RightParen);

	// JF to else (will jump if BoolExpr is false).
	unsigned int jfLine = std::prev(_currToken)->line;
	std::shared_ptr<JFToken> jfToken = std::make_shared<JFToken>();
	this->postfixTokens.emplace_back(jfLine, jfToken);
	parseDoBlock();
	jfToken->jumpToIdx = this->postfixTokens.size() - 1;

	if (_currToken->token->is(Token::Keyword) && _currToken->token->lexeme() == "else") {
		parseKeyword("else");

		std::shared_ptr<JUMPToken> jumpToken = std::make_shared<JUMPToken>();
		// JUMP to else end
		this->postfixTokens.emplace_back(jfLine, jumpToken);
		jfToken->jumpToIdx = this->postfixTokens.size() - 1;

		parseDoBlock();
		jumpToken->jumpToIdx = this->postfixTokens.size() - 1;
	}
	return true;
}

bool Parser::parseForStatement() {
	parseKeyword("for");
	parseToken(Token::LeftParen);

	Lexer::LineToken forIdentifier = *_currToken;

	// [Type] - initialization
	if (_currToken->token->is(Token::Keyword)) {
		forIdentifier = *std::next(_currToken);
		parseInitialization();
	}
	else {
		// just default assign
		parseAssign();
	}
	parseToken(Token::Semicolon);

	// JUMP to the "bool"
	std::shared_ptr<JUMPToken> jumpBool = std::make_shared<JUMPToken>();
	jumpBool->jumpToIdx = this->postfixTokens.size() - 1;

	parseBoolExpr();

	// JF to the "for" end while BoolExpr is not working anymore
	std::shared_ptr<JFToken> jumpOut = std::make_shared<JFToken>();
	this->postfixTokens.emplace_back(std::prev(this->postfixTokens.end())->line, jumpOut);

	// JUMP to the "body"
	std::shared_ptr<JUMPToken> jumpBody = std::make_shared<JUMPToken>();
	this->postfixTokens.emplace_back(std::prev(this->postfixTokens.end())->line, jumpBody);


	parseToken(Token::Semicolon);

	// JUMP to the "increment"
	std::shared_ptr<JUMPToken> jumpIncrement = std::make_shared<JUMPToken>();
	jumpIncrement->jumpToIdx = this->postfixTokens.size() - 1;


	parseAssign();

	this->postfixTokens.emplace_back(std::prev(this->postfixTokens.end())->line, jumpBool);


	parseToken(Token::RightParen);

	jumpBody->jumpToIdx = this->postfixTokens.size() - 1;

	parseDoBlock();

	this->postfixTokens.emplace_back(std::prev(this->postfixTokens.end())->line, jumpIncrement);

	jumpOut->jumpToIdx = this->postfixTokens.size() - 1;
	return true;
}
