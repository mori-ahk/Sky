#include <iostream>

#include "Lexer/Lexer.h"


int main(int argc, const char * argv[]) {

    const std::string basePath = "Tests/";
    std::string fileName;
    Lexer* lexer = new Lexer();

    while (true) {
        std::cout << "Please enter a file name: " << std::endl;
        std::cin >> fileName;
        lexer->lex(basePath + fileName);
    }

    return 0;
}
