//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "Local.h"
#include "../../../Visitors/Visitor.h"

void Local::accept(Visitor &visitor) {
    visitor.visit(this);
}