//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Compiler.h"


Compiler::Compiler(std::string filePath) {
    this->lexer = new Lexer();
    lexer->lex(filePath);
    this->parser = new Syntax::Parser(lexer);
    this->symTabGenerator = nullptr;
}

Compiler::~Compiler() {
    delete lexer;
    delete parser;
}

void Compiler::compile() {
    parser->parse("START");
    parser->AST_Builder->visualize();
    symTabGenerator = new STGV(parser->AST_Builder->getRoot());
    for (const auto& c: symTabGenerator->symbolTable->classes) {
        std::cout << *(c.second) << std::endl;
    }

    for (const auto& f : symTabGenerator->symbolTable->freeFunctions) {
        for (const auto& _f : f.second)
            std::cout << *(_f) << std::endl;
    }

    std::cout << *(symTabGenerator->symbolTable->main) << std::endl;

    for (const auto& e : symTabGenerator->detector->getErrors()) {
        std::string p;
        if (e.second == 0) p = "";
        else p += " at line " + std::to_string(e.second);
        std::cerr << e.first << p << std::endl;
    }
}