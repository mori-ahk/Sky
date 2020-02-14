//
// Created by Morteza Ahmadi on 2020-02-07.
//

#ifndef SKY_RULE_H
#define SKY_RULE_H

#include <string>
#include <vector>
#include <unordered_set>
#include "../Lexer/Token.h"

class Rule {
public:

    Rule(std::unordered_set<std::string>, std::unordered_set<std::string>, std::vector<std::string>, bool nullable = false);
    Rule(std::string);
    ~Rule();

    std::unordered_set<std::string>& getFirst();
    std::unordered_set<std::string>& getFollow();
    std::vector<std::string>& getRHS();
    std::vector<std::string>& getSeparatedRHS();
    std::string getName();

    void addToRHS(std::string);
    void addToFirst(std::string);
    void addToFollow(std::string);
    void seperateRHS(std::string&, bool isParsing = false);


    bool isTerminal();
    static bool isTerminal(std::string&);
    bool isNullable();
    bool doesBelongToFirst(Token*);
    bool doesBelongToFollow(Token*);

    bool visited;
    bool nullable;

private:

    bool doesContainWhitespace(std::string&);
    std::string name;
    std::unordered_set<std::string> first;
    std::unordered_set<std::string> follow;
    std::vector<std::string> RHS;
    std::vector<std::string> separatedRHS;
};

const std::unordered_map<std::string, std::string> TERMINALS = {
        {"id","id"},
        {"if","if"},
        {"then","then"},
        {"else","else"},
        {"integer","__Integer"},
        {"float","__Float"},
        {"intnum","Integer"},
        {"floatnum","Float"},
        {"while","while"},
        {"class","class"},
        {"do","do"},
        {"end","end"},
        {"public","public"},
        {"private","private"},
        {"or","or"},
        {"and","and"},
        {"not","not"},
        {"read","read"},
        {"write","write"},
        {"return","return"},
        {"main","main"},
        {"inherits","inherits"},
        {"local","local"},
        {"void","void"},
        {"eq","=="},
        {"noteq","<>"},
        {"less","<"},
        {"greater",">"},
        {"lesseq","<="},
        {"greatereq",">="},
        {"plus","+"},
        {"minus","-"},
        {"mult","*"},
        {"div","/"},
        {"equal","="},
        {"lpar","("},
        {"rpar",")"},
        {"lcurbr","{"},
        {"rcurbr","}"},
        {"lsqbr","["},
        {"rsqbr","]"},
        {"semi",";"},
        {"comma",","},
        {"dot","."},
        {"colon",":"},
        {"coloncolon","::"},
};

#endif //SKY_RULE_H
