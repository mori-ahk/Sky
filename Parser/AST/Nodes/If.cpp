//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "If.h"
#include "../../../Visitors/Visitor.h"

void If::accept(Visitor &visitor) {
    visitor.visit(this);
}