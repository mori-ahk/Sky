#include <iostream>

#include "Compiler.h"


int main(int argc, const char *argv[]) {


    std::string fileName = argv[1];

    Compiler *compiler = new Compiler(fileName);
    compiler->compile();

    return 0;
}
