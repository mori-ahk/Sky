//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "Calls.h"
#include "../../../Visitors/Visitor.h"

void Calls::accept(Visitor &visitor) {
    visitor.visit(this);
}