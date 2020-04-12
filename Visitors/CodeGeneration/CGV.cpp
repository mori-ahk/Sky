//
// Created by Morteza Ahmadi on 2020-04-10.
//

#include "CGV.h"

static int tag = 1;

CGV::CGV(AST::ASTNode *root, Semantic::SymbolTable *_symbolTable) {
    this->symbolTable = _symbolTable;
    this->writer = new CodeWriter();
    root->getChild(0)->accept(*this);
}

void CGV::visit(AddOp *node) {
    visitNodesAndUpdateFramePointer(node, false);

    writer->loadWord("r1", -4, "r12");
    writer->loadWord("r2", -12, "r12");

    writer->comment("Adding two number");
    if (node->getChild(1)->getName() == "+") writer->OP("add", "r1", "r1", "r2");
    else if (node->getChild(1)->getName() == "-") writer->OP("sub", "r1", "r1", "r2");
    else {
        writer->OP("cgt", "r1", "r1", "r0");
        writer->OP("cgt", "r2", "r2", "r0");
        writer->OP("or", "r1", "r1", "r2");
    }
    writer->saveWord(-4, "r12", "r1");
}

void CGV::visit(ArrayDim *node) {

}

void CGV::visit(AssignOp *node) {
    visitNodesAndUpdateFramePointer(node, true);

    writer->comment("Assigning variable");
    writer->loadWord("r1", -12, "r12");
    writer->loadWord("r2", -8, "r12");
    writer->saveWord(0, "r2", "r1");
}

void CGV::visit(Calls *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}

void CGV::visit(Call *node) {
    currentVar = currentFunction->getVariable(node->getChild(0)->getName());
    writer->comment("Setting the address and value of " + currentVar->getName());
    int offset = -(currentVar->getOffset() + currentVar->getSize());
    //load the value of node from memory
    writer->loadWord("r1", offset, "r14");
    writer->OP("addi", "r2", "r14", std::to_string(offset));
    writer->saveWord(-4, "r12", "r1");
    writer->saveWord(-8, "r12", "r2");
}

void CGV::visit(ClassDecls *node) {

}

void CGV::visit(ClassDecl *node) {

}

void CGV::visit(CompareOp *node) {
    visitNodesAndUpdateFramePointer(node, false);

    writer->comment("Comparing");
    auto compareNodeSymbol = node->getChild(1)->getName();
    if (compareNodeSymbol == "==") writer->OP("ceq", "r1", "r1", "r2");
    else if (compareNodeSymbol == "<>") writer->OP("cne", "r1", "r1", "r2");
    else if (compareNodeSymbol == "<=") writer->OP("cle", "r1", "r1", "r2");
    else if (compareNodeSymbol == ">=") writer->OP("cge", "r1", "r1", "r2");
    else if (compareNodeSymbol == ">") writer->OP("cgt", "r1", "r1", "r2");
    else writer->OP("clt", "r1", "r1", "r2");
    writer->saveWord(-4, "r12", "r1");
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
    writer->comment("If statement");
    std::string ifTag = generateTag("if");
    writer->tag(ifTag);
    //calling `cmp` node
    node->getChild(0)->accept(*this);

    writer->comment("check condition value");
    //if r1 is zero (condition is false), the program will jump to `else` tag
    writer->OP("bz", "r1", ifTag + "_else");

    //calling `then` node
    node->getChild(1)->accept(*this);
    writer->OP("j", ifTag + "_end");

    //calling `else` node
    writer->tag(ifTag + "_else");
    node->getChild(2)->accept(*this);
    writer->tag(ifTag + "_end");
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
    visitNodesAndUpdateFramePointer(node, false);
    writer->loadWord("r1", -4, "r12");
    writer->loadWord("r2", -12, "r12");

    writer->comment("multiplying two numbers");
    if (node->getChild(1)->getName() == "*") writer->OP("mul", "r1", "r1", "r2");
    else if (node->getChild(1)->getName() == "/") writer->OP("div", "r1", "r1", "r2");
    else {
        writer->OP("cgt", "r1", "r1", "r0");
        writer->OP("cgt", "r2", "r2", "r0");
        writer->OP("and", "r1", "r1", "r2");
    }
    writer->saveWord(-4, "r12", "r1");
}

void CGV::visit(Number *node) {
    writer->comment("Saving number " + node->getChild(0)->getName());
    writer->OP("addi", "r1", "r0", node->getChild(0)->getName());
    writer->saveWord(-4, "r12", "r1");
}

void CGV::visit(Program *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}

void CGV::visit(Read *node) {
    for (auto &child : node->getChildren()) {
        child->accept(*this);
        writer->comment("reading variable " + currentVar->getName());
        writer->OP("jl", "r15", "getint");
        writer->loadWord("r2", -8, "r12");
        writer->saveWord(0, "r2", "r1");
    }
}

void CGV::visit(Return *node) {

}

void CGV::visit(Sign *node) {

}

void CGV::visit(Statements *node) {
    for (auto &child : node->getChildren()) {
        writer->comment("Set frame pointer");
        writer->OP("subi", "r12", "r14", std::to_string(currentFunction->getSize()));
        child->accept(*this);
    }
}

void CGV::visit(VarDecl *node) {

}

void CGV::visit(While *node) {

}

void CGV::visit(Write *node) {
    for (auto &child : node->getChildren()) {
        child->accept(*this);
        writer->comment("Writing variable " + currentVar->getName());
        writer->loadWord("r1", -4, "r12");
        writer->OP("jl", "r15", "putint");
    }
}

void CGV::visit(AST::ASTNode *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}

void CGV::write(std::string &fileName) {
    writer->write(fileName);
}

Variable *CGV::getLiteralVariableWithTag() {
    std::string tagString = "literal_" + std::to_string(tag++);
    return currentFunction->getVariable(tagString);
}

std::string CGV::generateTag(const std::string &label) {
    std::string tagString = currentFunction->getName() + "_" + std::to_string(tag++) + "_" + label;
    return tagString;
}

void CGV::visitNodesAndUpdateFramePointer(AST::ASTNode *node, bool isBinary) {
    node->getChild(0)->accept(*this);
    writer->comment("moving frame pointer 8 byte up");
    writer->OP("addi", "r12", "r12", std::to_string(-8));
    node->getChild(isBinary ? 1 : 2)->accept(*this);
    writer->comment("set the frame pointer at its initial position");
    writer->OP("addi", "r12", "r12", std::to_string(8));
}