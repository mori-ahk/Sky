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

    std::string isInteger(std::string&);
    std::string isFloat(std::string&);
    std::string isID(std::string&);
    std::string isLongOperator(std::string&);
    std::string isShortOperator(std::string&);
    std::string isInlineComment(std::string&);
    std::string isMultilineComment(std::string&);
};

#endif /* Tokenizer_hpp */
