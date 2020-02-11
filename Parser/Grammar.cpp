//
// Created by Morteza Ahmadi on 2020-02-07.
//

#include "Grammar.h"

Grammar::Grammar() {}
Grammar::~Grammar() {}

Rule* Grammar::getRule(std::string rule) {
    return RULES.at(rule);
}

