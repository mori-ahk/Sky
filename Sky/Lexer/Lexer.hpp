//
//  Lexer.hpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include <stdio.h>
#include <string>
#include "Tokenizer.hpp"

class Lexer {
public:
    Lexer();
    ~Lexer();
    void lex(std::string);
    
private:
    Tokenizer* tokenizer;
    void handleWord(std::string&, int);
};
#endif /* Lexer_hpp */
