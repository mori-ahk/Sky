//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Symbol.h"

Symbol::Symbol() {
    this->name = "";
    this->kind = SymbolKind::CLASS;
    this->table = nullptr;
}

Symbol::Symbol(std::string name, SymbolKind kind, SymbolTable* table) {
    this->name = name;
    this->kind = kind;
    this->table = table;
}

Symbol::~Symbol() {}

std::string& Symbol::getName() {
    return name;
}

SymbolKind Symbol::getKind() {
    return kind;
}

SymbolTable* Symbol::getTable() {
    return table;
}