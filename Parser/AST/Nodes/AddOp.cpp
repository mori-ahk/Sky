//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "AddOp.h"
#include "../../../Visitors/Visitor.h"

void AddOp::accept(Visitor &visitor) {
    visitor.visit(this);
}