//
//  main.cpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-16.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#include <iostream>
#include <filesystem>
#include "Lexer.hpp"


int main(int argc, const char * argv[]) {
    
    const std::string basePath = "Tests/";
    std::string fileName;
    Lexer* lexer = new Lexer();
    while (fileName != "exit") {
        std::cout << "Please enter a file name: (type exit to terminate)" << std::endl;
        std::cin >> fileName;
        std::cout << basePath + fileName << std::endl;
        lexer->lex(basePath + fileName);
    }
    
    delete lexer;
    return 0;
}
