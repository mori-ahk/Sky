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

namespace Syntax {
    class Parser {
    public:
        explicit Parser(Lexer *);

        ~Parser();

        bool parse(std::string, bool isOnPanicMode = false);

        AST::ASTBuilder *AST_Builder;

    private:
        Lexer *lexer;
        Language::Grammar *grammar;
        Token *currentToken;

        void next();

        void printError(Language::Rule &);

        void panic(std::string &);

        bool shouldTakeNext(std::string &);

        static bool isKeyword(std::string &);
    };
}
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
        "void",
};

#endif //SKY_PARSER_H
