//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "FuncParams.h"
#include "../../../Visitors/Visitor.h"

void FuncParams::accept(Visitor &visitor) {
    visitor.visit(this);
}