//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "STGV.h"
#include <iostream>
#include "../../SymbolTable/Entries/Class.h"
STGV::STGV(ASTNode* root) {
    this->symbolTable = new SymbolTable();
    root->getChildren().at(0)->accept(*this);
}
void STGV::visit(Program *node) {
    for(auto child : node->getChildren()) {
        child->accept(*this);
    }
}

void STGV::visit(Local *node) {

}

void STGV::visit(FuncDef *node) {

    std::string namespaceName = "";
    //iterating on signature node's children
    auto signature = node->getChildren().at(0);

    //if the function belongs to a class and has a namespace;
    if (signature->getChildren().size() == 4) namespaceName = signature->getChildren().at(0)->getName();

    std::string funcName = signature->getChildren().size() == 4 ? signature->getChildren().at(1)->getName() : signature->getChildren().at(1)->getName();
    std::string returnType = signature->getChildren().at(2)->getName();
    Function* function = new Function(Visibility::PUBLIC, funcName, returnType, {}, {});
    if (signature->getChildren().size() == 3) symbolTable->freeFunctions[funcName] = function;
    //iterating on params node's children
    auto params = signature->getChildren().at(1);

    for (auto param: params->getChildren()) {
        std::string visibilityString = param->getChildren().at(0)->getName();
        Visibility visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
        std::string type = param->getChildren().at(1)->getName();
        std::string varName = param->getChildren().at(2)->getName();
        std::vector<int> dimensions;
        for (auto arrayDimensionChild: param->getChildren().at(3)->getChildren()) {
            if (isdigit(arrayDimensionChild->getChildren().at(0)->getName()[0])) {
                int dimension = std::stoi(arrayDimensionChild->getChildren().at(0)->getName());
                dimensions.push_back(dimension);
            }
        }

        Variable *variable = new Variable(visibility, type, varName, dimensions);
        function->addParam(variable);
    }

    auto funcBody = node->getChildren().at(1);

    //iterating on func_body node's children
    for (auto child : funcBody->getChildren().at(0)->getChildren()) {
        std::string visibilityString = child->getChildren().at(0)->getName();
        Visibility  visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
        std::string type = child->getChildren().at(1)->getName();
        std::string varName = child->getChildren().at(2)->getName();
        std::vector<int> dimensions;

        //iterating on dimension array
        for (auto dim: child->getChildren().at(2)->getChildren()) {
            if (isdigit(dim->getChildren().at(0)->getName()[0])) {
                int dimension = std::stoi(dim->getChildren().at(0)->getName());
                dimensions.push_back(dimension);
            }
        }

        Variable* variable = new Variable(visibility, type, varName, dimensions);
        function->addVariable(variable);

        //fetching the class that this function corresponds to and add local variable to its scope
        if (!namespaceName.empty()) symbolTable->classes.at(namespaceName)->getFunctions().at(funcName)->addVariable(variable);
    }
}

void STGV::visit(VarDecl *node) {
    std::string visibilityString = node->getChildren().at(0)->getName();
    Visibility  visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    std::string type = node->getChildren().at(1)->getName();
    std::string varName = node->getChildren().at(2)->getName();
    std::vector<int> dimensions;
    for (auto child: node->getChildren().at(3)->getChildren()) {
        if (isdigit(child->getChildren().at(0)->getName()[0])) {
            int dimension = std::stoi(child->getChildren().at(0)->getName());
            dimensions.push_back(dimension);
        }
    }

    Variable* variable = new Variable(visibility, type, varName, dimensions);
    symbolTable->classes.at(node->getParent()->getName())->addVariable(varName, variable);

}

void STGV::visit(ArrayDim *node) {

}

void STGV::visit(FuncBody *node) {

}

void STGV::visit(FuncDecl *node) {
    std::string visibilityString = node->getChildren().at(0)->getName();
    Visibility  visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    std::string funcName =  node->getChildren().at(1)->getName();
    std::string returnType = node->getChildren().at(3)->getName();
    Function* function = new Function(visibility, funcName, returnType, {}, {});
    symbolTable->classes.at(node->getParent()->getName())->addFunction(funcName, function);

    //setting the parent of `funcName` node to `className` node
    node->getChildren().at(1)->setParent(node->getParent());
    //setting the parent of `params` node to `funcName` node
    node->getChildren().at(2)->setParent(node->getChildren().at(1));

    node->getChildren().at(2)->accept(*this);
}

void STGV::visit(ClassDecl *node) {
    //Creating a class entry
    std::string className = node->getChildren().at(0)->getName();
    std::string inherits = "";
    for(auto child : node->getChildren().at(1)->getChildren()) {
        inherits += child->getName() + " ";
    }

    Class* classEntry = new Class(className, className, inherits);
    symbolTable->classes[className] = classEntry;

    for(auto child : node->getChildren().at(2)->getChildren()) {

       //setting the parent of each member in `MEMBERDECLARATIONS` to `className` node
       child->setParent(node->getChildren().at(0));
       child->accept(*this);
    }
}

void STGV::visit(ClassDecls *node) {
    for(auto child : node->getChildren()) {
        child->accept(*this);
    }
}

void STGV::visit(FuncParams *node) {
    for(auto child: node->getChildren()) {
        //setting the parent of each `param` node to `funcName` node
        child->setParent(node->getParent());

        std::string visibilityString = child->getChildren().at(0)->getName();
        Visibility  visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
        std::string type = child->getChildren().at(1)->getName();
        std::string varName = child->getChildren().at(2)->getName();
        std::vector<int> dimensions;

        for (auto arrayDimensionChild: child->getChildren().at(3)->getChildren()) {
            if (isdigit(arrayDimensionChild->getChildren().at(0)->getName()[0])) {
                int dimension = std::stoi(arrayDimensionChild->getChildren().at(0)->getName());
                dimensions.push_back(dimension);
            }
        }

        Variable* variable = new Variable(visibility, type, varName, dimensions);
        symbolTable->classes.at(node->getParent()->getParent()->getName())->getFunctions().at(node->getParent()->getName())->addParam(variable);
    }
}

void STGV::visit(ASTNode *node) {
    for(auto child : node->getChildren()) {
        child->setParent(node->getParent());
        child->accept(*this);

    }
}
