//
// Created by Morteza Ahmadi on 2020-02-07.
//

#include <vector>
#include "Rule.h"

Rule::Rule(std::string name) {
    this->name = name;
}

bool Rule::doesBelongToFirst(Token* token) {
    return first.find(token->getReverseTokenTypeMap()[token->getType()]) != first.end();
}

bool Rule::doesBelongToFollow(Token* token) {
    return follow.find(token->getReverseTokenTypeMap()[token->getType()]) != follow.end();
}

void Rule::seperateRHS(std::string& production, bool isParsing) {
    if (isParsing) this->separatedRHS.clear();
    if (!doesContainWhitespace(production)) {
        this->separatedRHS.push_back(production);
        return;
    }

    std::string toPushBack;
    for(int i = 0; i < production.size(); i++) {
        if (production.at(i) == ' ') {
            this->separatedRHS.push_back(toPushBack);
            toPushBack.clear();
        } else {
            toPushBack += production.at(i);
            if (i == production.size() - 1) this->separatedRHS.push_back(toPushBack);
        }
    }

}

bool Rule::doesContainWhitespace(std::string& rule) {
    for(char c: rule) {
        if (c == ' ') return true;
    }
    return false;
}

std::unordered_set<std::string>& Rule::getFirst() {
    return first;
}

std::unordered_set<std::string>& Rule::getFollow() {
    return follow;
}

std::string Rule::getName() {
    return name;
}

std::vector<std::string>& Rule::getRHS() {
    return RHS;
}

std::vector<std::string>& Rule::getSeparatedRHS() {
    return separatedRHS;
}

void Rule::addToRHS(std::string rhs) {
    RHS.push_back(rhs);
}

void Rule::addToFirst(std::string terminal) {
    this->first.insert(terminal);
}

void Rule::addToFollow(std::string terminal) {
    this->follow.insert(terminal);
}

bool Rule::isNullable() {
    return nullable;
}

bool Rule::isTerminal() {
    return TERMINALS.find(this->name) != TERMINALS.end();
}

bool Rule::isTerminal(std::string & rule) {
    return TERMINALS.find(rule) != TERMINALS.end();
}

