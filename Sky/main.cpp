//
//  main.cpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-16.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#include <iostream>
#include "Lexer.hpp"

int main(int argc, const char * argv[]) {
    
    Lexer* lexer = new Lexer();
    lexer->lex("Test_1.txt");
    lexer->lex("Test_2.txt");
    
    delete lexer;
    return 0;
}
