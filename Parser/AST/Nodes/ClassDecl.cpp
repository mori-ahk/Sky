//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "ClassDecl.h"
#include "../../../Visitors/Visitor.h"

void ClassDecl::accept(Visitor &visitor) {
    visitor.visit(this);
}