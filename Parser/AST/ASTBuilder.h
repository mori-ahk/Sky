//
// Created by Morteza Ahmadi on 2020-02-19.
//

#ifndef SKY_ASTBUILDER_H
#define SKY_ASTBUILDER_H

#include <stack>
#include <unordered_map>
#include "ASTNode.h"
#include "Visualizer.h"
#include "Nodes/ClassDecls.h"
#include "Nodes/ClassDecl.h"
#include "Nodes/FuncDecl.h"
#include "Nodes/FuncDef.h"
#include "Nodes/FuncBody.h"
#include "Nodes/FuncParams.h"
#include "Nodes/Local.h"
#include "Nodes/Program.h"
#include "Nodes/VarDecl.h"
#include "Nodes/ArrayDim.h"
class ASTBuilder {
public:

    ASTBuilder();
    ~ASTBuilder();

    void handle(std::string&, std::string&);
    void push(std::string&);
    bool isIgnoreModeOn;
    void printStack();
    ASTNode* getRoot();
    void visualize();

private:

    void createNode(std::string&);
    void insertLeftChild();
    void insertRightChild();
    void adoptChild();
    void constructListAndInsertAsChild();
    void removeSelfIfOnlyHasOneChild();

    std::stack<ASTNode*> stack;
    std::stack<ASTNode*> testStack;
    ASTNode* root;
    Visualizer* visualizer;
};

const std::unordered_map<std::string, ASTNode*> NODES = {
        {"CLASSDECLARATIONS", new ClassDecls("classes")},
        {"class", new ClassDecl("class")},
        {"FUNCTIONDECLARATION", new FuncDecl("func_decl")},
        {"FUNCTIONBODY", new FuncBody("func_body")},
        {"FUNCTIONPARAMS", new FuncParams("params")},
        {"FUNCTIONDEFINITION", new FuncDef("func_def")},
        {"ARRAYDIMENSIONS", new ArrayDim("Arr_dim")},
        {"LOCALSCOPE", new Local("local_scope")},
        {"PROGRAM", new Program("Program")},
        {"VARIABLEDECLARATION", new VarDecl("var_decl")}
};

#endif //SKY_ASTBUILDER_H
