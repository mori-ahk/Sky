//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "FuncDecl.h"
#include "../../../Visitors/Visitor.h"

void FuncDecl::accept(Visitor &visitor) {
    visitor.visit(this);
}