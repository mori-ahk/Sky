//
// Created by Morteza Ahmadi on 2020-03-10.
//

#include "MainFunc.h"
#include "../../../Visitors/Visitor.h"

void MainFunc::accept(Visitor &visitor) {
    visitor.visit(this);
}