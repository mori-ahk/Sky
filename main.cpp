#include <iostream>

#include "Compiler.h"


int main(int argc, const char * argv[]) {

    const std::string basePath = "Tests/";
    std::string fileName;

    std::cout << "Please enter a file name: " << std::endl;
    std::cin >> fileName;
    Compiler* compiler = new Compiler(basePath + fileName);
    compiler->compile();


    return 0;
}
