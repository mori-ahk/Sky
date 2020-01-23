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

void Lexer::handleWord(std::string& word, int lineNumber, char& currChar, std::ifstream& stream) {
    int numMatches = 0;
    numMatches = tokenizer->Tokenize(word, lineNumber);
    if (numMatches == 0) {
        
        if (word.size() > 0) word.pop_back();
        tokenizer->Tokenize(word, lineNumber);
        Token* matchedToken = tokenizer->getMatches().size() != 0 ? tokenizer->getMatches().at(0) : nullptr;
        
        if (matchedToken != nullptr) {
            totalMatches.push_back(matchedToken);
            if (currChar != '\n') stream.putback(currChar);
        }
        
        word.clear();
    }
}

void Lexer::lex(std::string filePath) {
    
    char currChar;
    int lineNumber = 1;
    
    std::string word;
    std::ifstream infile;
    
    infile.open (filePath, std::ios::in);
    while(!infile.eof()) {
        infile.get(currChar);
        
        switch (currChar) {
            case '.':
                word += currChar;
                infile.get(currChar);
                word += currChar;
                handleWord(word, lineNumber, currChar, infile);
                break;
            case '\n':
                word += currChar;
                handleWord(word, lineNumber, currChar, infile);
                lineNumber++;
                break;
            default:
                word += currChar;
                handleWord(word, lineNumber, currChar, infile);
                break;
        }
    }
    
    infile.close();
    
    for (auto& c : totalMatches) {
        std::cout << *c << std::endl;
    }
    
    return;
}
