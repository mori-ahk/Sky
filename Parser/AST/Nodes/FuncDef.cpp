//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "FuncDef.h"
#include "../../../Visitors/Visitor.h"

void FuncDef::accept(Visitor &visitor) {
    visitor.visit(this);
}