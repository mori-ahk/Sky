//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "ClassDecls.h"
#include "../../../Visitors/Visitor.h"

void ClassDecls::accept(Visitor &visitor) {
    visitor.visit(this);
}