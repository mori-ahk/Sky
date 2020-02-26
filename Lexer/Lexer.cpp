//
// Created by Morteza Ahmadi on 2020-01-22.
//

#include "Lexer.h"
#include "Token.h"
#include <iostream>

Lexer::Lexer() {
    tokenizer = new Tokenizer();
    currentToken = 0;
}

Lexer::~Lexer() {
    delete tokenizer;

    for (auto token: totalMatches) {
        delete token;
    }

    for (auto token: totalErrors) {
        delete token;
    }

    for (auto token: totalTokens) {
        delete token;
    }
}

bool Lexer::isComment(Token* matchedToken) {
    if (matchedToken->getType() == TokenType::InlineCmt || matchedToken->getType() == TokenType::BlockCmt) return true;
    else return false;
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
    //process the next line if the current line is empty.
    if (doesOnlyContainWhitespace(line)) return;

    //Ignoring tab, empty space, new line or carriage return characters.
    if (line.at(0) == '\r' || line.at(0) == ' ' || line.at(0) == '\n' || line.at(0) == '\t') {
        pos++;
        linePosition += pos;
        return;
    }

    Token* matchedToken = tokenizer->Tokenize(line, lineNumber, pos);
    if (matchedToken == nullptr) {
        std::string errorTokenString = extractErrorString(line);
        Token* errorToken = new Token(TokenType::Error, lineNumber, errorTokenString);
        totalErrors.push_back(errorToken);
        totalTokens.push_back(errorToken);
        pos += errorTokenString.size();
        linePosition += pos;
        errorToken->setPosition(linePosition);
    } else {
        //Ignoring comment tokens
        if (!isComment(matchedToken)) {
            totalMatches.push_back(matchedToken);
            totalTokens.push_back(matchedToken);
        }

        pos += matchedToken->getValue().size();
        linePosition += pos;
        matchedToken->setPosition(linePosition);
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
        if (fileContent.at(pos) == '\n') {
            lineNumber++;
            linePosition = 0;
        }
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

    std::ofstream stream(fileName + "_lex_tokens.txt");
    for (int i = 0; i < totalMatches.size(); i++) {
        if (i+1 < totalMatches.size() && totalMatches.at(i)->getLineno() < totalMatches.at(i+1)->getLineno()) {
            stream << *(totalMatches.at(i)) << std::endl;
        } else stream << *(totalMatches.at(i)) << " ";
    }

    stream.close();

    stream.open(fileName + "_lex_errors.txt");
    for (int i = 0; i < totalErrors.size(); i++) {
        if (i+1 < totalErrors.size() && totalErrors.at(i)->getLineno() < totalErrors.at(i+1)->getLineno()) {
            stream << *(totalErrors.at(i)) << std::endl;
        } else stream << *(totalErrors.at(i)) << " ";
    }

    stream.close();
}

Token* Lexer::next() {
    return currentToken > totalTokens.size() - 1 ? nullptr : totalTokens.at(currentToken++);
}


void Lexer::lex(std::string filePath) {
    totalMatches.clear();
    totalErrors.clear();
    read(filePath);
    write(filePath);
}
