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
    currentVar = currentFunction->getVariable(node->getChild(0)->getName());
}

void CGV::visit(ClassDecls *node) {

}

void CGV::visit(ClassDecl *node) {

}

void CGV::visit(CompareOp *node) {

}

void CGV::visit(FuncBody *node) {
    //Skipping local scope node as it was processed by the
    //symbol table generator visitor

    //Calling statements node
    node->getChild(1)->accept(*this);
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
    currentFuncName = "main";
    currentNamespace = std::string();
    currentFunction = symbolTable->main;
    node->getChild(0)->accept(*this);
    writer->finish();
}

void CGV::visit(MultOp *node) {

}

void CGV::visit(Number *node) {

}

void CGV::visit(Program *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}

void CGV::visit(Read *node) {
    for (auto &child : node->getChildren()) {
        child->accept(*this);
        int offset = -(currentVar->getOffset() + currentVar->getSize());
        writer->comment("reading variable " + currentVar->getName());
        writer->OP("jl", "r15", "getint");
        writer->saveWord(offset, "r14", "r1");
    }
}

void CGV::visit(Return *node) {

}

void CGV::visit(Sign *node) {

}

void CGV::visit(Statements *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}

void CGV::visit(VarDecl *node) {

}

void CGV::visit(While *node) {

}

void CGV::visit(Write *node) {
    for (auto &child : node->getChildren()) {
        child->accept(*this);
        int offset = -(currentVar->getOffset() + currentVar->getSize());
        writer->comment("Writing variable " + currentVar->getName());
        writer->loadWord("r1", offset, "r14");
        writer->OP("jl", "r15", "putint");
    }
}

void CGV::visit(AST::ASTNode *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}

void CGV::write(std::string &fileName) {
    writer->write(fileName);
}



