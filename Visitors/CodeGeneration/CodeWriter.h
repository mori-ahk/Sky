//
// Created by Morteza Ahmadi on 2020-04-10.
//

#ifndef SKY_CODEWRITER_H
#define SKY_CODEWRITER_H


#include <string>
#include <fstream>

class CodeWriter {
public:
    CodeWriter();

    void start();
    void finish();
    void write(std::string &);
    void comment(std::string);
    void tag(std::string);
    void loadWord(const std::string&, int, const std::string&);
    void saveWord(int, const std::string&, const std::string&);
    void OP(const std::string &, const std::string &);
    void OP(const std::string &, const std::string &, const std::string &);
    void OP(const std::string &, const std::string &, const std::string &, const std::string &);
    void line();

private:
    std::string moonOutput;
    const std::string tab = "\t";
    const std::string newLine = "\n";
    const std::string comma = ",";
    const std::string loadOp = "lw ";
    const std::string saveOp = "sw ";
    const std::string entry = "entry";
    const std::string halt = "hlt";
    const std::string nop = "nop";
    const std::string initStackPointer = "addi\tr14,r0,topaddr";
};


#endif //SKY_CODEWRITER_H
