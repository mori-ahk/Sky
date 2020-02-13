//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Parser.h"

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    currentRule = grammar->getRule(START);
    currentToken = lexer->next();
}

Parser::~Parser() {}

bool Parser::parse(std::string LHS) {
    if (grammar->isTerminal(LHS)) {
        std::cout << currentToken->getValue() << std::endl;
        if (currentToken->getTokenTypeMap()[LHS] == currentToken->getType()) {
            currentToken = lexer->next();
            return true;
        } else return false;
    }

    if (!currentRule->doesBelongToFirst(currentToken)) {
        return currentRule->isNullable() and currentRule->doesBelongToFollow(currentToken);
    }

    currentRule = grammar->getRule(LHS);
    for(auto& production : currentRule->getRHS()) {
        if (grammar->shouldTake(production, currentToken)) {
            currentRule->seperateRHS(production);
            break;
        }
    }

    for(auto& rule: currentRule->getSeparatedRHS()) {
        return parse(rule);
    }
}

