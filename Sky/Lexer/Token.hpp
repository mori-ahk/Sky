//
//  Token.hpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#ifndef Token_hpp
#define Token_hpp

#include <stdio.h>
#include <string>
#include "TokenType.hpp"


class Token {
public:
    Token(TokenType, int, std::string);
    TokenType type;
    int lineno;
    std::string value;
    
};
#endif /* Token_hpp */
