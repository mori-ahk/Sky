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
enum class TokenType {
    Id, // letter alphanum*
    Alphanum, // letter | digit | _
    Integer, // nonzero digit* | 0
    Float, // integer fraction [e[+|-] integer]
    Fraction, // .digit* nonzero | .0
    Letter, // a..z | A..Z
    Digit, // 0..9
    NonZero, // 1..9
    Eq, // ==
    NotEq, // <>
    Lt, // <
    Gt, // >
    LEq, // <=
    GEq, // >=
    Plus, // +
    Minus, // -
    Mult, // *
    Div, // /
    Asgn, // =
    OpenPr, // (
    ClosePr, // )
    OpenCbr, // {
    CloseCbr, // }
    OpenSqbr, // [
    CloseSqbr, // ]
    Semi, // ;
    Comma, // ,
    Dot, // .
    Colon, // :
    DblColon, // ::
    InlineCmt, // //
    BlockOpenCmt, // /*
    BlockCloseCmt, // */
};

enum class ReservedWord {
    If,
    Then,
    Else,
    Integer,
    Float,
    While,
    Class,
    Do,
    End,
    Public,
    Private,
    Or,
    And,
    Not,
    Read,
    Write,
    Return,
    Main,
    Inherits,
    Local,
};

class Token {
public:
    
    TokenType type;
    int lineno;
    std::string value;
    
};
#endif /* Token_hpp */
