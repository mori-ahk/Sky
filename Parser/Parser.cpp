//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Parser.h"

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->grammar = new Grammar();
    currentToken = lexer->next();
}


Parser::~Parser() {
    delete currentToken;
    delete lexer;
    delete grammar;
}

void Parser::next() {
    while (currentToken->getType() == currentToken->getTokenTypeMap().at("error")) currentToken = lexer->next();
    currentToken = lexer->next();
}

bool Parser::shouldTakeNext(std::string& LHS) {
    return currentToken->getTokenTypeMap().at(LHS) == currentToken->getType();
}

bool Parser::isUseless(std::string & rule) {
    return USELESS.find(rule) != USELESS.end();
}

void Parser::printError(Rule& rule) {
    if (!rule.isNullable()) {
        std::cout << "ERROR: at line " << currentToken->getLineno() << " at position: " << currentToken->getPosition() << " expected one of these: ";
        for (auto _rule: rule.getFollow()) {
            std::cout << _rule << ", ";
        }
        std::cout << *rule.getFirst().begin() << std::endl;
    }
}

void Parser::panic(std::string& rule) {
    while (!parse(rule, true)) next();
}

bool Parser::parse(std::string LHS, bool isOnPanicMode) {
    if (currentToken == nullptr and isOnPanicMode) return true;
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
        return (isOnPanicMode or currentRule->isNullable()) and currentRule->doesBelongToFollow(currentToken);
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
            panic(rule);
            printError(*currentRule);
        }
    }

    return true;
}

