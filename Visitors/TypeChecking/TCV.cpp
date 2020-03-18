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
        std::string errorString = "Unmatched type at line " + std::to_string(position);
        detector->addError(errorString);
    }
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
    auto isFuncCall = [&node]() {
        if (node->getChildren().size() > 1)
            return node->getChild(1)->getName().front() == 'F';
        else return false;
    };

    try {
        Variable *variable;
        if (currentNamespace.empty()) {
            if (isFuncCall()) {
                if (isCalledOnObject(node)) {

                }
                else {
                    checkIfFreeFunctionCalledWithRightArgument(nodeName, node);
                    return;
                }

            }

            if (currentFuncName == "main")
                variable = stgv->symbolTable->main->getVariable(nodeName);
            else
                variable = stgv->symbolTable->getFreeFunction(currentFuncName, tempFunction)->getVariable(nodeName);
        } else {
            if (isFuncCall()) {

            }
            variable = stgv->symbolTable->classes.at(currentNamespace)->getFunction(currentFuncName,
                                                                                    tempFunction)->getVariable(
                    nodeName);

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
    }

    if (_node->getType() == "id" &&
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

bool TCV::isMatchType(std::string &lhs, std::string &rhs) {
    if ((rhs == "integer" && lhs == "intnum") || (rhs == "intnum" && lhs == "integer")) return true;
    else if ((rhs == "float" && lhs == "floatnum") || (rhs == "floatnum" && lhs == "float")) return true;
    else if (rhs == lhs) return true;
    else return false;
}

bool TCV::isCalledOnObject(AST::ASTNode *node) {
    if (lastProcessedNode == -1) return false;
    if (node->getParent()->getChild(lastProcessedNode)->getType() == "id") return true;
    else return false;
}

std::vector<std::string> TCV::getParamsType(AST::ASTNode *_node) {
    std::vector<std::string> types;
    for (const auto& child : _node->getChildren()) {
        types.push_back(child->getType());
    }
    return types;
}

void TCV::checkIfFreeFunctionCalledWithRightArgument(std::string &nodeName, AST::ASTNode *_node) {
    auto functions = stgv->symbolTable->getFreeFunction(nodeName);
    auto callParams = getParamsType(_node->getChild(1));
    bool isRightFunctionCall = false;
    for (const auto &_function : functions) {
        if (_function->getParams().size() != callParams.size()) continue;
        int matchedParams = 0;
        for (int i = 0; i < _function->getParams().size(); i++) {
            auto fType = _function->getParams().at(i)->getType();
            if (!isMatchType(fType, callParams.at(i))) break;
            else matchedParams++;
        }
        if (matchedParams == callParams.size()) {
            isRightFunctionCall = true;
            returnType = _function->getReturnType();
            break;
        }
    }

    if (!isRightFunctionCall) { std::cerr << "Wrong number of arguments were passed to function name " << nodeName << std::endl;}
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