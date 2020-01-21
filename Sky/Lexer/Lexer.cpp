//
//  Lexer.cpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#include "Lexer.hpp"
#include <iostream>
#include <fstream>

void Lexer::lex(std::string filePath) {
    
    char ch;
    std::string word;
    std::ifstream infile;
    infile.open (filePath, std::ios::in);
    while(!infile.eof()) {
        infile.get(ch);
        word += ch;
        this->tokenizer->Tokenize(word, 0);
    }
    
    infile.close();
    
    return;
}
