//
// Created by Morteza Ahmadi on 2020-04-10.
//

#ifndef SKY_CODEWRITER_H
#define SKY_CODEWRITER_H


#include <string>
#include <fstream>
#include <unordered_map>
class CodeWriter {
public:
    CodeWriter() = default;

    void start();
    void finish();
    void write(std::string &);
    void comment(const std::string&);
    void tag(const std::string&, bool isForEnd = false);
    void loadWord(const std::string&, int, const std::string&);
    void saveWord(int, const std::string&, const std::string&);
    void OP(const std::string &, const std::string &);
    void OP(const std::string &, const std::string &, const std::string &);
    void OP(const std::string &, const std::string &, const std::string &, const std::string &);
    void endl();
    std::string generateTag(const std::string &, bool isForEnd = false);
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
    std::unordered_map<std::string, int> tags;
};


#endif //SKY_CODEWRITER_H
