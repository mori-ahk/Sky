//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Compiler.h"

Compiler::Compiler() {
    this->lexer = new Lexer();
    this->parser = new Parser();
}

Compiler::~Compiler() {
    delete lexer;
    delete parser;
}

void Compiler::compile(std::string filePath) {
    lexer->lex(filePath);
    auto nextToken = lexer->next();
    while(nextToken != nullptr) {
        parser->parse(nextToken);
        nextToken = lexer->next();
    }
}