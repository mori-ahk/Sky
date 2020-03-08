//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Parser.h"

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->grammar = new Grammar();
    this->AST_Builder = new ASTBuilder();
    this->currentToken = lexer->next();
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

bool Parser::isKeyword(std::string& rule) {
    return KEYWORDS.find(rule) != KEYWORDS.end();
}

void Parser::printError(Rule& rule) {
    if (currentToken == nullptr) return;
        std::cout << "ERROR: at line " << currentToken->getLineno() << " at position: " << currentToken->getPosition() << " expected one of these: ";
        for (auto _rule: rule.getFollow()) {
            std::cout << _rule << ", ";
        }
        std::cout << std::endl;
}

void Parser::panic(std::string& rule) {
    while (!parse(rule, true)) next();
}

bool Parser::parse(std::string LHS, bool isOnPanicMode) {
    if (currentToken == nullptr and isOnPanicMode) return true;
    if (currentToken == nullptr) return true;

    if (Rule::isTerminal(LHS)) {
        if (shouldTakeNext(LHS)) {
            if (isKeyword(LHS)) {
                std::string value = currentToken->getValue();
                AST_Builder->push(value);
                AST_Builder->printStack();
            }
            next();
            return true;
        } else return false;
    }

    Rule* currentRule = grammar->getRule(LHS);
    if (!currentRule->doesBelongToFirst(currentToken)) {
        if ((isOnPanicMode or currentRule->isNullable()) and currentRule->doesBelongToFollow(currentToken)) {
            AST_Builder->push(LHS);
            AST_Builder->printStack();
            return true;
        } else return false;
    }

    std::vector<std::string> rulesToProcess;
    bool found = false;
    for(auto& production : currentRule->getRHS()) {
        if (found) break;
        for (auto& _rule: production) {
            if (_rule != "#" and _rule.front() != '@') {
                if (grammar->shouldTake(_rule, currentToken)) {
                    rulesToProcess = production;
                    found = true;
                    break;
                } else break;
            }
        }
    }

    for(auto& rule: rulesToProcess) {
        if (rule.front() == '@') { // do action
            AST_Builder->handle(rule, LHS);
            continue;
        } else {
            bool result = parse(rule);
            if (!result) {
                AST_Builder->isIgnoreModeOn = true;
                printError(*currentRule);
                panic(rule);
            }
        }
    }

    return true;
}

