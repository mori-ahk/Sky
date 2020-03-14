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
    explicit STGV(AST::ASTNode* root);
    void visit(ClassDecls* node) override;
    void visit(ClassDecl* node) override;
    void visit(FuncDecl* node) override;
    void visit(FuncDef* node) override;
    void visit(FuncBody* node) override;
    void visit(FuncParams* node) override;
    void visit(Local* node) override;
    void visit(Program* node) override;
    void visit(VarDecl* node) override;
    void visit(ArrayDim* node) override;
    void visit(MainFunc* node) override;
    void visit(AST::ASTNode* node) override;

    Semantic::SymbolTable* symbolTable;
    Semantic::Detector* detector;
private:
    static Variable* createVar(AST::ASTNode*);

};


#endif //SKY_STGV_H
