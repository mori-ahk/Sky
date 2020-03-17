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
#include "Nodes/MainFunc.h"

namespace AST {
    class ASTBuilder {
    public:

        ASTBuilder();

        ~ASTBuilder() = default;

        void handle(std::string &, std::string &);

        void push(std::string &, Token *);

        bool isIgnoreModeOn;

        void printStack();

        ASTNode *getRoot();

        void visualize();

    private:

        void createNode(std::string &);

        void insertLeftChild();

        void insertRightChild();

        void adoptChild();

        void constructListAndInsertAsChild();

        void removeSelfIfOnlyHasOneChild();

        static ASTNode *createCustomNode(std::string &, Token *token = nullptr);

        std::stack<ASTNode *> stack;
        std::stack<ASTNode *> testStack;
        ASTNode *root;
        Visualizer *visualizer;
    };
}

#endif //SKY_ASTBUILDER_H
