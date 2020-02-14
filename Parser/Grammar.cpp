//
// Created by Morteza Ahmadi on 2020-02-07.
//

#include "Grammar.h"


Grammar::Grammar() {
    parseGrammar();
    constructFirstSet();
    constructFollowSet();
}

Grammar::~Grammar() {}

void Grammar::parseGrammar() {
    std::string line;
    std::ifstream stream;
    std::string delimiter = " -> ";
    stream.open ("Parser/Grammar.txt", std::ios::in);

    while (!stream.eof()) {
        std::getline(stream, line);
        if(line.empty()) continue;

        auto it = line.find(delimiter);
        std::string ruleName = line.substr(0, it);
        line.erase(0,it + delimiter.length());
        std::string RHS = line.substr(0, line.find("  ."));

        if (RULES.find(ruleName) == RULES.end()) {
            RULES[ruleName] = new Rule(ruleName);
        }

        if (RHS.empty()) RULES[ruleName]->addToRHS("#");
        else RULES[ruleName]->addToRHS(RHS);
    }

    for (auto& rule: RULES) {
        for (auto& production: rule.second->getRHS()) {
            rule.second->seperateRHS(production);
        }
    }
}

void Grammar::constructFirstSet() {
    for (auto& rule: RULES)
        rule.second->visited = false;

    for (auto& rule: RULES)
        if (!rule.second->visited) constructFirstSetHelper(rule.second);
}

void Grammar::constructFirstSetHelper(Rule* rule) {
    rule->visited = true;
    if (rule->isTerminal()) {
        rule->addToFirst(rule->getName());
        return;
    }

    for (std::string& production : rule->getRHS()) {
        if (production == "#") rule->addToFirst("#");
    }

    for (std::string& _rule: rule->getSeparatedRHS()) {
        if (_rule == "#") continue;
        rule->nullable = true;
        Rule* toDiscover;

        if (!Rule::isTerminal(_rule))
             toDiscover = RULES[_rule];
        else {
            rule->addToFirst(_rule);
            continue;
        }

        if (!toDiscover->visited) constructFirstSetHelper(toDiscover);

        // union the two sets except the null character.
        rule->getFirst().insert(toDiscover->getFirst().begin(), toDiscover->getFirst().end());
        rule->getFirst().erase("#");

        if (toDiscover->getFirst().find("#") == toDiscover->getFirst().end()) {
            rule->nullable = false;
            break;
        }
    }

    if (rule->nullable) {
        rule->addToFirst("#");
    }
}


void Grammar::constructFollowSet()  {
    for (auto& rule: RULES)
        rule.second->visited = false;

    for (auto& rule: RULES)
        if (!rule.second->visited) constructFollowSetHelper(rule.second);
}


void Grammar::constructFollowSetHelper(Rule *) {

}

Rule* Grammar::getRule(std::string& rule) {
    return RULES.at(rule);
}


bool Grammar::shouldTake(std::string& production, Token* token) {
    std::vector<std::string> separated = split(production);
    std::string firstRule = separated.front();
    if (Rule::isTerminal(firstRule)) {
        return firstRule == token->getReverseTokenTypeMap()[token->getType()];
    }
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



