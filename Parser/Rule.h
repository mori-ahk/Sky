//
// Created by Morteza Ahmadi on 2020-02-07.
//

#ifndef SKY_RULE_H
#define SKY_RULE_H

#include <string>
#include <unordered_set>
#include "RuleType.h"

class Rule {
public:

    Rule(RuleType, std::unordered_set<std::string>, std::unordered_set<std::string>, std::vector<std::string>);
    ~Rule();

    RuleType getType();
    std::string getName();
    std::unordered_set<std::string>& getFirst();
    std::unordered_set<std::string>& getFollow();
    std::vector<std::string>& getRHS();

    bool doesBelongToFirst();
    bool doesBelongToFollow();

private:

    std::string name;
    RuleType type;
    std::unordered_set<std::string> first;
    std::unordered_set<std::string> follow;
    std::vector<std::string> RHS;

};


#endif //SKY_RULE_H
