//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "FuncCall.h"
#include "../../../Visitors/Visitor.h"

void FuncCall::accept(Visitor &visitor) {
    visitor.visit(this);
}