//
//  Tokenizer.hpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#ifndef Tokenizer_hpp
#define Tokenizer_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.hpp"
#include "TokenType.hpp"

class Tokenizer {
public:
    
    Tokenizer();
    ~Tokenizer();
    std::vector<Token*> Tokenize(std::string);
    std::vector<Token*> matches;
    
private:
    std::string word;
    
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
    
    Token* isInteger(std::string);
    Token* isFloat(std::string);
    Token* isID(std::string);
    Token* isKeyword(std::string);
    
};

#endif /* Tokenizer_hpp */
