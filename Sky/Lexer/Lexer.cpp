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

std::vector<Token*> totalMatches;
std::vector<Token*> totalErrors;

Lexer::Lexer() {
    tokenizer = new Tokenizer();
}

Lexer::~Lexer() {
    delete tokenizer;
}

std::vector<Token*> Lexer::getTotalMatches() {
    return totalMatches;
}

std::vector<Token*> Lexer::getTotalErrors() {
    return totalErrors;
}

bool Lexer::doesOnlyContainWhitespace(std::string& line) {
    for (char c: line) {
        if (c != ' ') return false;
    }
    return true;
}

std::string Lexer::extractErrorString(std::string& line) {
    int counter = 0;
    while (line.size() > counter && line.at(counter) != ' ') counter++;
    return line.substr(0, counter);
}

void Lexer::handleWord(std::string& line, int lineNumber, int& pos) {
    if (doesOnlyContainWhitespace(line)) return;
    Token* matchedToken = tokenizer->Tokenize(line, lineNumber, pos);
    if (matchedToken == nullptr) {
        std::string errorTokenString = extractErrorString(line);
        Token* errorToken = new Token(TokenType::Error, lineNumber, errorTokenString);
        totalErrors.push_back(errorToken);
        pos += errorTokenString.size();
        return;
    } else {
        totalMatches.push_back(matchedToken);
        pos += matchedToken->getValue().size();
    }
}

void Lexer::lex(std::string filePath) {
    std::string line;
    std::ifstream stream;
    int pos = 0;
    int lineNumber = 0;
    stream.open (filePath, std::ios::in);
    
    while(!stream.eof()) {
        std::getline(stream, line);
        lineNumber++;
        while (line.size() != 0) {
            handleWord(line, lineNumber, pos);
            while (line.size() > pos && line.at(pos) == ' ') pos++;
            line = line.substr(pos);
            pos = 0;
        }
    }
    
    stream.close();
}
