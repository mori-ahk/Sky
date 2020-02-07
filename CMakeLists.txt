cmake_minimum_required(VERSION 3.15)
project(Sky)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sky main.cpp Lexer/Lexer.cpp Lexer/Lexer.h Lexer/Token.cpp Lexer/Token.h Lexer/Tokenizer.cpp Lexer/Tokenizer.h Lexer/TokenType.h Parser/Grammar.cpp Parser/Grammar.h Parser/Rule.cpp Parser/Rule.h Parser/Production.cpp Parser/Production.h Parser/RuleType.h)