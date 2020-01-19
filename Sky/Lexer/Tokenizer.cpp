//
//  Tokenizer.cpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#include <vector>
#include <regex>
#include "Tokenizer.hpp"
#include "Token.hpp"
#include "TokenType.hpp"

std::vector<Token*> Tokenizer::Tokenize(std::string word, int lineno) {
    matches.push_back(isInteger(word, lineno));
    matches.push_back(isFloat(word, lineno));
    return matches;
}

Token* Tokenizer::isInteger(std::string word, int lineno) {
    std::regex reg ("([1-9][0-9]*|0)");
    if (std::regex_match(word, reg)) {
        Token* integerToken = new Token(TokenType::Integer, lineno, word);
        return integerToken;
    } else return nullptr;
}

Token* Tokenizer::isFloat(std::string word, int lineno) {
    std::regex reg ("(([1-9][0-9]*|0)(.[0-9]*[1-9]|.0)([e]?[+-]?[1-9][0-9]*|0))");
    if ( std:: regex_match(word, reg) ) {
        Token* floatToken = new Token(TokenType::Float, lineno, word);
        return floatToken;
    } else return nullptr;
}

Token* Tokenizer::isID(std::string word, int lineno) {
    
    return nullptr;
}

Token* Tokenizer::isKeyword(std::string word, int lineno) {
    
    return nullptr;
}

