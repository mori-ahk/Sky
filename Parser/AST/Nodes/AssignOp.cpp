//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "AssignOp.h"
#include "../../../Visitors/Visitor.h"

void AssignOp::accept(Visitor &visitor) {
    visitor.visit(this);
}