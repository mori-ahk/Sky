//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "CompareOp.h"
#include "../../../Visitors/Visitor.h"

void CompareOp::accept(Visitor &visitor) {
    visitor.visit(this);
}