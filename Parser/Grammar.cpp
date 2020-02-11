//
// Created by Morteza Ahmadi on 2020-02-07.
//

#include "Grammar.h"

const std::unordered_map<RuleType, std::vector<std::string> >& Grammar::getRHS() {
    return RHS;
}

const std::unordered_map<RuleType, std::unordered_set<std::string> >& Grammar::getFIRST() {
    return FIRST;
}

const std::unordered_map<RuleType, std::unordered_set<std::string> >& Grammar::getFOLLOW() {
    return FOLLOW;
}

const Rule* Grammar::getRule(std::string rule) {
    return RULES.at(rule);
}

