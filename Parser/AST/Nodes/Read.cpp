//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "Read.h"
#include "../../../Visitors/Visitor.h"

void Read::accept(Visitor &visitor) {
    visitor.visit(this);
}