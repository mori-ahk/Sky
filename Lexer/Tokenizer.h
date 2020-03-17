//
// Created by Morteza Ahmadi on 2020-01-22.
//

#ifndef SKY_TOKENIZER_H
#define SKY_TOKENIZER_H


#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.h"
#include "TokenType.h"

class Tokenizer {
public:

    Tokenizer() = default;

    ~Tokenizer() = default;

    Token *Tokenize(std::string &, int &, int &);

private:

    std::string isInteger(std::string &);

    std::string isFloat(std::string &);

    std::string isID(std::string &);

    std::string isLongOperator(std::string &);

    std::string isShortOperator(std::string &);

    std::string isInlineComment(std::string &);

    std::string isMultilineComment(std::string &);
};


#endif //SKY_TOKENIZER_H
