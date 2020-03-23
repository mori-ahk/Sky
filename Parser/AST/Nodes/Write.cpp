//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "Write.h"
#include "../../../Visitors/Visitor.h"

void Write::accept(Visitor &visitor) {
    visitor.visit(this);
}