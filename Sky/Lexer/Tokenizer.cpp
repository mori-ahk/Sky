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

Token* Tokenizer::Tokenize(std::string& word, int& lineno, int& pos) {
    
    if (!isID(word, pos).empty()) {
        std::string match = isID(word, pos);
        if (RESERVED_WORDS.find(match) != RESERVED_WORDS.end()) {
            Token* reservedWordToken = new Token(RESERVED_WORDS.at(match), lineno, match);
            return reservedWordToken;
        } else {
            Token* idToken = new Token(TokenType::Id, lineno, match);
            return idToken;
        }
    }
    
    if (!isFloat(word, pos).empty()) {
        std::string match = isFloat(word, pos);
        Token* floatToken = new Token(TokenType::Float, lineno, match);
        return floatToken;
    }
    
    if (!isInteger(word, pos).empty()) {
        std::string match = isInteger(word, pos);
        Token* integerToken = new Token(TokenType::Integer, lineno, match);
        return integerToken;
    }
    
    if (!isLongOperator(word, pos).empty()) {
        std::string match = isLongOperator(word, pos);
        if (RESERVED_WORDS.find(match) != RESERVED_WORDS.end()) {
            Token* longOpToken = new Token(RESERVED_WORDS.at(match), lineno, match);
            return longOpToken;
        }
    }
    
    if (!isShortOperator(word, pos).empty()) {
        std::string match = isShortOperator(word, pos);
        if (RESERVED_WORDS.find(match) != RESERVED_WORDS.end()) {
            Token* shortOpToken = new Token(RESERVED_WORDS.at(match), lineno, match);
            return shortOpToken;
        }
    }
    
    if (!isComment(word, pos).empty()) {
        std::string match = isComment(word, pos);
        if (RESERVED_WORDS.find(match) != RESERVED_WORDS.end()) {
            Token* commentToken = new Token(RESERVED_WORDS.at(match), lineno, match);
            return commentToken;
        }
    }
    
    return nullptr;
}


std::string Tokenizer::isID(std::string& word, int& pos) {
    std::regex reg ("^(([a-z]|[A-Z])([a-z]|[A-Z]|[1-9][0-9]*|_)*)");
    std::smatch match;
    std::regex_search(word, match, reg);
    return !match.empty() ? match[0].str() : std::string();
}

std::string Tokenizer::isFloat(std::string& word, int& pos) {
    std::regex reg ("^([1-9][0-9]*.[0-9]*[0-9]?[e]?[+-]?[1-9]?[0-9]*)");
    std::smatch match;
    std::regex_search(word, match, reg);
    return !match.empty() ? match[0].str() : std::string();
}

std::string Tokenizer::isInteger(std::string& word, int& pos) {
    std::regex reg ("^([1-9][0-9]*|0)");
    std::smatch match;
    std::regex_search(word, match, reg);
    return !match.empty() ? match[0].str() : std::string();
}

std::string Tokenizer::isLongOperator(std::string& word, int& pos) {
    std::regex reg("^(==|<=|>=|<>|::)");
    std::smatch match;
    std::regex_search(word, match, reg);
    return !match.empty() ? match[0].str() : std::string();
}

std::string Tokenizer::isShortOperator(std::string& word, int& pos) {
    std::regex reg("^(\\[|\\]|\\(|\\)|\\{|\\}|\\+|-|=|>|<|\\*|:|;|,|/|\\.)");
    std::smatch match;
    std::regex_search(word, match, reg);
    return !match.empty() ? match[0].str() : std::string();
}

std::string Tokenizer::isComment(std::string& word, int& pos) {
    std::regex reg("^(//|/\\*|\\*/)");
    std::smatch match;
    std::regex_search(word, match, reg);
    return !match.empty() ? match[0].str() : std::string();
}

