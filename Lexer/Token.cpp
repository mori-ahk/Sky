//
// Created by Morteza Ahmadi on 2020-01-22.
//

#include "Token.h"
#include "TokenType.h"
#include <iostream>
#include <unordered_map>
Token::Token(TokenType type, int lineno, std::string value) {
    this->type = type;
    this->lineno = lineno;
    this->value = value;
}

TokenType Token::getType() { return this->type; }

int Token::getLineno() { return this->lineno; }

std::string Token::getValue() { return this->value; }

std::unordered_map<std::string, TokenType> TokenTypeMap = {
        {"id", TokenType::Id},
        {"Integer",TokenType::Integer},
        {"Float",TokenType::Float},
        {"==",TokenType::Eq},
        {"<>",TokenType::NotEq},
        {"<",TokenType::Lt},
        {">",TokenType::Gt},
        {"<=",TokenType::LEq},
        {">=",TokenType::GEq},
        {"+",TokenType::Plus},
        {"-",TokenType::Minus},
        {"*",TokenType::Mult},
        {"/",TokenType::Div},
        {"=",TokenType::Asgn},
        {"(",TokenType::OpenPr},
        {")",TokenType::ClosePr},
        {"{",TokenType::OpenCbr},
        {"}",TokenType::CloseCbr},
        {"[",TokenType::OpenSqbr},
        {"]",TokenType::CloseSqbr},
        {";",TokenType::Semi},
        {",",TokenType::Comma},
        {".",TokenType::Dot},
        {":",TokenType::Colon},
        {"::",TokenType::DblColon},
        {"InlineCmt",TokenType::InlineCmt},
        {"BlockCmt",TokenType::BlockCmt},
        {"if",TokenType::If},
        {"then",TokenType::Then},
        {"else",TokenType::Else},
        {"__Integer",TokenType::__Integer},
        {"__Float",TokenType::__Float},
        {"while",TokenType::While},
        {"class",TokenType::Class},
        {"do",TokenType::Do},
        {"end",TokenType::End},
        {"public",TokenType::Public},
        {"private",TokenType::Private},
        {"or",TokenType::Or},
        {"and",TokenType::And},
        {"not",TokenType::Not},
        {"read",TokenType::Read},
        {"write",TokenType::Write},
        {"return",TokenType::Return},
        {"main",TokenType::Main},
        {"inherits",TokenType::Inherits},
        {"local",TokenType::Local},
        {"error",TokenType::Error},
        {"void",TokenType::Void},
};

std::unordered_map<std::string, TokenType>& Token::getTokenTypeMap() {
    return TokenTypeMap;
}

std::ostream& operator<<(std::ostream& os, Token& t) {
    os << "[" << "TokenTypeMap[t.getType()]" << ", " << t.getValue() << ", " << t.getLineno() << "]";
    return os;
}
