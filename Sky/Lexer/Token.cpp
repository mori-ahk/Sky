//
//  Token.cpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#include "Token.hpp"

Token::Token(TokenType type, int lineno, std::string value) {
    this->type = type;
    this->lineno = lineno;
    this->value = value;
}

TokenType Token::getType() { return this->type; }

int Token::getLineno() { return this->lineno; }

std::string Token::getValue() { return this->value; }
