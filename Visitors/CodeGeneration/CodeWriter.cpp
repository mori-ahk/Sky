//
// Created by Morteza Ahmadi on 2020-04-10.
//

#include "CodeWriter.h"

CodeWriter::CodeWriter() {
    start();
}

void CodeWriter::start() {
    moonOutput += entry;
    moonOutput += newLine;
    moonOutput += tab;
    moonOutput += initStackPointer;
    moonOutput += newLine;
}

void CodeWriter::finish() {
    moonOutput += halt;
    moonOutput += newLine;
}

void CodeWriter::comment(std::string _comment) {
    moonOutput += newLine;
    moonOutput += tab;
    moonOutput += "% " + _comment;
    moonOutput += newLine;
}

void CodeWriter::tag(std::string tag) {
    moonOutput += tag;
    moonOutput += tab;
    moonOutput += nop;
    moonOutput += newLine;
}

void CodeWriter::loadWord(const std::string &Ri, int K, const std::string &Rj) {
    moonOutput += tab;
    moonOutput += loadOp;
    moonOutput += tab;
    moonOutput += Ri;
    moonOutput += comma;
    moonOutput += std::to_string(K);
    moonOutput += "(" + Rj + ")";
    moonOutput += newLine;
}

void CodeWriter::saveWord(int K, const std::string &Rj, const std::string &Ri) {
    moonOutput += tab;
    moonOutput += saveOp;
    moonOutput += tab;
    moonOutput += std::to_string(K);
    moonOutput += "(" + Rj + ")";
    moonOutput += comma;
    moonOutput += Ri;
    moonOutput += newLine;
}

void CodeWriter::OP(const std::string &op, const std::string &K) {
    moonOutput += tab;
    moonOutput += op;
    moonOutput += tab;
    moonOutput += K;
    moonOutput += newLine;
}

void CodeWriter::OP(const std::string &op, const std::string &Ri, const std::string &Rj) {
    moonOutput += tab;
    moonOutput += op;
    moonOutput += tab;
    moonOutput += Ri;
    moonOutput += comma;
    moonOutput += Rj; //this could be subroutine sometimes
    moonOutput += newLine;
}

void CodeWriter::OP(const std::string &op, const std::string &Ri, const std::string &Rj, const std::string &K) {
    moonOutput += tab;
    moonOutput += op;
    moonOutput += tab;
    moonOutput += Ri;
    moonOutput += comma;
    moonOutput += Rj;
    moonOutput += comma;
    moonOutput += K; //sometimes this could be offset
    moonOutput += newLine;
}

void CodeWriter::endl() {
    OP("addi", "r1", "r0", std::to_string(10));
    OP("putc", "R1");

}

void CodeWriter::write(std::string &fileName) {
    std::string base = "Moon/Generated/";
    std::ofstream stream( base + fileName + ".m");
    stream << moonOutput;
}