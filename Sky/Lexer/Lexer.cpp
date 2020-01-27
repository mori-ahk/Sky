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

bool Lexer::doesOnlyContainWhitespace(std::string& line) {
    for (char c: line) {
        if (c != ' ') return false;
    }
    return true;
}

std::string Lexer::extractErrorString(std::string& line) {
    int counter = 0;
    while (line.size() > counter && line.at(counter) != ' ' && line.at(counter) != '\n') counter++;
    return line.substr(0, counter);
}

void Lexer::handleWord(std::string& line, int lineNumber, int& pos) {
    if (doesOnlyContainWhitespace(line)) return;
    if (line.at(0) == '\n') {
        pos++;
        return;
    }
    
    Token* matchedToken = tokenizer->Tokenize(line, lineNumber, pos);
    if (matchedToken == nullptr) {
        std::string errorTokenString = extractErrorString(line);
        Token* errorToken = new Token(TokenType::Error, lineNumber, errorTokenString);
        totalErrors.push_back(errorToken);
        pos += errorTokenString.size();
    } else {
        totalMatches.push_back(matchedToken);
        pos += matchedToken->getValue().size();
    }
}

void Lexer::read(std::string& filePath) {
    std::string fileContent;
    std::string line;
    std::ifstream stream;
    int pos = 0;
    int lineNumber = 1;
    stream.open (filePath, std::ios::in);
    
    while (!stream.eof()) {
        std::getline(stream, line);
        fileContent += line + "\n";
    }
    
    while (fileContent.size() != 0) {
        if (fileContent.at(pos) == '\n') lineNumber++;
        handleWord(fileContent, lineNumber, pos);
        while (fileContent.size() > pos && fileContent.at(pos) == ' ') pos++;
        fileContent = fileContent.substr(pos);
        pos = 0;
    }
    
    stream.close();
}


void Lexer::write(std::string& filePath) {
    std::string fileName;
    
    for (auto& c : filePath) {
        if (c == '.') break;
        fileName += c;
    }
    
    int lastPrintedLine = totalMatches.front()->getLineno();
    std::ofstream stream(fileName + "_lex_tokens.txt");
    for (int i = 0; i < totalMatches.size(); i++) {
        if (i+1 < totalMatches.size() && totalMatches.at(i)->getLineno() < totalMatches.at(i+1)->getLineno()) {
            stream << *(totalMatches.at(i)) << std::endl;
        } else stream << *(totalMatches.at(i)) << " ";
    }
    
    stream.close();
    
    lastPrintedLine = totalMatches.front()->getLineno();
    stream.open(fileName + "_lex_errors.txt");
    for (int i = 0; i < totalErrors.size(); i++) {
        if (i+1 < totalErrors.size() && totalErrors.at(i)->getLineno() < totalErrors.at(i+1)->getLineno()) {
            stream << *(totalErrors.at(i)) << std::endl;
        } else stream << *(totalErrors.at(i)) << " ";
    }
    
    stream.close();
}


void Lexer::lex(std::string filePath) {
    totalMatches.clear();
    totalErrors.clear();
    read(filePath);
    write(filePath);
}
