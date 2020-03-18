//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "TCV.h"
#include "../SymbolTable/STGV.h"

TCV::TCV(AST::ASTNode *root, Semantic::SymbolTable *_symbolTable) {
    this->symbolTable = _symbolTable;
    root->getChild(0)->accept(*this);
}

void TCV::visit(FuncDef *node) {
    AST::ASTNode *signature = node->getChild(0);

    auto isClassFunc = [&node]() {
        return node->getChildren().size() == 4;
    };

    std::string _returnType = isClassFunc() ? signature->getChild(3)->getName() : signature->getChild(2)->getName();
    currentFuncName = isClassFunc() ? signature->getChild(1)->getName() : signature->getChild(0)->getName();
    currentNamespace = isClassFunc() ? signature->getChild(0)->getName() : std::string();

    tempFunction = new Function(Visibility::PUBLIC, currentFuncName, _returnType, {}, {});

    //iterating on params
    AST::ASTNode *params = isClassFunc() ? signature->getChild(2) : signature->getChild(1);

    for (auto &param: params->getChildren()) {
        Variable *variable = createVar(param);
        tempFunction->addParam(variable);
    }
}

void TCV::visit(AddOp *node) {

}

void TCV::visit(AssignOp *node) {
    node->getChild(0)->accept(*this);
    if (!isGoodToGo) return;
    std::string lhsType = returnType;
    node->getChild(1)->accept(*this);
    std::string rhsType = returnType;
    if (!isMatchType(lhsType, rhsType)) {
        isGoodToGo = false;
        std::cerr << "Unmatched type at line " << position << std::endl;
    }
}


void TCV::visit(Calls *node) {
    for (const auto &child: node->getChildren()) {
        child->setParent(node);
        if (!isGoodToGo) return;
        child->accept(*this);
    }
}

void TCV::visit(Call *node) {
    auto varName = node->getChild(0)->getName();
    Variable *variable;
    try {
        if (currentNamespace.empty()) {
            if (currentFuncName == "main")
                variable = symbolTable->main->getVariable(varName);
            else
                variable = symbolTable->getFreeFunction(currentFuncName, tempFunction)->getVariable(varName);
        } else
            variable = symbolTable->classes.at(currentNamespace)->getFunction(currentFuncName,
                                                                              tempFunction)->getVariable(varName);
        returnType = variable->getType();
        position = node->getChild(0)->getLineNumber();
    } catch (Semantic::Err::UndeclaredLocalVariable &undeclaredLocalVariable) {
        std::cerr << undeclaredLocalVariable.what() << std::endl;
        isGoodToGo = false;
        return;
    } catch (Semantic::Err::UndeclaredFunction &undeclaredFunction) {
        std::cerr << undeclaredFunction.what() << std::endl;
        isGoodToGo = false;
        return;
    }


    if (variable->getType() != "integer" && variable->getType() != "float" &&
        node->getParent()->getChildren().size() > 1) {

    } else {

    }
}

void TCV::visit(CompareOp *node) {

}

void TCV::visit(FuncCall *node) {

}


void TCV::visit(If *node) {

}

void TCV::visit(MainFunc *node) {
    currentFuncName = "main";
    for (const auto &child : node->getChildren())
        child->accept(*this);
}

void TCV::visit(MultOp *node) {

}

void TCV::visit(Program *node) {
    for (const auto &child : node->getChildren()) {
        if (!isGoodToGo) return;
        child->accept(*this);
    }
}

void TCV::visit(Read *node) {

}

void TCV::visit(Sign *node) {

}

void TCV::visit(Statements *node) {
    for (const auto &child : node->getChildren()) {
        if (!isGoodToGo) return;
        child->accept(*this);
    }
}

void TCV::visit(While *node) {

}

void TCV::visit(Write *node) {

}

void TCV::visit(AST::ASTNode *node) {
    returnType = node->getType();
    for (const auto &child: node->getChildren())
        child->accept(*this);
}

Variable *TCV::createVar(AST::ASTNode *node) {
    int startIndex = node->getChildren().size() == 4 ? 1 : 0;
    Visibility visibility = Visibility::PRIVATE;

    if (node->getChildren().size() == 4) {
        std::string visibilityString = node->getChildren().at(0)->getName();
        visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    }

    std::string type = node->getChild(startIndex++)->getName();
    std::string varName = node->getChild(startIndex)->getName();
    std::vector<int> dimensions;

    AST::ASTNode *dimNodeToIterate = node->getChildren().size() == 4 ? node->getChild(3) : node->getChild(2);
    for (auto &arrayDimensionChild: dimNodeToIterate->getChildren()) {
        try {
            int dimension = std::stoi(arrayDimensionChild->getChild(0)->getName());
            dimensions.push_back(dimension);
        } catch (const std::invalid_argument &invalid_argument) {}
    }
    return new Variable(visibility, varName, type, dimensions);
}

bool TCV::isMatchType(std::string &lhs, std::string &rhs) {
    if ((rhs == "integer" && lhs == "intnum") || (rhs == "intnum" && lhs == "integer")) return true;
    else if ((rhs == "float" && lhs == "floatnum") || (rhs == "floatnum" && lhs == "float")) return true;
    else if (rhs == lhs) return true;
    else return false;
}
//Type checking visitors do not need to implement these functions
//but they have to have an implementation to make the compiler happy
void TCV::visit(ArrayDim *node) {}

void TCV::visit(ClassDecls *node) {}

void TCV::visit(ClassDecl *node) {}

void TCV::visit(FuncBody *node) {
    //Call statements node because variable declarations node has been taken care of in symbol table generation phase.
    node->getChild(1)->accept(*this);
}

void TCV::visit(FuncDecl *node) {}

void TCV::visit(FuncParams *node) {}

void TCV::visit(VarDecl *node) {}

void TCV::visit(Local *node) {}