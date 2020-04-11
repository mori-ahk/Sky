//
// Created by Morteza Ahmadi on 2020-04-10.
//

#include "CGV.h"

CGV::CGV(AST::ASTNode *root, Semantic::SymbolTable *_symbolTable) {
    this->symbolTable = _symbolTable;
    this->writer = new CodeWriter();
    root->getChild(0)->accept(*this);

}

void CGV::visit(AddOp *node) {

}

void CGV::visit(ArrayDim *node) {

}

void CGV::visit(AssignOp *node) {

}

void CGV::visit(Calls *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}
void CGV::visit(Call *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}

void CGV::visit(ClassDecls *node) {

}

void CGV::visit(ClassDecl *node) {

}

void CGV::visit(CompareOp *node) {

}

void CGV::visit(FuncBody *node) {

}

void CGV::visit(FuncCall *node) {

}

void CGV::visit(FuncDef *node) {

}

void CGV::visit(FuncDecl *node) {

}

void CGV::visit(FuncParams *node) {

}

void CGV::visit(If *node) {

}

void CGV::visit(Local *node) {

}

void CGV::visit(MainFunc *node) {

}

void CGV::visit(MultOp *node) {

}

void CGV::visit(Number *node) {

}

void CGV::visit(Program *node) {

}

void CGV::visit(Read *node) {
    for (auto &child : node->getChildren()) child->accept(*this);

}

void CGV::visit(Return *node) {

}

void CGV::visit(Sign *node) {

}

void CGV::visit(Statements *node) {

}

void CGV::visit(VarDecl *node) {

}

void CGV::visit(While *node) {

}

void CGV::visit(Write *node) {

}

void CGV::visit(AST::ASTNode *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}




