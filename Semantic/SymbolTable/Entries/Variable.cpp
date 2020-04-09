//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Variable.h"

Variable::Variable(Enums::Visibility visibility, std::string name, std::string type, int dimensions, int position) {
    this->visibility = visibility;
    this->name = std::move(name);
    this->type = std::move(type);
    this->dimensions = dimensions;
    this->position = position;

}

const int &Variable::getDimensions() const {
    return dimensions;
}

const std::string &Variable::getType() const {
    return type;
}

std::string Variable::getRawType() const {
    std::string rawType;
    for (auto c : getType()) {
        if (c != '[' && c != ']') rawType += c;
        else break;
    }
    return rawType;
}

const std::string &Variable::getName() const {
    return name;
}

std::string Variable::getVisibilityString() const {
    if (getVisibility() == Enums::Visibility::PUBLIC) return "public";
    else return "private";
}

std::string Variable::getKindString() const {
    if (getKind() == Enums::Kind::VAR) return "var";
    else if (getKind() == Enums::Kind::LITERAL) return "literal";
    else return "temp";
}

Enums::Visibility Variable::getVisibility() const {
    return visibility;
}

Enums::Kind Variable::getKind() const {
    return kind;
}

std::ostream &operator<<(std::ostream &os, Variable &v) {
    std::string dimension = std::to_string(v.getDimensions());
    std::string visibility = v.getVisibilityString();
    os << "[ " << "visibility: " << visibility << " | name: " << v.getName() << " | type: " << v.getType()
       << " | dimensions: " << dimension << " ]" << std::endl;
    return os;
}


