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
        if (LHS == currentToken->getType())
        currentToken = lexer->next();

        return true;
    }
    currentRule = grammar->getRule(LHS);
    for(auto& production : currentRule->getRHS()) {
        if (grammar->shouldTake(production, currentToken)) {
            currentRule->seperateRHS(production);
            break;
        }
    }

    if (currentRule->doesBelongToFirst(currentToken)) {
        return parse(currentRule->getNextRule());
    } else if (currentRule->doesBelongToFollow(currentToken)) {
        return true;
    } else return false;
}
