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

std::vector<Token*> matches;
const std::unordered_map<std::string, TokenType> RESERVED_WORDS = {
    { "==", TokenType::Eq },
    { "<>", TokenType::NotEq },
    { "<", TokenType::Lt },
    { ">", TokenType::Gt },
    { "<=", TokenType::LEq },
    { ">=", TokenType::GEq },
    { "+", TokenType::Plus },
    { "-", TokenType::Minus },
    { "*", TokenType::Mult },
    { "/", TokenType::Div },
    { "=", TokenType::Asgn },
    { "(", TokenType::OpenPr },
    { ")", TokenType::ClosePr },
    { "{", TokenType::OpenCbr },
    { "}", TokenType::CloseCbr },
    { "[", TokenType::OpenSqbr },
    { "]", TokenType::CloseSqbr },
    { ";", TokenType::Semi },
    { ",", TokenType::Comma },
    { ".", TokenType::Dot },
    { ":", TokenType::Colon },
    { "::", TokenType::DblColon },
    { "//", TokenType:: InlineCmt },
    { "/*", TokenType::BlockOpenCmt },
    { "*/", TokenType::BlockCloseCmt },
    { "if", TokenType::If },
    { "then", TokenType::Then },
    { "else", TokenType::Else },
    { "integer", TokenType::__Integer },
    { "float", TokenType::__Float },
    { "while", TokenType::While },
    { "class", TokenType::Class },
    { "do", TokenType::Do },
    { "end", TokenType::End },
    { "public", TokenType::Public },
    { "private", TokenType::Private },
    { "or", TokenType::Or },
    { "and", TokenType::And },
    { "not", TokenType::Not },
    { "read", TokenType::Read },
    { "write", TokenType::Write },
    { "return", TokenType::Return },
    { "main", TokenType::Main },
    { "inherits", TokenType::Inherits},
    { "local", TokenType::Local },
};

Tokenizer::Tokenizer() {}

Tokenizer::~Tokenizer() {}

int Tokenizer::Tokenize(std::string word, int lineno) {
    matches.clear();
    
    if (isInteger(word)) {
        Token* integerToken = new Token(TokenType::Integer, lineno, word);
        matches.push_back(integerToken);
    }
    
    if (isFloat(word)) {
        Token* floatToken = new Token(TokenType::Float, lineno, word);
        matches.push_back(floatToken);
    }
    
    if (isID(word)) {
        if (RESERVED_WORDS.find(word) != RESERVED_WORDS.end()) {
            Token* reservedWordToken = new Token(RESERVED_WORDS.at(word), lineno, word);
            matches.push_back(reservedWordToken);
        } else {
            Token* idToken = new Token(TokenType::Id, lineno, word);
            matches.push_back(idToken);
        }
    }
    
    if (isSpecial(word)) {
        if (RESERVED_WORDS.find(word) != RESERVED_WORDS.end()) {
            Token* specialToken = new Token(RESERVED_WORDS.at(word), lineno, word);
            matches.push_back(specialToken);
        }
    }
    
    return int(matches.size());
}

bool Tokenizer::isInteger(std::string word) {
    std::regex reg ("([1-9][0-9]*|0)");
    return std::regex_match(word, reg);
}

bool Tokenizer::isFloat(std::string word) {
    std::regex reg ("[1-9][0-9]*.[0-9]*[0-9]?[e]?[+-]?[1-9]?[0-9]*");
    return std::regex_match(word, reg);
}

bool Tokenizer::isID(std::string word) {
    std::regex reg ("(([a-z]|[A-Z])([a-z]|[A-Z]|[1-9][0-9]*|_)*)");
    return std::regex_match(word, reg);
}

bool Tokenizer::isSpecial(std::string word) {
    std::regex reg("\\[|\\]|\\(|\\)|\\{|\\}|\\+|-|=|==|<=|>=|>|<|//|\\*|/\\*|\\*/|:|::|;|,|/|<>|\\.");
    return std::regex_match(word, reg);
}

std::vector<Token*> Tokenizer::getMatches() { return matches; }

