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
    Token* Tokenize(std::string&, int&, int&);
    
private:

    std::string isInteger(std::string&, int&);
    std::string isFloat(std::string&, int&);
    std::string isID(std::string&, int&);
    std::string isLongOperator(std::string&, int&);
    std::string isShortOperator(std::string&, int&);
    std::string isComment(std::string&, int&);
    
};

#endif /* Tokenizer_hpp */
