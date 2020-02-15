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

bool Parser::parse(std::string LHS) {
    if (currentToken == nullptr) return true;
    if (Rule::isTerminal(LHS)) {
        std::cout << currentToken->getValue() << std::endl;
        if (currentToken->getTokenTypeMap()[LHS] == currentToken->getType()) {
            currentToken = lexer->next();
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
        auto v = grammar->getRule(rule);
        if (!result) {
            std::cout << "ERROR expected: " << rule << std::endl;
        }
    }

    return true;
}

