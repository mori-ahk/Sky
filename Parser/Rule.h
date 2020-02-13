//
// Created by Morteza Ahmadi on 2020-02-07.
//

#ifndef SKY_RULE_H
#define SKY_RULE_H

#include <string>
#include <vector>
#include <unordered_set>
#include "RuleType.h"
#include "../Lexer/Token.h"
class Rule {
public:

    Rule(RuleType, std::unordered_set<std::string>, std::unordered_set<std::string>, std::vector<std::string>, bool nullable = false, bool endable = false);
    ~Rule();

    RuleType getType();
    std::unordered_set<std::string>& getFirst();
    std::unordered_set<std::string>& getFollow();
    std::vector<std::string>& getRHS();
    std::vector<std::string>& getSeparatedRHS();

    bool isNullable();
    bool isEndable();
    bool doesBelongToFirst(Token*);
    bool doesBelongToFollow(Token*);
    void seperateRHS(std::string&);
    std::string getNextRule();
private:

    bool doesContainWhitespace(std::string&);
    RuleType type;
    std::unordered_set<std::string> first;
    std::unordered_set<std::string> follow;
    std::vector<std::string> RHS;
    std::vector<std::string> separatedRHS;
    bool nullable;
    bool endable;

    int currentRule;


};


#endif //SKY_RULE_H
