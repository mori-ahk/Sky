//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Parser.h"

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->grammar = new Grammar();
    currentToken = lexer->next();
}


Parser::~Parser() {}

void Parser::next() {
    while (currentToken->getType() == currentToken->getTokenTypeMap().at("error")) currentToken = lexer->next();
    currentToken = lexer->next();
}

bool Parser::shouldTakeNext(std::string& LHS) {
    return currentToken->getTokenTypeMap().at(LHS) == currentToken->getType();
}

bool Parser::parse(std::string LHS) {
    if (currentToken == nullptr) return true;

    if (Rule::isTerminal(LHS)) {
        std::cout << currentToken->getValue() << std::endl;
        if (shouldTakeNext(LHS)) {
            next();
            return true;
        } else return false;
    }

    Rule* currentRule = grammar->getRule(LHS);
    if (!currentRule->doesBelongToFirst(currentToken)) {
        return currentRule->isNullable() and currentRule->doesBelongToFollow(currentToken);
    }

    std::vector<std::string> rulesToProcess;
    for(auto& production : currentRule->getRHS()) {
        if (production.front() != "#") {
            if (grammar->shouldTake(production.front(), currentToken)) {
                rulesToProcess = production;
                break;
            }
        }
    }

    for(auto& rule: rulesToProcess) {
        bool result = parse(rule);
        if (!result) {
            std::cout << "ERROR expected: " << rule << std::endl;
        }
    }

    return true;
}

