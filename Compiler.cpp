//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Compiler.h"

#include <fstream>

Compiler::Compiler(std::string _filePath) {
    this->filePath = std::move(_filePath);
    this->lexer = new Lexer();
    lexer->lex(filePath);
    this->parser = new Syntax::Parser(lexer);
    this->symTabGenerator = nullptr;
    this->typeChecker = nullptr;
}
std::string Compiler::extractFileName() {
    std::string fileName;

    for (const auto &c : filePath) {
        if (c == '.') break;
        fileName += c;
    }

    return fileName;
}

Compiler::~Compiler() {
    delete lexer;
    delete parser;
    delete symTabGenerator;
    delete typeChecker;
}

void Compiler::writeSymTab() {
    std::string fileName = extractFileName();
    std::ofstream stream(fileName + "_symtab.txt");
    for (const auto &c : symTabGenerator->symbolTable->classes) stream << *c.second << "\n";

    for (const auto &functions : symTabGenerator->symbolTable->freeFunctions) {
        for (const auto &f : functions.second) stream << *f << "\n";
    }

    stream << *(symTabGenerator->symbolTable->main) << "\n";

    stream.close();
}

void Compiler::writeSymTabErrors(const std::vector<std::string> &errors) {
    if (errors.empty()) return;
    std::string fileName = extractFileName();
    std::ofstream stream(fileName + "_symtab_errors.txt");
    stream << "============================ SYMBOL TABLE ERRORS ========================= \n";
    for (const auto & error : errors) stream << error << "\n";

    stream.close();
}

void Compiler::writeSymTabWarnings(const std::vector<std::string> &warnings) {
    if (warnings.empty()) return;
    std::string fileName = extractFileName();
    std::ofstream stream(fileName + "_symtab_warnings.txt");
    stream << "============================ SYMBOL TABLE WARNINGS ========================= \n";
    for (const auto & warning : warnings) stream << warning << "\n";
    stream.close();
}

void Compiler::writeTypeCheckingErrors(const std::vector<std::string> &errors) {
    if (errors.empty()) return;
    std::string fileName = extractFileName();
    std::ofstream stream(fileName + "_typecheck_errors.txt");
    stream << "============================ TYPE CHECKING ERRORS ========================= \n";
    for (const auto & error : errors) stream << error << "\n";
    stream.close();
}

void Compiler::compile() {
    parser->parse("START");
    parser->AST_Builder->visualize();

    AST::ASTNode *root = parser->AST_Builder->getRoot();
    symTabGenerator = new STGV(root);
    writeSymTabErrors(symTabGenerator->getErrors());
    writeSymTabWarnings(symTabGenerator->getWarnings());
    writeSymTab();
    if (!symTabGenerator->getErrors().empty()) return;

    typeChecker = new TCV(root, symTabGenerator);
    writeTypeCheckingErrors(typeChecker->getErrors());

    codeGenerator = new CGV(root, symTabGenerator->symbolTable);
}