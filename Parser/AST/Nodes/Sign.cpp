//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "Sign.h"
#include "../../../Visitors/Visitor.h"

void Sign::accept(Visitor &visitor) {
    visitor.visit(this);
}