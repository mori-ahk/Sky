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
    if (isInteger(word, lineno) != nullptr) matches.push_back(isInteger(word, lineno));
    if (isFloat(word, lineno) != nullptr) matches.push_back(isFloat(word, lineno));
    if (isID(word, lineno) != nullptr) matches.push_back(isID(word, lineno));
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
    if (std:: regex_match(word, reg)) {
        Token* floatToken = new Token(TokenType::Float, lineno, word);
        return floatToken;
    } else return nullptr;
}

Token* Tokenizer::isID(std::string word, int lineno) {
    std::regex reg ("(([a-z]|[A-Z])([a-z]|[A-Z]|[1-9][0-9]*|_)*)");
    if (std::regex_match(word, reg)) {
        if (RESERVED_WORDS.find(word) != RESERVED_WORDS.end()) {
            Token* reservedWordToken = new Token(RESERVED_WORDS.at(word), lineno, word);
            return reservedWordToken;
        } else {
            Token* idToken = new Token(TokenType::Id, lineno, word);
            return idToken;
        }
    } else return nullptr;
}

Token* Tokenizer::isKeyword(std::string word, int lineno) {
    
    return nullptr;
}

