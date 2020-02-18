//
// Created by Morteza Ahmadi on 2020-01-22.
//

#ifndef SKY_TOKEN_H
#define SKY_TOKEN_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include "TokenType.h"


class Token {
public:

    Token(TokenType, int, std::string);

    TokenType getType();
    int getLineno();
    std::string getValue();
    int getPosition();
    void setPosition(int&);
    std::unordered_map<std::string, TokenType>& getTokenTypeMap();
    std::unordered_map<TokenType, std::string>& getReverseTokenTypeMap();
    friend std::ostream& operator<<(std::ostream&, Token&);
private:
    void reverseMap(std::unordered_map<std::string, TokenType>&);
    std::unordered_map<TokenType, std::string> reverseTokenTypeMap;
    TokenType type;
    int lineno;
    std::string value;
    int position;
};


#endif //SKY_TOKEN_H
