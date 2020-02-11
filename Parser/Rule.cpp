//
// Created by Morteza Ahmadi on 2020-02-07.
//

#include <vector>
#include "Rule.h"

Rule::Rule(RuleType type, std::unordered_set<std::string> first, std::unordered_set<std::string> follow, std::vector<std::string> RHS) {
    this->type = type;
    this->first = first;
    this->follow = follow;
    seperateRHS(RHS);
    currentRule = 0;
}

bool Rule::doesBelongToFirst(Token* token) {
    return first.find(token->getValue()) != first.end();
}

bool Rule::doesBelongToFollow(Token* token) {
    return follow.find(token->getValue()) != follow.end();
}

void Rule::seperateRHS(std::vector<std::string>& RHS) {
    for(std::string& rule: RHS) {
        if (!doesContainWhitespace(rule)) {
            this->RHS.push_back(rule);
            continue;
        }
        std::string toPushBack;
        for(int i = 0; i < rule.size(); i++) {
            if (rule.at(i) == ' ') {
                this->RHS.push_back(toPushBack);
                toPushBack.clear();
            } else {
                toPushBack += rule.at(i);
                if (i == rule.size() - 1) this->RHS.push_back(toPushBack);
            }
        }
    }
}

bool Rule::doesContainWhitespace(std::string& rule) {
    for(char c: rule) {
        if (c == ' ') return true;
    }
    return false;
}

std::string Rule::getNextRule() {
    return currentRule > RHS.size() - 1 ? std::string() : RHS.at(currentRule++);
}

std::string RuleTypeString[] = {
        "MULT_OP",
        "LOCAL_SCOPE",
        "INHERITED_CLASSES",
        "FUNCTION_DECLARATION",
        "FUNCTION_CALL_PARAMS",
        "ASSIGNMENT_OP",
        "FUNCTION_DEFINITION",
        "START",
        "STATEMENT_FUNCTION_CALL",
        "ARRAY_DIMENSIONS",
        "TERM",
        "ASSIGN_STATEMENT_OR_FUNCTION_CALL",
        "REL_EXPRESSION_OR_NULL",
        "RIGHT_REC_TERM",
        "FUNCTION_BODY",
        "FUNCTION_SIGNATURE_NAMESPACE",
        "TYPE_OR_VOID",
        "VISIBILITY",
        "MEMBER_DECLARATIONS",
        "VARIABLE_EXT",
        "STATEMENT_VARIABLE_EXT",
        "ARITH_EXPRESSION",
        "EXPRESSION",
        "STATEMENT",
        "ADD_OP",
        "FUNCTION_DEFINITIONS",
        "CLASS_DECLARATIONS",
        "STATEMENT_VARIABLE_OR_FUNCTION_CALL",
        "VARIABLE_OR_FUNCTION_CALL_EXT",
        "CLASS_DECLARATION",
        "VARIABLE_DECLARATIONS",
        "REL_EXPRESSION",
        "FUNCTION_PARAMS",
        "FUNCTION_SIGNATURE_EXT",
        "VARIABLE_OR_FUNCTION_CALL",
        "VARIABLE_DECLARATION",
        "FUNCTION_PARAMS_TAILS",
        "STATEMENT_VARIABLE",
        "INDEX",
        "FACTOR_VARIABLE",
        "ARRAY_SIZE",
        "INDICES",
        "FACTOR_FUNCTION_CALL",
        "FUNCTION_SIGNATURE",
        "FUNCTION_PARAMS_TAIL",
        "FUNCTION_CALL_PARAMS_TAILS",
        "OPTIONAL_INT",
        "COMPARE_OP",
        "FUNCTION_CALL_EXT",
        "STATEMENTS",
        "TYPE",
        "OPTIONAL_INHERITS",
        "FUNCTION_CALL_PARAMS_TAIL",
        "VARIABLE_FUNCTION_CALL",
        "MEMBER_DECLARATION",
        "RIGHT_REC_ARITH_EXPRESSION",
        "TYPE_NON_ID",
        "FACTOR",
        "PROGRAM",
        "STATEMENT_BLOCK",
        "SIGN",
        "FUNCTION_OR_VARIABLE_DECLARATION",
};