//
// Created by Morteza Ahmadi on 2020-02-11.
//

#ifndef SKY_PARSER_H
#define SKY_PARSER_H

#include <string>
#include "Grammar.h"
#include "../Lexer/Lexer.h"
class Parser {
public:
    Parser(Lexer*);
    ~Parser();

    bool parse(std::string);
private:
    Lexer* lexer;
    Grammar* grammar;
    Rule* currentRule;
    Token* currentToken;
    std::string START = "START";
};


#endif //SKY_PARSER_H
