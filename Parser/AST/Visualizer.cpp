//
// Created by Morteza Ahmadi on 2020-02-19.
//

#include "Visualizer.h"
#include <iostream>
#include <fstream>

void Visualizer::visualize(ASTNode * root) {
    dotFileContent += "digraph AST {\n";
    generateDot(root);
    dotFileContent += "}";
    std::ofstream stream("TreeContent.gv");
    stream << dotFileContent;
}

void Visualizer::generateDot(ASTNode* root) {
    dotFileContent += std::to_string(root->getUniqueID()) + " [label=\"" + root->getName() + "\"];\n";
    if (root->getChildren().size() == 0) return;
    for (auto& child: root->getChildren()) {
        dotFileContent += std::to_string(root->getUniqueID()) + " -> " + std::to_string(child->getUniqueID()) + ";\n";
        generateDot(child);
    }
}

Visualizer::Visualizer() {
    dotFileContent = "";
}
