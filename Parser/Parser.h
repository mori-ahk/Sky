//
// Created by Morteza Ahmadi on 2020-02-11.
//

#ifndef SKY_PARSER_H
#define SKY_PARSER_H

#include <string>
#include "Grammar.h"
#include "../Lexer/Token.h"
class Parser {
public:
    Parser();
    ~Parser();

    void parse(Token*, std::string);

private:
    Grammar* grammar;
};


#endif //SKY_PARSER_H
