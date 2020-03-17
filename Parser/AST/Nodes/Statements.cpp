//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "Statements.h"
#include "../../../Visitors/Visitor.h"

void Statements::accept(Visitor &visitor) {
    visitor.visit(this);
}