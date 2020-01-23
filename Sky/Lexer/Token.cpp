//
//  Token.cpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#include "Token.hpp"
#include <iostream>

Token::Token(TokenType type, int lineno, std::string value) {
    this->type = type;
    this->lineno = lineno;
    this->value = value;
}

TokenType Token::getType() { return this->type; }

int Token::getLineno() { return this->lineno; }

std::string Token::getValue() { return this->value; }

std::string TokenTypeString[] = {
    "Id", // letter alphanum*
    "Integer", // nonzero digit* | 0
    "Float", // integer fraction [e[+|-] integer]
    "Eq", // ==
    "NotEq", // <>
    "Lt", // <
    "Gt", // >
    "LEq", // <=
    "GEq", // >=
    "Plus", // +
    "Minus", // -
    "Mult", // *
    "Div", // /
    "Asgn", // =
    "OpenPr", // (
    "ClosePr", // )
    "OpenCbr", // {
    "CloseCbr", // }
    "OpenSqbr", // [
    "CloseSqbr", // ]
    "Semi", // ;
    "Comma", // ,
    "Dot", // .
    "Colon", // :
    "DblColon", // ::
    "InlineCmt", // //
    "BlockOpenCmt", // /*
    "BlockCloseCmt", // */
    "If",
    "Then",
    "Else",
    "__Integer",
    "__Float",
    "While",
    "Class",
    "Do",
    "End",
    "Public",
    "Private",
    "Or",
    "And",
    "Not",
    "Read",
    "Write",
    "Return",
    "Main",
    "Inherits",
    "Local",
    "Error",
};


std::ostream& operator<<(std::ostream& os, Token& t) {
    os << "[" <<TokenTypeString[static_cast<int>(t.getType())] << ", " << t.getValue() << ", " << t.getLineno() << "]";
    return os;
}
