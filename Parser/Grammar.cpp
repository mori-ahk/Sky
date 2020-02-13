//
// Created by Morteza Ahmadi on 2020-02-07.
//

#include "Grammar.h"

Grammar::Grammar() {}
Grammar::~Grammar() {}

Rule* Grammar::getRule(std::string& rule) {
    return RULES.at(rule);
}

bool Grammar::isTerminal(std::string& rule) {
    return TERMINALS.find(rule) != TERMINALS.end();
}

bool Grammar::shouldTake(std::string& production, Token* token) {
    std::vector<std::string> separated = split(production);
    std::string firstRule = separated.front();
    if (isTerminal(firstRule)) return true;
    Rule* rule = getRule(firstRule);
    return rule->doesBelongToFirst(token) or
           (rule->isNullable() and rule->doesBelongToFollow(token));
}


std::vector<std::string> Grammar::split(std::string& production) {
    std::vector<std::string> toReturn;
    std::string splitted;
    for(int i = 0; i < production.size(); i++) {
        if (production.at(i) == ' ') {
            toReturn.push_back(splitted);
            splitted.clear();
        } else {
            splitted += production.at(i);
            if (i == production.size() - 1) toReturn.push_back(splitted);
        }
    }

    return toReturn;
}