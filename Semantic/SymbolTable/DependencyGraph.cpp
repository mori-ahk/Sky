//
// Created by Morteza Ahmadi on 2020-03-15.
//

#include "DependencyGraph.h"


void DependencyGraph::build(Semantic::SymbolTable *symbolTable) {
    for (const auto &_class : symbolTable->classes) {
        auto node = new DependencyNode(_class.first);
        for (const std::string &inherit : _class.second->getInherits()) {
            try {
                symbolTable->getClass(inherit);
                node->addToList(inherit);
            }
            catch (Semantic::Err::UndeclaredClass &undeclaredClass) { throw; }
        }
        for (const auto &_variable : _class.second->getVariables()) {
            std::string localVarType = _variable.second->getType();
            if (localVarType != "float" && localVarType != "integer" && localVarType != "integer[][]" && localVarType != "float[][]" && localVarType != "integer[]" && localVarType != "float[]") {
                try {
                    symbolTable->getClass(localVarType);
                    node->addToList(localVarType);
                } catch (Semantic::Err::UndeclaredClass &undeclaredClass) { throw; }
            }
        }
        nodes.push_back(node);
    }
}

std::vector<std::string> &DependencyGraph::getAdjList(const std::string &className) {
    for (const auto &node : nodes) {
        if (node->getName() == className) return node->getAdjList();
    }
}

std::pair<std::string, std::string>
DependencyGraph::dfs(std::string &className, StringSet visiting, StringSet visited) {
    visiting.insert(className);
    for (auto &dependency : getAdjList(className)) {
        if (visited.find(dependency) != visited.end()) continue;
        if (visiting.find(dependency) != visiting.end()) return std::make_pair(className, dependency);
        else {
            auto pair = dfs(dependency, visiting, visited);
            if (!pair.first.empty() && !pair.second.empty()) return pair;
        }
    }
    return std::make_pair("", "");
}