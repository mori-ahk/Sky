#include <iostream>

#include "Compiler.h"


int main(int argc, const char *argv[]) {

    const std::string basePath = "Tests/";

    std::string fileName = argv[1];

    Compiler *compiler = new Compiler(basePath + fileName);
    compiler->compile();

    system("dot -Tpng TreeContent.gv -o TreeContent.png");

    return 0;
}
