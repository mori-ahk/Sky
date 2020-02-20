cmake_minimum_required(VERSION 3.15)
project(Sky)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sky main.cpp Lexer/Lexer.cpp Lexer/Lexer.h Lexer/Token.cpp Lexer/Token.h Lexer/Tokenizer.cpp Lexer/Tokenizer.h Lexer/TokenType.h Parser/Grammar.cpp Parser/Grammar.h Parser/Rule.cpp Parser/Rule.h Parser/Parser.cpp Parser/Parser.h Compiler.cpp Compiler.h Parser/AST/ASTNode.cpp Parser/AST/ASTNode.h Parser/AST/ASTBuilder.cpp Parser/AST/ASTBuilder.h Parser/AST/Visualizer.cpp Parser/AST/Visualizer.h)