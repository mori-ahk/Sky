//
//  Lexer.cpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#include "Lexer.hpp"
#include "Token.hpp"
#include <iostream>
#include <fstream>
#include <regex>

std::vector<Token*> totalMatches;
std::vector<Token*> totalErrors;

Lexer::Lexer() {
    tokenizer = new Tokenizer();
}

Lexer::~Lexer() {
    delete tokenizer;
}

void Lexer::handleWord(std::string& line, int lineNumber, int& pos) {
    Token* matchedToken = tokenizer->Tokenize(line, lineNumber, pos);
    if (matchedToken == nullptr) {
        Token* errorToken = new Token(TokenType::Error, lineNumber, matchedToken->getValue());
        totalErrors.push_back(errorToken);
    } else {
        totalMatches.push_back(matchedToken);
    }
    pos += matchedToken->getValue().size();
}

void Lexer::lex(std::string filePath) {

    int lineNumber = 0;
    
    std::string word;
    std::string line;
    std::ifstream stream;
    std::regex reg("\\s+");
    int pos = 0;
    stream.open (filePath, std::ios::in);
    while(!stream.eof()) {
        std::getline(stream, line);
        word = line;
        line = std::regex_replace(line, reg, "");
        lineNumber++;
        while (word.size() != 0) {
            word = line.substr(pos);
            handleWord(word, lineNumber, pos);
        }
        
        
    }
    
    stream.close();
    
   
    
//    for (auto& c: totalMatches) {
//        std::cout << *c << std::endl;
//    }
//
//    for (auto& c: totalErrors) {
//        std::cout << *c << std::endl;
//    }
}
