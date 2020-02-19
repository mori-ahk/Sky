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

class Parser {
public:
    Parser(Lexer*);
    ~Parser();
    bool parse(std::string, bool isOnPanicMode = false);

private:
    Lexer* lexer;
    Grammar* grammar;
    Token* currentToken;
    ASTBuilder* ASTBuilder;

    void next();
    void printError(Rule&);
    void panic(std::string&);

    bool shouldTakeNext(std::string&);
    bool isUseless(std::string&);
    bool isKeyword(std::string&);

};

const std::unordered_set<std::string> USELESS = {
        "lpar",
        "rpar",
        "lcurbr",
        "rcurbr",
        "lsqbr",
        "rsqbr",
        "semi",
        "comma",
        "dot",
        "colon",
        "coloncolon",
};


const std::unordered_set<std::string> KEYWORDS = {
        "if",
        "then",
        "else",
        "integer",
        "float",
        "while",
        "class",
        "do",
        "end",
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
}
#endif //SKY_PARSER_H
