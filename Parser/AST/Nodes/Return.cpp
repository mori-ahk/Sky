//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "Return.h"
#include "../../../Visitors/Visitor.h"

void Return::accept(Visitor &visitor) {
    visitor.visit(this);
}