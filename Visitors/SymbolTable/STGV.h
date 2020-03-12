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
    STGV(AST::ASTNode* root);
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
    Variable* createVar(AST::ASTNode*);
    void handleClassDuplicate(NamePair&);
    void handleClassOverloaded(NamePair&);
    void handleUndefinedClassFunctions(NamePair&);
    void handleFreeDuplicate(std::vector<std::string>&);
    void handleFreeOverloaded(std::vector<std::string>&);

};


#endif //SKY_STGV_H
