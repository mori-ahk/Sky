//
// Created by Morteza Ahmadi on 2020-02-11.
//

#ifndef SKY_COMPILER_H
#define SKY_COMPILER_H
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
class Compiler {
public:
    Compiler(std::string);
    ~Compiler();
    void compile();
private:
    Lexer* lexer;
    Parser* parser;
};


#endif //SKY_COMPILER_H
