//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Compiler.h"

Compiler::Compiler(std::string filePath) {
    this->lexer = new Lexer();
    lexer->lex(filePath);
    this->parser = new Parser(lexer);
    this->symTabGenerator = nullptr;
}

Compiler::~Compiler() {
    delete lexer;
    delete parser;
}

void Compiler::compile() {
    parser->parse("START");
    parser->AST_Builder->visualize();
//    symTabGenerator = new STGV(parser->AST_Builder->getRoot());

}