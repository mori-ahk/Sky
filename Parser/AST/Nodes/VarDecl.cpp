//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "VarDecl.h"
#include "../../../Visitors/Visitor.h"

void VarDecl::accept(Visitor &visitor) {
    visitor.visit(this);
}