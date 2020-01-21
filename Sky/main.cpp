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
    // insert code here...
    Lexer* lexer = new Lexer();
    lexer->lex("Test.txt");
    return 0;
}
