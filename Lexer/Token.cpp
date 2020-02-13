//
// Created by Morteza Ahmadi on 2020-01-22.
//

#include "Token.h"
#include "TokenType.h"
#include <iostream>
#include <string>

Token::Token(TokenType type, int lineno, std::string value) {
    this->type = type;
    this->lineno = lineno;
    this->value = value;
}

TokenType Token::getType() { return this->type; }

int Token::getLineno() { return this->lineno; }

std::string Token::getValue() { return this->value; }

std::unordered_map<std::string, TokenType> TokenTypeMap = {
        {"Id", TokenType::Id},
        {"Integer",TokenType::Integer},
        {"Float",TokenType::Float},
        {"Eq",TokenType::Eq},
        {"NotEq",TokenType::NotEq},
        {"Lt",TokenType::Lt},
        {"Gt",TokenType::Gt},
        {"LEq",TokenType::LEq},
        {"GEq",TokenType::GEq},
        {"Plus",TokenType::Plus},
        {"Minus",TokenType::Minus},
        {"Mult",TokenType::Mult},
        {"Div",TokenType::Div},
        {"Asgn",TokenType::Asgn},
        {"OpenPr",TokenType::OpenPr},
        {"ClosePr",TokenType::ClosePr},
        {"OpenCbr",TokenType::OpenCbr},
        {"CloseCbr",TokenType::CloseCbr},
        {"OpenSqbr",TokenType::OpenSqbr},
        {"CloseSqbr",TokenType::CloseSqbr},
        {"Semi",TokenType::Semi},
        {"Comma",TokenType::Comma},
        {"Dot",TokenType::Dot},
        {"Colon",TokenType::Colon},
        {"DblColon",TokenType::DblColon},
        {"InlineCmt",TokenType::InlineCmt},
        {"BlockCmt",TokenType::BlockCmt},
        {"If",TokenType::If},
        {"Then",TokenType::Then},
        {"Else",TokenType::Else},
        {"__Integer",TokenType::__Integer},
        {"__Float",TokenType::__Float},
        {"While",TokenType::While},
        {"Class",TokenType::Class},
        {"Do",TokenType::Do},
        {"End",TokenType::End},
        {"Public",TokenType::Public},
        {"Private",TokenType::Private},
        {"Or",TokenType::Or},
        {"And",TokenType::And},
        {"Not",TokenType::Not},
        {"Read",TokenType::Read},
        {"Write",TokenType::Write},
        {"Return",TokenType::Return},
        {"Main",TokenType::Main},
        {"Inherits",TokenType::Inherits},
        {"Local",TokenType::Local},
        {"Error",TokenType::Error},
        {"Void",TokenType::Void},
};

std::unordered_map<std::string, TokenType>& Token::getTokenTypeMap() {
    return TokenTypeMap;
}

std::ostream& operator<<(std::ostream& os, Token& t) {
    os << "[" << TokenTypeMap[t.getType()] << ", " << t.getValue() << ", " << t.getLineno() << "]";
    return os;
}
