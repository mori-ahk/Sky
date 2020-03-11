//
// Created by Morteza Ahmadi on 2020-02-19.
//

#ifndef SKY_VISUALIZER_H
#define SKY_VISUALIZER_H

#include <string>
#include "ASTNode.h"

class Visualizer {
public:
    void visualize(AST::ASTNode*);
    void generateDot(AST::ASTNode*);

    Visualizer();

private:
    std::string dotFileContent;
};


#endif //SKY_VISUALIZER_H
