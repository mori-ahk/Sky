//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "FuncBody.h"
#include "../../../Visitors/Visitor.h"

void FuncBody::accept(Visitor &visitor) {
    visitor.visit(this);
}