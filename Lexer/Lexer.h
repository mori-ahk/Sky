//
// Created by Morteza Ahmadi on 2020-01-22.
//

#ifndef SKY_LEXER_H
#define SKY_LEXER_H


#include <stdio.h>
#include <string>
#include <fstream>
#include "Tokenizer.h"
#include "Token.h"

class Lexer {
public:
    Lexer();
    ~Lexer();
    void lex(std::string);
    Token* next();

private:
    Tokenizer* tokenizer;
    void handleWord(std::string&, int, int&);
    void read(std::string&);
    void write(std::string&);
    bool doesOnlyContainWhitespace(std::string&);
    bool isComment(Token*);
    std::string extractErrorString(std::string&);
    int currentToken;
    std::vector<Token*> totalMatches;
    std::vector<Token*> totalErrors;
    std::vector<Token*> totalTokens;
};

#endif //SKY_LEXER_H
