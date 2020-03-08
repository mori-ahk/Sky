//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "ArrayDim.h"
#include "../../../Visitors/Visitor.h"

void ArrayDim::accept(Visitor &visitor) {
    visitor.visit(this);
}