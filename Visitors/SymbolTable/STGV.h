//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_STGV_H
#define SKY_STGV_H


#include "../Visitor.h"
#include "../../Semantic/SymbolTable/SymbolTable.h"
#include "../../Semantic/Error/Detector.h"

class STGV : public Visitor {
public:
    explicit STGV(AST::ASTNode *root);

    void visit(AddOp *node) override;

    void visit(ArrayDim *node) override;

    void visit(AssignOp *node) override;

    void visit(Calls *node) override;

    void visit(Call *node) override;

    void visit(ClassDecls *node) override;

    void visit(ClassDecl *node) override;

    void visit(CompareOp *node) override;

    void visit(FuncBody *node) override;

    void visit(FuncCall *node) override;

    void visit(FuncDef *node) override;

    void visit(FuncDecl *node) override;

    void visit(FuncParams *node) override;

    void visit(If *node) override;

    void visit(Local *node) override;

    void visit(MainFunc *node) override;

    void visit(MultOp *node) override;

    void visit(Program *node) override;

    void visit(Read *node) override;

    void visit(Sign *node) override;

    void visit(Statements *node) override;

    void visit(VarDecl *node) override;

    void visit(While *node) override;

    void visit(Write *node) override;

    void visit(AST::ASTNode *node) override;

    Semantic::SymbolTable *symbolTable;
    Semantic::Detector *detector;

private:
    static Variable *createVar(AST::ASTNode *);
    Function *createTempFunction(AST::ASTNode *, std::string &, std::string &);
};


#endif //SKY_STGV_H
