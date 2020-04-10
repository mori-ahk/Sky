//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "STGV.h"
#include <iostream>
#include <vector>


STGV::STGV(AST::ASTNode *root) {
    this->symbolTable = new Semantic::SymbolTable();
    this->detector = new Semantic::Detector(this->symbolTable);
    root->getChild(0)->accept(*this);
}

void STGV::visit(Program *node) {
    for (auto child : node->getChildren()) child->accept(*this);

    //detect for errors
    detector->detect();
}

void STGV::visit(FuncBody *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}

void STGV::visit(FuncDef *node) {

    AST::ASTNode *signature = node->getChild(0);
    auto isClassFunc = [&signature]() {
        return signature->getChildren().size() == 4;
    };

    //if the function belongs to a class and has a namespace;
    if (isClassFunc()) currentNamespace = signature->getChild(0)->getName();
    else currentNamespace = std::string();

    if (isClassFunc()) currentFuncName = signature->getChild(1)->getName();
    else currentFuncName = signature->getChild(0)->getName();

    std::string returnType = isClassFunc() ? signature->getChild(3)->getName() : signature->getChild(2)->getName();
    currentFunction = createTempFunction(node, currentFuncName, returnType);

    //check if the class function signature and defined function signature match.
    if (isClassFunc()) {
        try {
            auto classFunction = symbolTable->getClass(currentNamespace)->getFunction(currentFuncName, currentFunction);
            classFunction->isDefined = true;
        } catch (Semantic::Error &error) {
            detector->addError(error.what());
            return;
        }
    }

    //iterating on local vars
    for (auto &child : node->getChild(1)->getChildren()) child->accept(*this);

    if (!isClassFunc()) symbolTable->addFunction(currentFuncName, currentFunction);
}

void STGV::visit(VarDecl *node) {
    Variable *variable = createVar(node);
    variable->setKind(Enums::Kind::VAR);
    try { symbolTable->classes.at(currentNamespace)->addVariable(variable->getName(), variable); }
    catch (Semantic::Error &error) {
        detector->addError(error.what());
        return;
    }
}

void STGV::visit(FuncDecl *node) {
    std::string visibilityString = node->getChild(0)->getName();
    Enums::Visibility visibility =
            visibilityString == "private" ? Enums::Visibility::PRIVATE : Enums::Visibility::PUBLIC;
    currentFuncName = node->getChild(1)->getName();
    std::string returnType = node->getChild(3)->getName();
    Function *function = new Function(visibility, currentFuncName, returnType, {}, {},
                                      node->getChild(1)->getLineNumber());

    symbolTable->getClass(currentNamespace)->addFunction(currentFuncName, function);

    node->getChild(2)->accept(*this);
}

void STGV::visit(ClassDecl *node) {
    //Creating a class entry
    currentNamespace = node->getChild(0)->getName();
    std::vector<std::string> inherits;

    //constructing a string indicating all the parent class
    for (auto &child : node->getChild(1)->getChildren()) {
        inherits.push_back(child->getName());
    }

    Class *classEntry = new Class(currentNamespace, currentNamespace, inherits, node->getChild(0)->getLineNumber());
    try { symbolTable->addClass(currentNamespace, classEntry); }
    catch (Semantic::Error &error) { detector->addError(error.what()); }

    for (auto &child : node->getChild(2)->getChildren()) child->accept(*this);
}

void STGV::visit(ClassDecls *node) {
    for (auto &child : node->getChildren()) child->accept(*this);
}

void STGV::visit(FuncParams *node) {
    for (auto &child: node->getChildren()) {
        Variable *variable = createVar(child);
        try {
            symbolTable->classes.at(currentNamespace)->getFunctions().at(currentFuncName).back()->addParam(variable);
        } catch (Semantic::Error &error) { detector->addError(error.what()); }
    }
}

void STGV::visit(Local *node) {
    for (auto &localVar : node->getChildren()) {
        Variable *variable = createVar(localVar);
        variable->setKind(Enums::Kind::VAR);
        //throw a semantic error if `variable` is a duplicate variable in the `function`'s local scope.
        try { currentFunction->addVariable(variable); }
        catch (Semantic::Error &error) { detector->addError(error.what()); }

        //fetching the class that this function corresponds to and add local variable to its scope
        if (!currentNamespace.empty()) {
            auto classFunction = symbolTable->classes.at(currentNamespace)->getFunction(currentFuncName,
                                                                                        currentFunction);
            classFunction->addVariable(variable);
        }
    }
}

void STGV::visit(MainFunc *node) {
    currentFuncName = "main";
    currentNamespace = std::string();
    AST::ASTNode *funcBody = node->getChild(0);
    AST::ASTNode *localVars = funcBody->getChild(0);
    symbolTable->main->setPosition(node->getLineNumber());

    for (auto &var : localVars->getChildren()) {
        Variable *variable = createVar(var);
        try { symbolTable->main->addVariable(variable); }
        catch (Semantic::Error &error) { detector->addError(error.what()); }
    }

    funcBody->getChild(1)->accept(*this);
}

void STGV::visit(AST::ASTNode *node) {
    for (auto &child : node->getChildren()) {
        child->accept(*this);
    }
}

Variable *STGV::createVar(AST::ASTNode *node) {
    int startIndex = node->getChildren().size() == 4 ? 1 : 0;
    Enums::Visibility visibility = Enums::Visibility::PRIVATE;

    if (node->getChildren().size() == 4) {
        std::string visibilityString = node->getChildren().at(0)->getName();
        visibility = visibilityString == "private" ? Enums::Visibility::PRIVATE : Enums::Visibility::PUBLIC;
    }

    std::string type = node->getChild(startIndex++)->getName();

    std::string varName = node->getChild(startIndex)->getName();
    int dimensions = 0;
    std::vector<int> arraySize;
    AST::ASTNode *dimNodeToIterate = node->getChildren().size() == 4 ? node->getChild(3) : node->getChild(2);
    for (auto &arrayDimensionChild: dimNodeToIterate->getChildren()) {
        int size;
        type += "[]";
        dimensions++;
        try {
            size = std::stoi(arrayDimensionChild->getChild(0)->getName());
            arraySize.push_back(size);
        } catch (std::exception &ignored) {}
    }

    return new Variable(visibility, varName, type, dimensions, node->getChild(startIndex)->getLineNumber(), arraySize);
}

Function *STGV::createTempFunction(AST::ASTNode *node, std::string &funcName, std::string &returnType) {
    AST::ASTNode *signature = node->getChild(0);
    auto isClassFunc = [&signature]() {
        return signature->getChildren().size() == 4;
    };

    Function *function = new Function(Enums::Visibility::PUBLIC, funcName, returnType, {}, {},
                                      signature->getChild(0)->getLineNumber());

    //iterating on params
    AST::ASTNode *params = isClassFunc() ? signature->getChild(2) : signature->getChild(1);

    for (auto &param: params->getChildren()) {
        Variable *variable = createVar(param);

        //throw a semantic error if `variable` is a duplicate param in the `function`
        try { function->addParam(variable); }
        catch (Semantic::Error &error) { detector->addError(error.what()); }
    }

    return function;
}

//Symbol table visitors do not need to implement these functions
//but they have to have an implementation to make the compiler happy

void STGV::visit(ArrayDim *node) {}

void STGV::visit(AddOp *node) {}

void STGV::visit(AssignOp *node) {
    for(auto &child : node->getChildren()) child->accept(*this);
}

void STGV::visit(Calls *node) {
    for(auto &child : node->getChildren()) child->accept(*this);
}

void STGV::visit(Call *node) {
    for(auto &child : node->getChildren()) child->accept(*this);
}

void STGV::visit(CompareOp *node) {}

void STGV::visit(FuncCall *node) {}

void STGV::visit(If *node) {}

void STGV::visit(MultOp *node) {}

void STGV::visit(Read *node) {}

void STGV::visit(Return *node) {}

void STGV::visit(Sign *node) {}

void STGV::visit(Statements *node) {
    for(auto &child : node->getChildren()) child->accept(*this);
}

void STGV::visit(While *node) {}

void STGV::visit(Write *node) {}

void STGV::visit(Number *node) {
    std::cout << "Hello" << std::endl;
}
