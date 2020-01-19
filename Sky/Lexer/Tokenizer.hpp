//
//  Tokenizer.hpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#ifndef Tokenizer_hpp
#define Tokenizer_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Token.hpp"

class Tokenizer {
public:
    Tokenizer(std::string word);
    ~Tokenizer();
    std::vector<Token*> matches;
    
private:
    std::string word;
    Token isInteger(std::string);
    Token isFloat(std::string);
    Token isID(std::string);
    Token isKeyword(std::string);
    
};

#endif /* Tokenizer_hpp */
