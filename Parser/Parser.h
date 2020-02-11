//
// Created by Morteza Ahmadi on 2020-02-11.
//

#ifndef SKY_PARSER_H
#define SKY_PARSER_H

#include "Grammar.h"
#include "../Lexer/Token.h"
class Parser {
public:
    Parser();
    ~Parser();

    void parse();

private:
    Token* token;
    Grammar* grammar;
    void nextToken();
};


#endif //SKY_PARSER_H
