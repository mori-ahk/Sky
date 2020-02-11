//
// Created by Morteza Ahmadi on 2020-02-11.
//

#include "Parser.h"

Parser::Parser() {}

Parser::~Parser() {}

void Parser::parse(Token* token, std::string ruleString) {
    if (ruleString.empty()) return;
    Rule* rule = grammar->getRule(ruleString);
    if (rule->doesBelongToFirst(token)) {
        parse(token, rule->getNextRule());
    } else {
        std::cout << "false" << std::endl;
    }
}
