//
// Created by Morteza Ahmadi on 2020-04-10.
//

#include "CodeWriter.h"
void CodeWriter::start() {
    moonOutput += entry;
    moonOutput += initStackPointer;
    moonOutput += newLine;
}

void CodeWriter::finish() {
    moonOutput += halt;
    moonOutput += newLine;
}

void CodeWriter::comment(std::string _comment) {
    moonOutput += commentIndent;
    moonOutput += "% " + _comment;
    moonOutput += newLine;
}

void CodeWriter::loadWord(const std::string& Ri, int K, const std::string& Rj) {
    moonOutput += tab;
    moonOutput += loadOp;
    moonOutput += tab;
    moonOutput += Ri;
    moonOutput += comma;
    moonOutput += std::to_string(K);
    moonOutput += "(" + Rj + ")";
    moonOutput += newLine;
}

void CodeWriter::saveWord(const std::string& Ri, int K, const std::string& Rj) {
    moonOutput += tab;
    moonOutput += saveOp;
    moonOutput += tab;
    moonOutput += std::to_string(K);
    moonOutput += "(" + Rj + ")";
    moonOutput += comma;
    moonOutput += Ri;
    moonOutput += newLine;
}