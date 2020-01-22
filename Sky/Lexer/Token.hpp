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
#include <iostream>
#include "TokenType.hpp"


class Token {
public:
    
    Token(TokenType, int, std::string);
    
    TokenType getType();
    int getLineno();
    std::string getValue();
    
    friend std::ostream& operator<<(std::ostream&, Token&);
private:
    
    TokenType type;
    int lineno;
    std::string value;
};
#endif /* Token_hpp */
