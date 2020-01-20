//
//  TokenType.hpp
//  Sky
//
//  Created by Morteza Ahmadi on 2020-01-19.
//  Copyright © 2020 Morteza Ahmadi. All rights reserved.
//

#ifndef TokenType_hpp
#define TokenType_hpp

#include <stdio.h>

enum class TokenType {
    Id, // letter alphanum*
    Integer, // nonzero digit* | 0
    Float, // integer fraction [e[+|-] integer]
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
    If,
    Then,
    Else,
    __Integer,
    __Float,
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

#endif /* TokenType_hpp */
