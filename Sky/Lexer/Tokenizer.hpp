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
#include <unordered_map>
#include "Token.hpp"
#include "TokenType.hpp"

class Tokenizer {
public:
    
    Tokenizer();
    ~Tokenizer();
    int Tokenize(std::string, int);
    std::vector<Token*> getMatches();
private:

    bool isInteger(std::string);
    bool isFloat(std::string);
    bool isID(std::string);
    bool isKeyword(std::string);
    
};

#endif /* Tokenizer_hpp */
