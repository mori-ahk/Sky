//
// Created by Morteza Ahmadi on 2020-02-07.
//

#ifndef SKY_RULE_H
#define SKY_RULE_H

#include <string>
#include <vector>
#include <unordered_set>
#include "../Lexer/Token.h"

namespace Language {
    class Rule {
    public:
        explicit Rule(std::string);

        ~Rule() = default;

        std::unordered_set<std::string> &getFirst();

        std::unordered_set<std::string> &getFollow();

        std::vector<std::vector<std::string>> &getRHS();

        std::string &getName();

        static const std::unordered_map<std::string, std::string> &getTerminals();

        static bool isTerminal(std::string &);

        void addToRHS(std::vector<std::string>);

        void addToFirst(std::string);

        void addToFollow(std::string);

        void addToWatchList(Rule *);

        void clearWatchList();

        int indexOf(std::vector<std::string>, std::string);

        bool isTerminal();

        bool isNullable();

        bool doesBelongToFirst(Token *);

        bool doesBelongToFollow(Token *);

        bool visited;

    private:

        std::string name;
        std::unordered_set<std::string> first;
        std::unordered_set<std::string> follow;
        std::vector<std::vector<std::string>> RHS;
        std::vector<Rule *> watchlist;

        void callWatchlist(bool);
    };
}
static const std::unordered_map<std::string, std::string> TERMINALS = {
        {"id",         "id"},
        {"if",         "if"},
        {"then",       "then"},
        {"else",       "else"},
        {"integer",    "__Integer"},
        {"float",      "__Float"},
        {"intnum",     "Integer"},
        {"floatnum",   "Float"},
        {"while",      "while"},
        {"class",      "class"},
        {"do",         "do"},
        {"end",        "end"},
        {"public",     "public"},
        {"private",    "private"},
        {"or",         "or"},
        {"and",        "and"},
        {"not",        "not"},
        {"read",       "read"},
        {"write",      "write"},
        {"return",     "return"},
        {"main",       "main"},
        {"inherits",   "inherits"},
        {"local",      "local"},
        {"void",       "void"},
        {"eq",         "=="},
        {"noteq",      "<>"},
        {"less",       "<"},
        {"greater",    ">"},
        {"lesseq",     "<="},
        {"greatereq",  ">="},
        {"plus",       "+"},
        {"minus",      "-"},
        {"mult",       "*"},
        {"div",        "/"},
        {"equal",      "="},
        {"lpar",       "("},
        {"rpar",       ")"},
        {"lcurbr",     "{"},
        {"rcurbr",     "}"},
        {"lsqbr",      "["},
        {"rsqbr",      "]"},
        {"semi",       ";"},
        {"comma",      ","},
        {"dot",        "."},
        {"colon",      ":"},
        {"coloncolon", "::"},
};

#endif //SKY_RULE_H
