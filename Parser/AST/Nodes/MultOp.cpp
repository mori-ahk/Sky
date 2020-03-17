//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "MultOp.h"
#include "../../../Visitors/Visitor.h"

void MultOp::accept(Visitor &visitor) {
    visitor.visit(this);
}