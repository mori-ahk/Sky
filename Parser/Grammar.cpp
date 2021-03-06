//
// Created by Morteza Ahmadi on 2020-02-07.
//

#include "Grammar.h"


Language::Grammar::Grammar() {
    // Adding terminals to RULES map
    for (const auto &_rule: Rule::getTerminals()) ruleNames.push_back(_rule.first);
    for (const auto &_rule: Rule::getTerminals()) RULES[_rule.first] = new Rule(_rule.first);
    parseGrammar();
    constructFirstSet();
    constructFollowSet();
}

void Language::Grammar::parseGrammar() {
    std::string line;
    std::ifstream stream;
    std::string delimiter = " -> ";
    stream.open("Parser/Grammar.txt", std::ios::in);

    while (!stream.eof()) {
        std::getline(stream, line);
        if (line.empty()) continue;

        auto it = line.find(delimiter);
        std::string ruleName = line.substr(0, it);
        line.erase(0, it + delimiter.length());
        std::string RHS = line.substr(0, line.find("  ."));
        std::vector<std::string> _RHS = split(RHS);

        if (!doesContainRuleName(ruleName)) ruleNames.push_back(ruleName);
        if (RULES.find(ruleName) == RULES.end()) {
            RULES[ruleName] = new Rule(ruleName);
        }

        if (RHS.empty()) RULES[ruleName]->addToRHS({"#"});
        else RULES[ruleName]->addToRHS(_RHS);
    }
}

void Language::Grammar::constructFirstSet() {
    for (const auto &rule: ruleNames)
        RULES[rule]->visited = false;

    for (const auto &rule: ruleNames)
        if (!RULES[rule]->visited) constructFirstSetHelper(RULES[rule]);
}

void Language::Grammar::constructFirstSetHelper(Rule *rule) {
    rule->visited = true;
    if (rule->isTerminal()) {
        rule->addToFirst(rule->getName());
        return;
    }

    for (const auto &production : rule->getRHS()) {
        if (production.front() == "#") rule->addToFirst("#");
    }

    for (const auto &production : rule->getRHS()) {
        if (production.front() == "#") continue;
        bool nullable = true;
        for (const std::string &_rule: production) {
            if (_rule.front() == '@') continue;
            Rule *toDiscover = RULES[_rule];
            if (!toDiscover->visited) constructFirstSetHelper(toDiscover);

            // union the two sets except the null character.
            auto firstSet = std::unordered_set<std::string>(toDiscover->getFirst());
            firstSet.erase("#");
            rule->appendFirst(firstSet);

            if (toDiscover->getFirst().find("#") == toDiscover->getFirst().end()) {
                nullable = false;
                break;
            }
        }

        if (nullable) rule->addToFirst("#");
    }
}

void Language::Grammar::constructFollowSet() {
    for (const auto &rule: ruleNames) {
        RULES[rule]->visited = false;
        RULES[rule]->clearWatchList();
    }

    for (const auto &rule: ruleNames)
        if (!RULES[rule]->visited) constructFollowSetHelper(RULES[rule]);

}

void Language::Grammar::constructFollowSetHelper(Rule *rule) {
    rule->visited = true;
    if (rule->getName() == "START") {
        rule->addToFollow("$");
        return;
    }

    auto v = findUsage(rule->getName());
    for (const auto &usage : v) {
        auto rules = usage.second;
        int lookAfter = rule->indexOf(rules, rule->getName());
        bool nullable = true;
        for (int i = lookAfter + 1; i < rules.size(); i++) {
            if (rules.at(i).front() == '@') continue;
            auto firstSet = std::unordered_set<std::string>(RULES[rules.at(i)]->getFirst());
            firstSet.erase("#");

            for (const auto &element: firstSet)
                rule->addToFollow(element);
            if (!RULES[rules.at(i)]->isNullable()) {
                nullable = false;
                break;
            }
        }

        if (nullable) {
            Rule *usageRule = RULES[usage.first];
            usageRule->addToWatchList(rule);
            if (!usageRule->visited) constructFollowSetHelper(usageRule);
        }
    }
}

longVector Language::Grammar::findUsage(const std::string &name) {
    longVector toReturn;
    for (const auto &rule : RULES) {
        for (const auto &production : rule.second->getRHS()) {
            for (const auto &_rule : production) {
                if (name == _rule) {
                    auto pair = std::make_pair(rule.second->getName(), production);
                    toReturn.push_back(pair);
                    break;
                }
            }
        }
    }

    return toReturn;
}

const Language::Rule *Language::Grammar::getRule(std::string &rule) const {
    return RULES.at(rule);
}

bool Language::Grammar::shouldTake(std::string &production, Token *token) {
    if (Rule::isTerminal(production)) {
        return production == token->getReverseTokenTypeMap()[token->getType()];
    }
    const Rule *rule = getRule(production);
    return rule->doesBelongToFirst(token) ||
           (rule->isNullable() && rule->doesBelongToFollow(token));
}

std::vector<std::string> Language::Grammar::split(std::string &production) {
    std::vector<std::string> toReturn;
    std::string splitted;
    for (int i = 0; i < production.size(); i++) {
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

bool Language::Grammar::doesContainRuleName(std::string &rule) {
    for (const auto &_rule : ruleNames) {
        if (_rule == rule) return true;
    }
    return false;
}


