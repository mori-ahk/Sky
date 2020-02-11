#include <iostream>

#include "Compiler.h"


int main(int argc, const char * argv[]) {

    const std::string basePath = "Tests/";
    std::string fileName;
    Compiler* compiler = new Compiler();

    while (true) {
        std::cout << "Please enter a file name: " << std::endl;
        std::cin >> fileName;
        compiler->compile(basePath + fileName);
    }

    return 0;
}
