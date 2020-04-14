//
// Created by Morteza Ahmadi on 2020-04-12.
//

#include "FuncCallParams.h"
#include "../../../Visitors/Visitor.h"

void FuncCallParams::accept(Visitor &visitor) {
    visitor.visit(this);
}