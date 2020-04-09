//
// Created by Morteza Ahmadi on 2020-04-09.
//

#include "Number.h"
#include "../../../Visitors/Visitor.h"

void Number::accept(Visitor &visitor) {
    visitor.visit(this);
}