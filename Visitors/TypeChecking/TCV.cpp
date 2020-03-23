//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "TCV.h"
#include "../SymbolTable/STGV.h"

static int lastProcessedNode = -1;

TCV::TCV(AST::ASTNode *root, STGV *_stgv) {
    this->stgv = _stgv;
    this->detector = new Semantic::Detector();
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
    tempFunction = stgv->createTempFunction(node, currentFuncName, _returnType);
    node->getChild(1)->accept(*this);
}

void TCV::visit(AddOp *node) {
    node->getChild(0)->accept(*this);
    if (!isGoodToGo) return;
    std::string lhsType = returnType;
    node->getChild(2)->accept(*this);
    if (!isGoodToGo) return;
    std::string rhsType = returnType;
    if (!isMatchType(lhsType, rhsType)) {
        isGoodToGo = false;
        std::string errorString = "Unmatched type at line " + std::to_string(position);
        detector->addError(errorString);
    }
}

void TCV::visit(AssignOp *node) {
    node->getChild(0)->accept(*this);
    if (!isGoodToGo) return;
    std::string lhsType = returnType;
    node->getChild(1)->accept(*this);
    std::string rhsType = returnType;
    if (!isGoodToGo) return;
    if (!isMatchType(lhsType, rhsType)) {
        isGoodToGo = false;
        std::string errorString = "Unmatched type at line " + std::to_string(position);
        detector->addError(errorString);
    }
    returnType = "";
}


void TCV::visit(Calls *node) {
    for (const auto &child: node->getChildren()) {
        child->setParent(node);
        if (!isGoodToGo) return;
        child->accept(*this);
        lastProcessedNode++;
    }
    lastProcessedNode = -1;
}

void TCV::visit(Call *node) {
    auto _node = node->getChild(0);
    auto nodeName = _node->getName();

    try {
        Variable *variable;
        if (isFuncCall(node)) {
            if (isCalledOnObject(node)) {
                checkIfClassFunctionCalledWithRightAccess(nodeName, node);
                return;
            } else if (isCalledOnFunction(node)) {
                if (returnType != "integer" && returnType != "float") {
                    checkIfClassFunctionCalledWithRightAccess(nodeName, node, true);
                    return;
                }
            } else {
                checkIfFreeFunctionCalledWithRightArgument(nodeName, node);
                return;
            }
        } else {
            if (isCalledOnObject(node) || isCalledOnFunction(node)) {
                checkIfClassVariableCalledWithRightAccess(nodeName, node);
                return;
            }
        }
        if (currentNamespace.empty()) {
            if (currentFuncName == "main")
                variable = stgv->symbolTable->main->getVariable(nodeName);
            else
                variable = stgv->symbolTable->getFreeFunction(currentFuncName, tempFunction)->getVariable(nodeName);
        } else {
            auto _class = stgv->symbolTable->classes.at(currentNamespace);
            variable = _class->getFunction(currentFuncName, tempFunction)->getVariable(nodeName);
        }

        if (isCalledWithDimension(node)) {
            checkIfArrayCalledWithRightDimensions(variable, nodeName, node);
            return;
        }

        returnType = variable->getType();
        position = _node->getLineNumber();
    } catch (Semantic::Err::UndeclaredLocalVariable &undeclaredLocalVariable) {
        detector->addError(undeclaredLocalVariable.what());
        isGoodToGo = false;
        return;
    } catch (Semantic::Err::UndeclaredFunction &undeclaredFunction) {
        detector->addError(undeclaredFunction.what());
        isGoodToGo = false;
        return;
    } catch (Semantic::Err::UndeclaredClassVariable &undeclaredClassVariable) {
        detector->addError(undeclaredClassVariable.what());
        isGoodToGo = false;
        return;
    }
}

void TCV::visit(CompareOp *node) {
    node->getChild(0)->accept(*this);
    if (!isGoodToGo) return;
    std::string lhsType = returnType;
    node->getChild(2)->accept(*this);
    if (!isGoodToGo) return;
    std::string rhsType = returnType;
    if (!isMatchType(lhsType, rhsType)) {
        isGoodToGo = false;
        std::string errorString = "Unmatched type at line " + std::to_string(position);
        detector->addError(errorString);
    }
    returnType = "";
}

void TCV::visit(FuncCall *node) {
    for (const auto &child : node->getChildren())
        child->accept(*this);
}

void TCV::visit(FuncBody *node) {
    //Call statements node because variable declarations node has been taken care of in symbol table generation phase.
    node->getChild(1)->accept(*this);
}

void TCV::visit(If *node) {
    for (const auto &child : node->getChildren())
        child->accept(*this);
}

void TCV::visit(MainFunc *node) {
    currentFuncName = "main";
    for (const auto &child : node->getChildren())
        child->accept(*this);
}

void TCV::visit(MultOp *node) {
    node->getChild(0)->accept(*this);
    if (!isGoodToGo) return;
    std::string lhsType = returnType;
    node->getChild(2)->accept(*this);
    if (!isGoodToGo) return;
    std::string rhsType = returnType;
    if (!isMatchType(lhsType, rhsType)) {
        isGoodToGo = false;
        std::string errorString = "Unmatched type at line " + std::to_string(position);
        detector->addError(errorString);
    }
}

void TCV::visit(Program *node) {
    for (const auto &child : node->getChildren()) {
        if (!isGoodToGo) return;
        child->accept(*this);
    }
}

void TCV::visit(Read *node) {
    for (const auto &child : node->getChildren())
        child->accept(*this);
}

void TCV::visit(Return *node) {
    for (const auto &child : node->getChildren())
        child->accept(*this);

    Function *currentFunction;
    if (currentNamespace.empty())
        currentFunction = stgv->symbolTable->getFreeFunction(currentFuncName, tempFunction);
    else
        currentFunction = stgv->symbolTable->getClass(currentNamespace)->getFunction(currentFuncName, tempFunction);


    if (!isMatchType(currentFunction->getReturnType(), returnType)) {
        std::string errorString = "Expected to return " + currentFunction->getReturnType() +
                                  " but return " + returnType + " instead, at line " +
                                  std::to_string(node->getLineNumber());
        isGoodToGo = false;
        detector->addError(errorString);
        return;
    }
}

void TCV::visit(Statements *node) {
    for (const auto &child : node->getChildren()) {
        if (!isGoodToGo) return;
        child->accept(*this);
    }
}

void TCV::visit(While *node) {
    for (const auto &child : node->getChildren())
        child->accept(*this);
}

void TCV::visit(Write *node) {
    for (const auto &child: node->getChildren())
        child->accept(*this);
}

void TCV::visit(AST::ASTNode *node) {
    returnType = node->getType();
    position = node->getLineNumber();
    for (const auto &child: node->getChildren())
        child->accept(*this);
}

bool TCV::isMatchType(std::string &lhs, std::string &rhs) {
    if ((rhs == "integer" && lhs == "intnum") || (rhs == "intnum" && lhs == "integer")) return true;
    else if ((rhs == "float" && lhs == "floatnum") || (rhs == "floatnum" && lhs == "float")) return true;
    else if (rhs == lhs) return true;
    else return false;
}

bool TCV::isFuncCall(AST::ASTNode *node) {
    if (node->getChildren().size() > 1)
        return node->getChild(1)->getName().front() == 'F';
    else return false;
}

bool TCV::isCalledOnObject(AST::ASTNode *node) {
    if (lastProcessedNode == -1) return false;
    auto callNode = node->getParent()->getChild(lastProcessedNode);
    return callNode->getChild(0)->getType() == "id" && !isFuncCall(callNode);
}

bool TCV::isCalledOnFunction(AST::ASTNode *node) {
    if (lastProcessedNode == -1) return false;
    auto callNode = node->getParent()->getChild(lastProcessedNode);
    return callNode->getChild(1)->getName().front() == 'F';
}

bool TCV::isCalledWithDimension(AST::ASTNode *node) {
    if (node->getChildren().size() < 2) return false;
    else
        return !node->getChild(1)->getChildren().empty();
}

std::vector<std::string> TCV::getParamsType(AST::ASTNode *_node) {
    std::vector<std::string> types;
    for (const auto &child : _node->getChildren()) {
        child->accept(*this);
        types.push_back(returnType);
    }
    return types;
}


void TCV::checkIfFreeFunctionCalledWithRightArgument(std::string &nodeName, AST::ASTNode *_node) {
    auto functions = stgv->symbolTable->getFreeFunction(nodeName);
    auto function = getRightFunction(functions, _node);
    if (function != nullptr) returnType = function->getReturnType();
    else {
        isGoodToGo = false;
        std::string errorString = "Wrong arguments were passed to function name " + nodeName;
        detector->addError(errorString);
    }
}

void
TCV::checkIfClassFunctionCalledWithRightAccess(std::string &nodeName, AST::ASTNode *_node, bool isCalledOnFunction) {
    auto object = _node->getParent()->getChild(lastProcessedNode)->getChild(0);

    //if there is a chain of function calls, the return type
    //of the last processed function is the object type that
    //next function should be called on.
    std::string objectType = isCalledOnFunction ? returnType : "";

    //if in main function scope, we need to fetch main function local variable
    if (objectType.empty()) {
        if (currentFuncName == "main") objectType = stgv->symbolTable->main->getVariable(object->getName())->getType();
        else objectType = tempFunction->getVariable(object->getName())->getType();
    }
    auto functions = stgv->symbolTable->getClass(objectType)->getFunctions().at(nodeName);

    auto function = getRightFunction(functions, _node);
    if (function != nullptr && function->isPrivate()) {
        isGoodToGo = false;
        std::string errorString = "Accessing private function name " + nodeName;
        detector->addError(errorString);
        return;
    } else if (function == nullptr) {
        isGoodToGo = false;
        std::string errorString = "no matching function name " + nodeName;
        detector->addError(errorString);
        return;
    } else {
        returnType = function->getReturnType();
        return;
    }
}

void TCV::checkIfArrayCalledWithRightDimensions(Variable *variable, std::string &nodeName, AST::ASTNode *node) {
    std::string lineNumber = std::to_string(node->getChild(0)->getLineNumber());
    if (variable->isArray()) {
        int indices = node->getChild(1)->getChildren().size();
        if (variable->getDimensions() != indices) {
            std::string errorString = "missing dimensions for variable " + nodeName + " at line " + lineNumber;
            detector->addError(errorString);
            isGoodToGo = false;
            return;
        } else {
            for (const auto &index : node->getChild(1)->getChildren()) {
                index->accept(*this);
                if (returnType != "intnum" && returnType != "integer") {
                    std::string errorString = "Array dimensions should be of type integer at line " + lineNumber;
                    detector->addError(errorString);
                    isGoodToGo = false;
                    return;
                }
            }
            returnType = variable->getType() == "float[][]" ? "float" : "integer";
        }
    }
}

void TCV::checkIfClassVariableCalledWithRightAccess(std::string &nodeName, AST::ASTNode *node) {
    if (returnType != "integer" && returnType != "float") {
        std::string lineNumber = std::to_string(node->getChild(0)->getLineNumber());
        auto _variable = stgv->symbolTable->getClass(returnType)->getVariable(nodeName);
        if (isCalledWithDimension(node)) checkIfArrayCalledWithRightDimensions(_variable, nodeName, node);
        if (_variable->getVisibility() == Visibility::PRIVATE) {
            std::string errorString =
                    "Use of private member " + nodeName + " of class " + returnType + " at line " + lineNumber;
            detector->addError(errorString);
            isGoodToGo = false;
            return;
        } else {
            returnType = _variable->getType();
            return;
        }
    }
}

Function *TCV::getRightFunction(const std::vector<Function *> &__functions, AST::ASTNode *_node) {
    auto callParams = getParamsType(_node->getChild(1));
    for (const auto &_function : __functions) {
        if (_function->getParams().size() != callParams.size()) continue;
        int matchedParams = 0;
        for (int i = 0; i < _function->getParams().size(); i++) {
            auto fType = _function->getParams().at(i)->getType();
            if (!isMatchType(fType, callParams.at(i))) break;
            else matchedParams++;
        }
        if (matchedParams == callParams.size()) {
            return _function;
        }
    }
    return nullptr;
}


//Type checking visitors do not need to implement these functions
//but they have to have an implementation to make the compiler happy
void TCV::visit(ArrayDim *node) {}

void TCV::visit(ClassDecls *node) {}

void TCV::visit(ClassDecl *node) {}

void TCV::visit(FuncDecl *node) {}

void TCV::visit(FuncParams *node) {}

void TCV::visit(VarDecl *node) {}

void TCV::visit(Local *node) {}

void TCV::visit(Sign *node) {}