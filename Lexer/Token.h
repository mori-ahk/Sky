//
// Created by Morteza Ahmadi on 2020-01-22.
//

#ifndef SKY_TOKEN_H
#define SKY_TOKEN_H

#include <stdio.h>
#include <string>
#include <iostream>
#include "TokenType.h"


class Token {
public:

    Token(TokenType, int, std::string);

    TokenType getType();
    int getLineno();
    std::string getValue();

    friend std::ostream& operator<<(std::ostream&, Token&);
private:

    TokenType type;
    int lineno;
    std::string value;
};


#endif //SKY_TOKEN_H
