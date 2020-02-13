//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Parser.h"

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
//    currentRule = grammar->getRule(START);
    currentToken = lexer->next();
}

Parser::~Parser() {}

bool Parser::parse(std::string LHS) {
    if (currentToken == nullptr) return true;
    if (grammar->isTerminal(LHS)) {
        std::cout << currentToken->getValue() << std::endl;
//        std::cout << LHS << std::endl;
        if (currentToken->getTokenTypeMap()[LHS] == currentToken->getType()) {
            currentToken = lexer->next();
            return true;
        } else {
            return false;
        }
    }

    Rule* currentRule = grammar->getRule(LHS);
    if (!currentRule->doesBelongToFirst(currentToken)) {
        if (currentRule->isNullable() and currentRule->doesBelongToFollow(currentToken)) {
            return true;
        } else {
            return false;
        }
    }

    for(auto& production : currentRule->getRHS()) {
        if (grammar->shouldTake(production, currentToken)) {
            currentRule->seperateRHS(production);
            break;
        }
    }

    for(auto& rule: currentRule->getSeparatedRHS()) {
        bool result = parse(rule);
        if (!result) {
            std::cout << "ERROR expected: " << rule << std::endl;
        }
    }

    return true;
}

