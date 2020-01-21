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

std::vector<Token*> totalMatches;

Lexer::Lexer() {
    tokenizer = new Tokenizer();
}

Lexer::~Lexer() {
    delete tokenizer;
}

void Lexer::lex(std::string filePath) {
    
    char letter;
    int lineNumber = 1;
    int numMatches = 0;
    std::string word;
    std::ifstream infile;
    
    infile.open (filePath, std::ios::in);
    while(!infile.eof()) {
        infile.get(letter);
        word += letter;
        numMatches = tokenizer->Tokenize(word, lineNumber);
        if (numMatches == 0) {
            if (word.size() > 0) word.pop_back();
            tokenizer->Tokenize(word, lineNumber);
            Token* matchedToken = tokenizer->getMatches().size() != 0 ? tokenizer->getMatches().at(0) : nullptr;
            word = "";
            if (matchedToken != nullptr) totalMatches.push_back(matchedToken);
        }
        
        if (letter == '\n') lineNumber++;
    }
    
    infile.close();
    
    return;
}
