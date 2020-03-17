//
// Created by Morteza Ahmadi on 2020-01-22.
//

#include "Token.h"
#include "TokenType.h"
#include <iostream>
#include <unordered_map>
#include <utility>

Token::Token(TokenType type, int lineno, std::string value) {
    this->type = type;
    this->lineno = lineno;
    this->value = std::move(value);
}

TokenType Token::getType() { return this->type; }

int Token::getLineno() { return this->lineno; }

std::string Token::getValue() { return this->value; }

std::string Token::getTypeString() { return reverseTokenTypeMap[type]; }

int Token::getPosition() { return position; }

void Token::setPosition(int &pos) {
    this->position = pos;
}

std::unordered_map<std::string, TokenType> TokenTypeMap = {
        {"id",         TokenType::Id},
        {"intnum",     TokenType::Integer},
        {"floatnum",   TokenType::Float},
        {"eq",         TokenType::Eq},
        {"noteq",      TokenType::NotEq},
        {"less",       TokenType::Lt},
        {"greater",    TokenType::Gt},
        {"lesseq",     TokenType::LEq},
        {"greatereq",  TokenType::GEq},
        {"plus",       TokenType::Plus},
        {"minus",      TokenType::Minus},
        {"mult",       TokenType::Mult},
        {"div",        TokenType::Div},
        {"equal",      TokenType::Asgn},
        {"lpar",       TokenType::OpenPr},
        {"rpar",       TokenType::ClosePr},
        {"lcurbr",     TokenType::OpenCbr},
        {"rcurbr",     TokenType::CloseCbr},
        {"lsqbr",      TokenType::OpenSqbr},
        {"rsqbr",      TokenType::CloseSqbr},
        {"semi",       TokenType::Semi},
        {"comma",      TokenType::Comma},
        {"dot",        TokenType::Dot},
        {"colon",      TokenType::Colon},
        {"coloncolon", TokenType::DblColon},
        {"InlineCmt",  TokenType::InlineCmt},
        {"BlockCmt",   TokenType::BlockCmt},
        {"if",         TokenType::If},
        {"then",       TokenType::Then},
        {"else",       TokenType::Else},
        {"integer",    TokenType::__Integer},
        {"float",      TokenType::__Float},
        {"while",      TokenType::While},
        {"class",      TokenType::Class},
        {"do",         TokenType::Do},
        {"end",        TokenType::End},
        {"public",     TokenType::Public},
        {"private",    TokenType::Private},
        {"or",         TokenType::Or},
        {"and",        TokenType::And},
        {"not",        TokenType::Not},
        {"read",       TokenType::Read},
        {"write",      TokenType::Write},
        {"return",     TokenType::Return},
        {"main",       TokenType::Main},
        {"inherits",   TokenType::Inherits},
        {"local",      TokenType::Local},
        {"error",      TokenType::Error},
        {"void",       TokenType::Void},
};


void Token::reverseMap(std::unordered_map<std::string, TokenType> &map) {
    for (auto &element: map) {
        reverseTokenTypeMap[element.second] = element.first;
    }
}

std::unordered_map<std::string, TokenType> &Token::getTokenTypeMap() {
    return TokenTypeMap;
}

std::unordered_map<TokenType, std::string> &Token::getReverseTokenTypeMap() {
    reverseMap(TokenTypeMap);
    return reverseTokenTypeMap;
}

std::ostream &operator<<(std::ostream &os, Token &t) {
    os << "[" << t.getReverseTokenTypeMap()[t.getType()] << ", " << t.getValue() << ", " << t.getLineno() << "]";
    return os;
}
