//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Compiler.h"

#include <utility>


Compiler::Compiler(std::string filePath) {
    this->lexer = new Lexer();
    lexer->lex(std::move(filePath));
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
    AST::ASTNode *root = parser->AST_Builder->getRoot();
    symTabGenerator = new STGV(root);

    for (const auto &c : symTabGenerator->symbolTable->classes)
        std::cout << *(c.second) << std::endl;

    for (const auto &e : symTabGenerator->getErrors()) {
        std::cerr << e << std::endl;
    }

    if (!symTabGenerator->getErrors().empty()) return;

    typeChecker = new TCV(root, symTabGenerator);

    for (const auto &e : typeChecker->getErrors()) {
        std::cerr << e << std::endl;
    }
}