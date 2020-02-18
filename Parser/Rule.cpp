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

std::unordered_set<std::string>& Rule::getFirst() {
    return first;
}

std::unordered_set<std::string>& Rule::getFollow() {
    return follow;
}

std::string& Rule::getName() {
    return name;
}

std::vector<std::vector<std::string>>& Rule::getRHS() {
    return RHS;
}

void Rule::addToRHS(std::vector<std::string> rhs) {
    RHS.push_back(rhs);
}

void Rule::addToFirst(std::string terminal) {
    int prevSize = first.size();
    this->first.insert(terminal);
    if (prevSize != first.size())
        callWatchlist(true);
}

void Rule::addToFollow(std::string terminal) {
    int prevSize = follow.size();
    this->follow.insert(terminal);
    if (prevSize != follow.size())
        callWatchlist(false);
}

int Rule::indexOf(std::vector<std::string> vector, std::string rule) {
    for (int i = 0; i < vector.size(); i++) {
        if (rule == vector.at(i)) return i;
    }
    return -1;
}

bool Rule::isNullable() {
    return first.find("#") != first.end();
}

bool Rule::isTerminal() {
    return TERMINALS.find(this->name) != TERMINALS.end();
}

bool Rule::isTerminal(std::string & rule) {
    return TERMINALS.find(rule) != TERMINALS.end();
}

const std::unordered_map<std::string, std::string>& Rule::getTerminals() {
    return TERMINALS;
}

void Rule::addToWatchList(Rule *rule) {
    watchlist.push_back(rule);
    callWatchlist(false);
}

void Rule::clearWatchList() {
    watchlist.clear();
}

void Rule::callWatchlist(bool isFirst) {
    if (isFirst) {
        for (auto &s: first) {
            for (Rule* r: watchlist) {
                r->addToFirst(s);
            }
        }
    } else {
        for (auto &s: follow) {
            for (Rule* r: watchlist) {
                r->addToFollow(s);
            }
        }
    }
}

