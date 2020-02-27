//
// Created by Morteza Ahmadi on 2020-02-11.
//

#ifndef SKY_PARSER_H
#define SKY_PARSER_H

#include <string>
#include <unordered_set>
#include "Grammar.h"
#include "../Lexer/Lexer.h"
#include "AST/ASTBuilder.h"
#include "AST/Visualizer.h"

class Parser {
public:
    Parser(Lexer*);
    ~Parser();
    bool parse(std::string, bool isOnPanicMode = false);
    ASTBuilder* AST_Builder;


private:
    Lexer* lexer;
    Grammar* grammar;
    Token* currentToken;

    void next();
    void printError(Rule&);
    void panic(std::string&);

    bool shouldTakeNext(std::string&);
    bool isKeyword(std::string&);

};

const std::unordered_set<std::string> KEYWORDS = {
        "id",
        "intnum",
        "floatnum",
        "eq",
        "noteq",
        "less",
        "greater",
        "lesseq",
        "greatereq",
        "plus",
        "minus",
        "mult",
        "div",
        "equal",
        "if",
        "then",
        "else",
        "integer",
        "float",
        "while",
        "class",
        "public",
        "private",
        "or",
        "and",
        "not",
        "read",
        "write",
        "return",
        "main",
        "inherits",
        "local",
        "void",
};

#endif //SKY_PARSER_H
