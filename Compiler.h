//
// Created by Morteza Ahmadi on 2020-02-11.
//

#ifndef SKY_COMPILER_H
#define SKY_COMPILER_H

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Visitors/SymbolTable/STGV.h"

class Compiler {
public:
    explicit Compiler(std::string);

    ~Compiler();

    void compile();

private:
    Lexer *lexer;
    Syntax::Parser *parser;
    STGV *symTabGenerator;

};


#endif //SKY_COMPILER_H
