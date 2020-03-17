//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_VISITOR_H
#define SKY_VISITOR_H

#include "../Parser/AST/ASTBuilder.h"

class Visitor {
public:

    virtual void visit(AddOp *node) = 0;

    virtual void visit(ArrayDim *node) = 0;

    virtual void visit(AssignOp *node) = 0;

    virtual void visit(Calls *node) = 0;

    virtual void visit(Call *node) = 0;

    virtual void visit(ClassDecls *node) = 0;

    virtual void visit(ClassDecl *node) = 0;

    virtual void visit(CompareOp *node) = 0;

    virtual void visit(FuncBody *node) = 0;

    virtual void visit(FuncCall *node) = 0;

    virtual void visit(FuncDef *node) = 0;

    virtual void visit(FuncDecl *node) = 0;

    virtual void visit(FuncParams *node) = 0;

    virtual void visit(If *node) = 0;

    virtual void visit(Local *node) = 0;

    virtual void visit(MainFunc *node) = 0;

    virtual void visit(MultOp *node) = 0;

    virtual void visit(Program *node) = 0;

    virtual void visit(Read *node) = 0;

    virtual void visit(Sign *node) = 0;

    virtual void visit(Statements *node) = 0;

    virtual void visit(VarDecl *node) = 0;

    virtual void visit(While *node) = 0;

    virtual void visit(Write *node) = 0;

    virtual void visit(AST::ASTNode *node) = 0;


    virtual ~Visitor() = default;
};


#endif //SKY_VISITOR_H
