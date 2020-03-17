//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "Call.h"
#include "../../../Visitors/Visitor.h"

void Call::accept(Visitor &visitor) {
    visitor.visit(this);
}