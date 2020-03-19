//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_TCV_H
#define SKY_TCV_H


#include "../Visitor.h"
#include "../../Semantic/SymbolTable/SymbolTable.h"
#include "../SymbolTable/STGV.h"

class TCV : public Visitor {
public:
    TCV(AST::ASTNode *, STGV *);

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

    void visit(Return *node) override;

    void visit(Sign *node) override;

    void visit(Statements *node) override;

    void visit(VarDecl *node) override;

    void visit(While *node) override;

    void visit(Write *node) override;

    void visit(AST::ASTNode *node) override;

    inline std::vector<std::string> getErrors() { return detector->getErrors(); }

private:
    static bool isMatchType(std::string &, std::string &);

    static bool isCalledOnObject(AST::ASTNode *);

    static bool isFuncCall(AST::ASTNode *);

    static bool isCalledOnFunction(AST::ASTNode *);

    static std::vector<std::string> getParamsType(AST::ASTNode *);

    void checkIfFreeFunctionCalledWithRightArgument(std::string &, AST::ASTNode *);

    void checkIfClassFunctionCalledWithRightAccess(std::string &, AST::ASTNode *, bool isCalledOnFunction = false);

    void checkIfClassVariableCalledWithRightAccess(std::string &, AST::ASTNode *);

    STGV *stgv;
    Function *tempFunction;

    static Function *getRightFunction(std::vector<Function *>, AST::ASTNode *);

    Semantic::Detector *detector;

    bool isGoodToGo = true;

    std::string returnType;
    std::string currentFuncName;
    std::string currentNamespace;

    int position;


};


#endif //SKY_TCV_H
