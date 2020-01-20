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
    if (isInteger(word, lineno)) {
        Token* integerToken = new Token(TokenType::Integer, lineno, word);
        matches.push_back(integerToken);
    }
    
    if (isFloat(word, lineno)) {
        Token* floatToken = new Token(TokenType::Float, lineno, word);
        matches.push_back(floatToken);
    }
    
    if (isID(word, lineno)) {
        if (RESERVED_WORDS.find(word) != RESERVED_WORDS.end()) {
            Token* reservedWordToken = new Token(RESERVED_WORDS.at(word), lineno, word);
            matches.push_back(reservedWordToken);
        } else {
            Token* idToken = new Token(TokenType::Id, lineno, word);
            matches.push_back(idToken);
        }
    }
    
    return matches;
}

bool Tokenizer::isInteger(std::string word, int lineno) {
    std::regex reg ("([1-9][0-9]*|0)");
    return std::regex_match(word, reg);
}

bool Tokenizer::isFloat(std::string word, int lineno) {
    std::regex reg ("(([1-9][0-9]*|0)(.[0-9]*[1-9]|.0)([e]?[+-]?[1-9][0-9]*|0))");
    return std::regex_match(word, reg);
}

bool Tokenizer::isID(std::string word, int lineno) {
    std::regex reg ("(([a-z]|[A-Z])([a-z]|[A-Z]|[1-9][0-9]*|_)*)");
    return std::regex_match(word, reg);
}

bool Tokenizer::isKeyword(std::string word, int lineno) {
    
    return nullptr;
}

