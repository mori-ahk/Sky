//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "Program.h"
#include "../../../Visitors/Visitor.h"

void Program::accept(Visitor &visitor) {
    visitor.visit(this);
}