//
// Created by Morteza Ahmadi on 2020-03-14.
//

#ifndef SKY_DEPENDENCYGRAPH_H
#define SKY_DEPENDENCYGRAPH_H

#include <vector>
#include <string>
#include <unordered_set>
#include "SymbolTable.h"

typedef std::unordered_set<std::string>& StringSet;
class DependencyNode {
public:
    DependencyNode() = default;
    explicit DependencyNode(std::string name) { this->name = std::move(name); }
    ~DependencyNode() = default;
    inline void addToList(const std::string& _name) { adjList.push_back(_name); }
    inline std::string& getName() { return name; }
    inline std::vector<std::string>& getAdjList() { return adjList; }
    bool isVisited = false;
private:
    std::string name;
    std::vector<std::string> adjList;
};

class DependencyGraph {
public:
    DependencyGraph() = default;
    explicit DependencyGraph(Semantic::SymbolTable* symbolTable) { build(symbolTable); }
    ~DependencyGraph() = default;
    std::vector<DependencyNode*> nodes = {};
    std::pair<std::string, std::string> dfs(std::string&, StringSet, StringSet);
private:
    void build(Semantic::SymbolTable*);
    std::vector<std::string>& getAdjList(const std::string&);
};






#endif //SKY_DEPENDENCYGRAPH_H
