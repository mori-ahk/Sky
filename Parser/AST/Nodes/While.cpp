//
// Created by Morteza Ahmadi on 2020-03-17.
//

#include "While.h"
#include "../../../Visitors/Visitor.h"

void While::accept(Visitor &visitor) {
    visitor.visit(this);
}