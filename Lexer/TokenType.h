//
// Created by Morteza Ahmadi on 2020-01-22.
//

#ifndef SKY_TOKENTYPE_H
#define SKY_TOKENTYPE_H


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
    BlockCmt, // /* ... */
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
    Error,
    Void,
};


#endif //SKY_TOKENTYPE_H
