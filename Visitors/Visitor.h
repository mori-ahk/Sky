//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_VISITOR_H
#define SKY_VISITOR_H

#include "../Parser/AST/Nodes/ClassDecls.h"
#include "../Parser/AST/Nodes/ClassDecl.h"
#include "../Parser/AST/Nodes/FuncDecl.h"
#include "../Parser/AST/Nodes/FuncDef.h"
#include "../Parser/AST/Nodes/FuncBody.h"
#include "../Parser/AST/Nodes/FuncParams.h"
#include "../Parser/AST/Nodes/Local.h"
#include "../Parser/AST/Nodes/Program.h"
#include "../Parser/AST/Nodes/VarDecl.h"
#include "../Parser/AST/Nodes/ArrayDim.h"
#include "../Parser/AST/ASTNode.h"

class Visitor {
public:
    virtual void visit(ClassDecls* node) = 0;
    virtual void visit(ClassDecl* node) = 0;
    virtual void visit(FuncDecl* node) = 0;
    virtual void visit(FuncDef* node) = 0;
    virtual void visit(FuncBody* node) = 0;
    virtual void visit(FuncParams* node) = 0;
    virtual void visit(Local* node) = 0;
    virtual void visit(Program* node) = 0;
    virtual void visit(VarDecl* node) = 0;
    virtual void visit(ArrayDim* node) = 0;
    virtual void visit(ASTNode* node) = 0;
    ~Visitor();

};


#endif //SKY_VISITOR_H
