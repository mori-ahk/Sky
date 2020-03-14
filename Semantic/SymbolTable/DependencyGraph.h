//
// Created by Morteza Ahmadi on 2020-03-14.
//

#ifndef SKY_DEPENDENCYGRAPH_H
#define SKY_DEPENDENCYGRAPH_H

#include <vector>
#include <string>

class DependencyNode {
public:
    DependencyNode() = default;
    explicit DependencyNode(std::string name) { this->name = std::move(name); }
    ~DependencyNode() = default;
    inline void addToList(const std::string& _name) { adjList.push_back(_name); }
    inline std::string& getName() { return name; }

private:
    std::string name;
    std::vector<std::string> adjList;
};

class DependencyGraph {
public:
    DependencyGraph() = default;
    ~DependencyGraph() = default;
    std::vector<DependencyNode*> nodes = {};
};






#endif //SKY_DEPENDENCYGRAPH_H
