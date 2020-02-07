//
// Created by Morteza Ahmadi on 2020-02-07.
//

#ifndef SKY_RULE_H
#define SKY_RULE_H

#include <string>
#include <unordered_set>

class Rule {
public:
    Rule();
    ~Rule();

    std::string getName();
    std::unordered_set<std::string>& getFirst();
    std::unordered_set<std::string>& getFollow();

    bool doesBelongToFirst();
    bool doesBelongToFollow();

private:

    std::string name;
    std::unordered_set<std::string> first;
    std::unordered_set<std::string> follow;

};


#endif //SKY_RULE_H
