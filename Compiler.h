//
// Created by Morteza Ahmadi on 2020-02-11.
//

#ifndef SKY_COMPILER_H
#define SKY_COMPILER_H

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Visitors/SymbolTable/STGV.h"
#include "Visitors/TypeChecking/TCV.h"

class Compiler {
public:
    explicit Compiler(std::string);

    ~Compiler();

    void compile();

private:
    Lexer *lexer;
    Syntax::Parser *parser;
    STGV *symTabGenerator;
    TCV *typeChecker;
    std::string filePath;

    void writeSymTab();
    void writeSymTabErrors(const std::vector<std::string> &errors);
    void writeSymTabWarnings(const std::vector<std::string> &warnings);
    void writeTypeCheckingErrors(const std::vector<std::string> &errors);

    std::string extractFileName();
};


#endif //SKY_COMPILER_H
