//
// Created by Morteza Ahmadi on 2020-02-07.
//

#ifndef SKY_GRAMMAR_H
#define SKY_GRAMMAR_H

#include "Rule.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

typedef std::vector<std::pair<std::string, std::vector<std::string>>> longVector;

namespace Language {
    class Grammar {
    public:
        Grammar();
        ~Grammar() = default;

        Rule *getRule(std::string &);
        bool shouldTake(std::string &, Token *);

    private:
        void constructFirstSet();
        void constructFirstSetHelper(Rule *);
        void constructFollowSetHelper(Rule *);
        void constructFollowSet();
        void parseGrammar();

        bool doesContainRuleName(std::string &);

        longVector findUsage(const std::string&);

        std::vector<std::string> split(std::string &);
        std::vector<std::string> ruleNames;
        std::unordered_map<std::string, Rule *> RULES;
    };
}

#endif //SKY_GRAMMAR_H
