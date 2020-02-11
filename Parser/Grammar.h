//
// Created by Morteza Ahmadi on 2020-02-07.
//

#ifndef SKY_GRAMMAR_H
#define SKY_GRAMMAR_H

#include "Rule.h"
#include "RuleType.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
class Grammar {
public:
    Grammar();
    ~Grammar();
    Rule* getRule(std::string);

};


const std::unordered_map<RuleType, std::vector<std::string> > RHS = {
        {RuleType::START,                               {"PROGRAM"}},
        {RuleType::PROGRAM,                             {"CLASS_DECLARATIONS FUNCTION_DEFINITIONS main FUNCTION_BODY"}},
        {RuleType::CLASS_DECLARATIONS,                  {"CLASS_DECLARATION CLASS_DECLARATIONS",                "#"}},
        {RuleType::CLASS_DECLARATION,                   {"class id OPTIONAL_INHERITS { MEMBER_DECLARATIONS } ;"}},
        {RuleType::FUNCTION_DEFINITIONS,                {"FUNCTION_DEFINITION FUNCTION_DEFINITIONS",            "#"}},
        {RuleType::FUNCTION_DEFINITION,                 {"FUNCTION_SIGNATURE FUNCTION_BODY ;"}},
        {RuleType::MEMBER_DECLARATIONS,                 {"VISIBILITY MEMBER_DECLARATION MEMBER_DECLARATIONS",   "#"}},
        {RuleType::MEMBER_DECLARATION,                  {"id FUNCTION_OR_VARIABLE_DECLARATION",                 "TYPE_NON_ID VARIABLE_DECLARATION"}},
        {RuleType::FUNCTION_OR_VARIABLE_DECLARATION,    {"FUNCTION_DECLARATION",                                "VARIABLE_DECLARATION"}},
        {RuleType::VISIBILITY,                          {"public",                                              "private"}},
        {RuleType::STATEMENT,                           {"if ( REL_EXPRESSION ) then STATEMENT_BLOCK else STATEMENT_BLOCK ;",
                                                                                                                "while ( REL_EXPRESSION ) STATEMENT_BLOCK ;",
                                                                                                                           "read ( STATEMENT_VARIABLE ) ;",
                                                                                                                                    "write ( EXPRESSION ) ;",
                                                                                                                                                            "return ( EXPRESSION ) ;",
                                                                                                                                                                          "ASSIGN_STATEMENT_OR_FUNCTION_CALL"}},
        {RuleType::STATEMENT_VARIABLE,                  {"id STATEMENT_VARIABLE_OR_FUNCTION_CALL"}},
        {RuleType::STATEMENT_VARIABLE_OR_FUNCTION_CALL, {"INDICES STATEMENT_VARIABLE_EXT",
                                                                                                                "( FUNCTION_CALL_PARAMS ) STATEMENT_FUNCTION_CALL"}},
        {RuleType::STATEMENT_VARIABLE_EXT,              {". STATEMENT_VARIABLE",                                "#"}},
        {RuleType::STATEMENT_FUNCTION_CALL,             {". STATEMENT_VARIABLE"}},
        {RuleType::ASSIGN_STATEMENT_OR_FUNCTION_CALL,   {"id VARIABLE_OR_FUNCTION_CALL_EXT"}},
        {RuleType::VARIABLE_OR_FUNCTION_CALL_EXT,       {"INDICES VARIABLE_EXT",
                                                                                                                "( FUNCTION_CALL_PARAMS ) FUNCTION_CALL_EXT"}},
        {RuleType::VARIABLE_EXT,                        {"ASSIGNMENT_OP EXPRESSION ;",                          ". ASSIGN_STATEMENT_OR_FUNCTION_CALL"}},
        {RuleType::FUNCTION_CALL_EXT,                   {";",                                                   ". ASSIGN_STATEMENT_OR_FUNCTION_CALL"}},
        {RuleType::FUNCTION_PARAMS,                     {"TYPE id ARRAY_DIMENSIONS FUNCTION_PARAMS_TAILS",      "#"}},
        {RuleType::ADD_OP,                              {"+",                                                   "-",       "or"}},
        {RuleType::OPTIONAL_INHERITS,                   {"inherits id INHERITED_CLASSES",                       "#"}},
        {RuleType::REL_EXPRESSION,                      {"ARITH_EXPRESSION COMPARE_OP INHERITED_CLASSES",       "#"}},
        {RuleType::FUNCTION_DECLARATION,                {"( FUNCTION_PARAMS ) : TYPE_OR_VOID ;"}},
        {RuleType::FUNCTION_CALL_PARAMS_TAILS,          {"FUNCTION_CALL_PARAMS_TAIL FUNCTION_CALL_PARAM_TAILS", "#"}},
        {RuleType::LOCAL_SCOPE,                         {"local VARIABLE_DECLARATIONS",                         "#"}},
        {RuleType::ARRAY_DIMENSIONS,                    {"ARRAY_SIZE ARRAY_DIMENSIONS",                         "#"}},
        {RuleType::EXPRESSION,                          {"ARITH_EXPRESSION REL_EXPRESSION_OR_NULL"}},
        {RuleType::REL_EXPRESSION_OR_NULL,              {"COMPARE_OP ARITH_EXPRESSION",                         "#"}},
        {RuleType::STATEMENTS,                          {"STATEMENT STATEMENTS",                                "#"}},
        {RuleType::ARITH_EXPRESSION,                    {"TERM RIGHT_REC_ARITH_EXPRESSION"}},
        {RuleType::RIGHT_REC_ARITH_EXPRESSION,          {"ADD_OP TERM RIGHT_REC_ARITH_EXPRESSION",              "#"}},
        {RuleType::FUNCTION_SIGNATURE,                  {"id FUNCTION_SIGNATURE_NAMESPACE"}},
        {RuleType::FUNCTION_SIGNATURE_NAMESPACE,        {"FUNCTION_SIGNATURE_EXT",                              ":: id FUNCTION_SIGNATURE_EXT"}},
        {RuleType::FUNCTION_SIGNATURE_EXT,              {"( FUNCTION_PARAMS ) : TYPE_OR_VOID"}},
        {RuleType::FUNCTION_PARAMS_TAILS,               {"FUNCTION_PARAMS_TAIL FUNCTION_PARAMS_TAILS",          "#"}},
        {RuleType::INHERITED_CLASSES,                   {", id INHERITED_CLASSES"}},
        {RuleType::SIGN,                                {"+",                                                   "-"}},
        {RuleType::COMPARE_OP,                          {"==",                                                  "<>",      "<",     ">",                    "<=",         ">="}},
        {RuleType::INDEX,                               {"[ ARITH_EXPRESSION ]"}},
        {RuleType::VARIABLE_DECLARATIONS,               {"VARIABLE_DECLARATION VARIABLE_DECLARATIONS",          "#"}},
        {RuleType::FACTOR,                              {"VARIABLE_FUNCTION_CALL",                              "Integer", "float", "( ARITH_EXPRESSION )", "not FACTOR", "SIGN FACTOR"}},
        {RuleType::VARIABLE_FUNCTION_CALL,              {"id VARIABLE_OR_FUNCTION_CALL"}},
        {RuleType::VARIABLE_OR_FUNCTION_CALL,           {"INDICES FACTOR_VARIABLE",                             "( FUNCTION_CALL_PARAMS ) FACTOR_FUNCTION_CALL"}},
        {RuleType::FACTOR_VARIABLE,                     {". VARIABLE_FUNCTION_CALL",                            "#"}},
        {RuleType::FACTOR_FUNCTION_CALL,                {". VARIABLE_FUNCTION_CALL",                            "#"}},
        {RuleType::TERM,                                {"FACTOR RIGHT_REC_TERM"}},
        {RuleType::MULT_OP,                             {"*",                                                   "/",       "and"}},
        {RuleType::RIGHT_REC_TERM,                      {"MULT_OP FACTOR RIGHT_REC_TERM",                       "#"}},
        {RuleType::TYPE_OR_VOID,                        {"TYPE",                                                "void"}},
        {RuleType::TYPE,                                {"TYPE_NON_ID",                                         "id"}},
        {RuleType::TYPE_NON_ID,                         {"__Integer",                                           "__Float"}},
        {RuleType::ARRAY_SIZE,                          {"[ OPTIONAL_INT ]"}},
        {RuleType::OPTIONAL_INT,                        {"Integer",                                             "#"}},
        {RuleType::FUNCTION_CALL_PARAMS_TAIL,           {", EXPRESSION"}},
        {RuleType::FUNCTION_CALL_PARAMS,                {"EXPRESSION FUNCTION_CALL_PARAMS_TAILS",               "#"}},
        {RuleType::VARIABLE_DECLARATION,                {"id ARRAY_DIMENSIONS ;"}},
        {RuleType::FUNCTION_BODY,                       {"LOCAL_SCOPE do STATEMENT end"}},
        {RuleType::STATEMENT_BLOCK,                     {"do STATEMENTS end", "STATEMENT",                      "#"}},
        {RuleType::ASSIGNMENT_OP,                       {"="}},
        {RuleType::FUNCTION_PARAMS_TAIL,                {", TYPE id ARRAY_DIMENSIONS"}},
        {RuleType::INDICES,                             {"INDEX INDICES",                                       "#"}},
};

const std::unordered_map<RuleType, std::unordered_set<std::string>> FIRST = {
        {RuleType::START,                               {"main", "class", "id"}},
        {RuleType::PROGRAM,                             {"main", "class", "id"}},
        {RuleType::CLASS_DECLARATIONS,                  {"class"}},
        {RuleType::CLASS_DECLARATION,                   {"class"}},
        {RuleType::FUNCTION_DEFINITIONS,                {"id"}},
        {RuleType::FUNCTION_DEFINITION,                 {"id"}},
        {RuleType::MEMBER_DECLARATIONS,                 {"public", "private"}},
        {RuleType::MEMBER_DECLARATION,                  {"id", "__Integer", "__Float"}},
        {RuleType::FUNCTION_OR_VARIABLE_DECLARATION,    {"id", "("}},
        {RuleType::VISIBILITY,                          {"public", "private"}},
        {RuleType::STATEMENT,                           {"id", "if", "while", "read", "write", "return"}},
        {RuleType::STATEMENT_VARIABLE,                  {"id"}},
        {RuleType::STATEMENT_VARIABLE_OR_FUNCTION_CALL, {"(", ".", "["}},
        {RuleType::STATEMENT_VARIABLE_EXT,              {"."}},
        {RuleType::STATEMENT_FUNCTION_CALL,             {"."}},
        {RuleType::ASSIGN_STATEMENT_OR_FUNCTION_CALL,   {"id"}},
        {RuleType::VARIABLE_OR_FUNCTION_CALL_EXT,       {"(", ".", "[", "="}},
        {RuleType::VARIABLE_EXT,                        {".", "="}},
        {RuleType::FUNCTION_CALL_EXT,                   {";", "."}},
        {RuleType::FUNCTION_PARAMS,                     {"id", "__Integer", "__Float"}},
        {RuleType::ADD_OP,                              {"+", "-", "or"}},
        {RuleType::OPTIONAL_INHERITS,                   {"inherits"}},
        {RuleType::REL_EXPRESSION,                      {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::FUNCTION_DECLARATION,                {"("}},
        {RuleType::FUNCTION_CALL_PARAMS_TAILS,          {","}},
        {RuleType::LOCAL_SCOPE,                         {"local"}},
        {RuleType::ARRAY_DIMENSIONS,                    {"["}},
        {RuleType::EXPRESSION,                          {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::REL_EXPRESSION_OR_NULL,              {"==", "<>", "<", ">", "<=", ">="}},
        {RuleType::STATEMENTS,                          {"id", "if", "while", "read", "write", "return"}},
        {RuleType::ARITH_EXPRESSION,                    {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::RIGHT_REC_ARITH_EXPRESSION,          {"plus", "minus", "or"}},
        {RuleType::FUNCTION_SIGNATURE,                  {"id"}},
        {RuleType::FUNCTION_SIGNATURE_NAMESPACE,        {"(", "::"}},
        {RuleType::FUNCTION_SIGNATURE_EXT,              {"("}},
        {RuleType::FUNCTION_PARAMS_TAILS,               {","}},
        {RuleType::INHERITED_CLASSES,                   {","}},
        {RuleType::SIGN,                                {"+", "-"}},
        {RuleType::COMPARE_OP,                          {"==", "<>", "<", ">", "<=", ">="}},
        {RuleType::INDEX,                               {"["}},
        {RuleType::VARIABLE_DECLARATIONS,               {"id"}},
        {RuleType::FACTOR,                              {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::VARIABLE_FUNCTION_CALL,              {"id"}},
        {RuleType::VARIABLE_OR_FUNCTION_CALL,           {"(", ".", "["}},
        {RuleType::FACTOR_VARIABLE,                     {"."}},
        {RuleType::FACTOR_FUNCTION_CALL,                {"."}},
        {RuleType::TERM,                                {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::MULT_OP,                             {"*", "/", "and"}},
        {RuleType::RIGHT_REC_TERM,                      {"*", "/", "and"}},
        {RuleType::TYPE_OR_VOID,                        {"id", "void", "__Integer", "__Float"}},
        {RuleType::TYPE,                                {"id", "__Integer", "__Float"}},
        {RuleType::TYPE_NON_ID,                         {"__Integer", "__Float"}},
        {RuleType::ARRAY_SIZE,                          {"["}},
        {RuleType::OPTIONAL_INT,                        {"Integer"}},
        {RuleType::FUNCTION_CALL_PARAMS_TAIL,           {","}},
        {RuleType::FUNCTION_CALL_PARAMS,                {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::VARIABLE_DECLARATION,                {"id"}},
        {RuleType::FUNCTION_BODY,                       {"local", "do"}},
        {RuleType::STATEMENT_BLOCK,                     {"id", "if", "while", "read", "write", "return", "do"}},
        {RuleType::ASSIGNMENT_OP,                       {"="}},
        {RuleType::FUNCTION_PARAMS_TAIL,                {","}},
        {RuleType::INDICES,                             {"["}},
};

const std::unordered_map<RuleType, std::unordered_set<std::string> > FOLLOW = {
        {RuleType::START,                               {"#"}},
        {RuleType::PROGRAM,                             {"#"}},
        {RuleType::CLASS_DECLARATIONS,                  {"main", "id"}},
        {RuleType::CLASS_DECLARATION,                   {"main", "class", "id"}},
        {RuleType::FUNCTION_DEFINITIONS,                {"main"}},
        {RuleType::FUNCTION_DEFINITION,                 {"main", "id"}},
        {RuleType::MEMBER_DECLARATIONS,                 {"}"}},
        {RuleType::MEMBER_DECLARATION,                  {"}", "public", "private"}},
        {RuleType::FUNCTION_OR_VARIABLE_DECLARATION,    {"}", "public", "private"}},
        {RuleType::VISIBILITY,                          {"id", "integer", "float"}},
        {RuleType::STATEMENT,                           {"id", "semi", "if", "else", "while", "read", "write", "return", "end"}},
        {RuleType::STATEMENT_VARIABLE,                  {")"}},
        {RuleType::STATEMENT_VARIABLE_OR_FUNCTION_CALL, {")"}},
        {RuleType::STATEMENT_VARIABLE_EXT,              {")"}},
        {RuleType::STATEMENT_FUNCTION_CALL,             {")"}},
        {RuleType::ASSIGN_STATEMENT_OR_FUNCTION_CALL,   {"id", "semi", "if", "else", "while", "read", "write", "return", "end"}},
        {RuleType::VARIABLE_OR_FUNCTION_CALL_EXT,       {"id", "semi", "if", "else", "while", "read", "write", "return", "end"}},
        {RuleType::VARIABLE_EXT,                        {"id", "semi", "if", "else", "while", "read", "write", "return", "end"}},
        {RuleType::FUNCTION_CALL_EXT,                   {"id", "semi", "if", "else", "while", "read", "write", "return", "end"}},
        {RuleType::FUNCTION_PARAMS,                     {")"}},
        {RuleType::ADD_OP,                              {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::OPTIONAL_INHERITS,                   {"{"}},
        {RuleType::REL_EXPRESSION,                      {")"}},
        {RuleType::FUNCTION_DECLARATION,                {"{", "public", "private"}},
        {RuleType::FUNCTION_CALL_PARAMS_TAILS,          {")"}},
        {RuleType::LOCAL_SCOPE,                         {"do"}},
        {RuleType::ARRAY_DIMENSIONS,                    {";", ")", ","}},
        {RuleType::EXPRESSION,                          {";", ")", ","}},
        {RuleType::REL_EXPRESSION_OR_NULL,              {";", ")", ","}},
        {RuleType::STATEMENTS,                          {"end"}},
        {RuleType::ARITH_EXPRESSION,                    {";", ")", "," , "==", "<>", "<", ">", "<=", ">=", "]"}},
        {RuleType::RIGHT_REC_ARITH_EXPRESSION,          {";", ")", "," , "==", "<>", "<", ">", "<=", ">=", "]"}},
        {RuleType::FUNCTION_SIGNATURE,                  {"local", "do"}},
        {RuleType::FUNCTION_SIGNATURE_NAMESPACE,        {"local", "do"}},
        {RuleType::FUNCTION_SIGNATURE_EXT,              {"local", "do"}},
        {RuleType::FUNCTION_PARAMS_TAILS,               {")"}},
        {RuleType::INHERITED_CLASSES,                   {"{"}},
        {RuleType::SIGN,                                {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::COMPARE_OP,                          {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::INDEX,                               {";", ")", ".", "+", "-", "or", ",", "==", "<>", "<", ">", "<=", ">=", "[", "]", "*", "/", "and", "="}},
        {RuleType::VARIABLE_DECLARATIONS,               {"do"}},
        {RuleType::FACTOR,                              {";", ")", "+", "-", "or", ",", "==", "<>", "<", ">", "<=", ">=", "]", "*", "/", "and"}},
        {RuleType::VARIABLE_FUNCTION_CALL,              {";", ")", "+", "-", "or", ",", "==", "<>", "<", ">", "<=", ">=", "]", "*", "/", "and"}},
        {RuleType::VARIABLE_OR_FUNCTION_CALL,           {";", ")", "+", "-", "or", ",", "==", "<>", "<", ">", "<=", ">=", "]", "*", "/", "and"}},
        {RuleType::FACTOR_VARIABLE,                     {";", ")", "+", "-", "or", ",", "==", "<>", "<", ">", "<=", ">=", "]", "*", "/", "and"}},
        {RuleType::FACTOR_FUNCTION_CALL,                {";", ")", "+", "-", "or", ",", "==", "<>", "<", ">", "<=", ">=", "]", "*", "/", "and"}},
        {RuleType::TERM,                                {";", ")", "+", "-", "or", ",", "==", "<>", "<", ">", "<=", ">=", "]"}},
        {RuleType::MULT_OP,                             {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::RIGHT_REC_TERM,                      {";", ")", "+", "-", "or", ",", "==", "<>", "<", ">", "<=", ">=", "]"}},
        {RuleType::TYPE_OR_VOID,                        {";", "local", "do"}},
        {RuleType::TYPE,                                {"id", ";", "local", "do"}},
        {RuleType::TYPE_NON_ID,                         {"id", ";", "local", "do"}},
        {RuleType::ARRAY_SIZE,                          {";", ")", ",", "["}},
        {RuleType::OPTIONAL_INT,                        {"]"}},
        {RuleType::FUNCTION_CALL_PARAMS_TAIL,           {")", ","}},
        {RuleType::FUNCTION_CALL_PARAMS,                {")"}},
        {RuleType::VARIABLE_DECLARATION,                {"id", "}", "public", "private", "do"}},
        {RuleType::FUNCTION_BODY,                       {";", "#"}},
        {RuleType::STATEMENT_BLOCK,                     {";", "else"}},
        {RuleType::ASSIGNMENT_OP,                       {"id", "(", "+", "-", "Integer", "Float", "not"}},
        {RuleType::FUNCTION_PARAMS_TAIL,                {")", ","}},
        {RuleType::INDICES,                             {";", ")", ".", "+", "-", "or", ",", "==", "<>", "<", ">", "<=", ">=", "[", "]", "*", "/", "and", "="}},
};

const std::unordered_map<std::string, Rule*> RULES = {
        {"START", new Rule(RuleType::START, FIRST.at(RuleType::START), FOLLOW.at(RuleType::START), RHS.at(RuleType::START))},
        {"PROGRAM", new Rule(RuleType::PROGRAM, FIRST.at(RuleType::PROGRAM), FOLLOW.at(RuleType::PROGRAM), RHS.at(RuleType::PROGRAM))},
        {"CLASS_DECLARATIONS", new Rule(RuleType::CLASS_DECLARATIONS, FIRST.at(RuleType::CLASS_DECLARATIONS), FOLLOW.at(RuleType::CLASS_DECLARATIONS), RHS.at(RuleType::CLASS_DECLARATIONS))},
        {"CLASS_DECLARATION", new Rule(RuleType::CLASS_DECLARATION, FIRST.at(RuleType::CLASS_DECLARATION), FOLLOW.at(RuleType::CLASS_DECLARATION), RHS.at(RuleType::CLASS_DECLARATION))},
        {"FUNCTION_DEFINITIONS", new Rule(RuleType::FUNCTION_DEFINITIONS, FIRST.at(RuleType::FUNCTION_DEFINITIONS), FOLLOW.at(RuleType::FUNCTION_DEFINITIONS), RHS.at(RuleType::FUNCTION_DEFINITIONS))},
        {"FUNCTION_DEFINITION", new Rule(RuleType::FUNCTION_DEFINITION, FIRST.at(RuleType::FUNCTION_DEFINITION), FOLLOW.at(RuleType::FUNCTION_DEFINITION), RHS.at(RuleType::FUNCTION_DEFINITION))},
        {"MEMBER_DECLARATIONS", new Rule(RuleType::MEMBER_DECLARATIONS, FIRST.at(RuleType::MEMBER_DECLARATIONS), FOLLOW.at(RuleType::MEMBER_DECLARATIONS), RHS.at(RuleType::MEMBER_DECLARATIONS))},
        {"MEMBER_DECLARATION", new Rule(RuleType::MEMBER_DECLARATION, FIRST.at(RuleType::MEMBER_DECLARATION), FOLLOW.at(RuleType::MEMBER_DECLARATION), RHS.at(RuleType::MEMBER_DECLARATION))},
        {"FUNCTION_OR_VARIABLE_DECLARATION", new Rule(RuleType::FUNCTION_OR_VARIABLE_DECLARATION, FIRST.at(RuleType::FUNCTION_OR_VARIABLE_DECLARATION), FOLLOW.at(RuleType::FUNCTION_OR_VARIABLE_DECLARATION), RHS.at(RuleType::FUNCTION_OR_VARIABLE_DECLARATION))},
        {"VISIBILITY", new Rule(RuleType::VISIBILITY, FIRST.at(RuleType::VISIBILITY), FOLLOW.at(RuleType::VISIBILITY), RHS.at(RuleType::VISIBILITY))},
        {"STATEMENT", new Rule(RuleType::STATEMENT, FIRST.at(RuleType::STATEMENT), FOLLOW.at(RuleType::STATEMENT), RHS.at(RuleType::STATEMENT))},
        {"STATEMENT_VARIABLE", new Rule(RuleType::STATEMENT_VARIABLE, FIRST.at(RuleType::STATEMENT_VARIABLE), FOLLOW.at(RuleType::STATEMENT_VARIABLE), RHS.at(RuleType::STATEMENT_VARIABLE))},
        {"STATEMENT_VARIABLE_OR_FUNCTION_CALL", new Rule(RuleType::STATEMENT_VARIABLE_OR_FUNCTION_CALL, FIRST.at(RuleType::STATEMENT_VARIABLE_OR_FUNCTION_CALL), FOLLOW.at(RuleType::STATEMENT_VARIABLE_OR_FUNCTION_CALL), RHS.at(RuleType::STATEMENT_VARIABLE_OR_FUNCTION_CALL))},
        {"STATEMENT_VARIABLE_EXT", new Rule(RuleType::STATEMENT_VARIABLE_EXT, FIRST.at(RuleType::STATEMENT_VARIABLE_EXT), FOLLOW.at(RuleType::STATEMENT_VARIABLE_EXT), RHS.at(RuleType::STATEMENT_VARIABLE_EXT))},
        {"STATEMENT_FUNCTION_CALL", new Rule(RuleType::STATEMENT_FUNCTION_CALL, FIRST.at(RuleType::STATEMENT_FUNCTION_CALL), FOLLOW.at(RuleType::STATEMENT_FUNCTION_CALL), RHS.at(RuleType::STATEMENT_FUNCTION_CALL))},
        {"ASSIGN_STATEMENT_OR_FUNCTION_CALL", new Rule(RuleType::ASSIGN_STATEMENT_OR_FUNCTION_CALL, FIRST.at(RuleType::ASSIGN_STATEMENT_OR_FUNCTION_CALL), FOLLOW.at(RuleType::ASSIGN_STATEMENT_OR_FUNCTION_CALL), RHS.at(RuleType::ASSIGN_STATEMENT_OR_FUNCTION_CALL))},
        {"VARIABLE_OR_FUNCTION_CALL_EXT", new Rule(RuleType::VARIABLE_OR_FUNCTION_CALL_EXT, FIRST.at(RuleType::VARIABLE_OR_FUNCTION_CALL_EXT), FOLLOW.at(RuleType::VARIABLE_OR_FUNCTION_CALL_EXT), RHS.at(RuleType::VARIABLE_OR_FUNCTION_CALL_EXT))},
        {"VARIABLE_EXT", new Rule(RuleType::VARIABLE_EXT, FIRST.at(RuleType::VARIABLE_EXT), FOLLOW.at(RuleType::VARIABLE_EXT), RHS.at(RuleType::VARIABLE_EXT))},
        {"FUNCTION_CALL_EXT", new Rule(RuleType::FUNCTION_CALL_EXT, FIRST.at(RuleType::FUNCTION_CALL_EXT), FOLLOW.at(RuleType::FUNCTION_CALL_EXT), RHS.at(RuleType::FUNCTION_CALL_EXT))},
        {"FUNCTION_PARAMS", new Rule(RuleType::FUNCTION_PARAMS, FIRST.at(RuleType::FUNCTION_PARAMS), FOLLOW.at(RuleType::FUNCTION_PARAMS), RHS.at(RuleType::FUNCTION_PARAMS))},
        {"ADD_OP", new Rule(RuleType::ADD_OP, FIRST.at(RuleType::ADD_OP), FOLLOW.at(RuleType::ADD_OP), RHS.at(RuleType::ADD_OP))},
        {"OPTIONAL_INHERITS", new Rule(RuleType::OPTIONAL_INHERITS, FIRST.at(RuleType::OPTIONAL_INHERITS), FOLLOW.at(RuleType::OPTIONAL_INHERITS), RHS.at(RuleType::OPTIONAL_INHERITS))},
        {"REL_EXPRESSION", new Rule(RuleType::REL_EXPRESSION, FIRST.at(RuleType::REL_EXPRESSION), FOLLOW.at(RuleType::REL_EXPRESSION), RHS.at(RuleType::REL_EXPRESSION))},
        {"FUNCTION_DECLARATION", new Rule(RuleType::FUNCTION_DECLARATION, FIRST.at(RuleType::FUNCTION_DECLARATION), FOLLOW.at(RuleType::FUNCTION_DECLARATION), RHS.at(RuleType::FUNCTION_DECLARATION))},
        {"FUNCTION_CALL_PARAMS_TAILS", new Rule(RuleType::FUNCTION_CALL_PARAMS_TAILS, FIRST.at(RuleType::FUNCTION_CALL_PARAMS_TAILS), FOLLOW.at(RuleType::FUNCTION_CALL_PARAMS_TAILS), RHS.at(RuleType::FUNCTION_CALL_PARAMS_TAILS))},
        {"LOCAL_SCOPE", new Rule(RuleType::LOCAL_SCOPE, FIRST.at(RuleType::LOCAL_SCOPE), FOLLOW.at(RuleType::LOCAL_SCOPE), RHS.at(RuleType::LOCAL_SCOPE))},
        {"ARRAY_DIMENSIONS", new Rule(RuleType::ARRAY_DIMENSIONS, FIRST.at(RuleType::ARRAY_DIMENSIONS), FOLLOW.at(RuleType::ARRAY_DIMENSIONS), RHS.at(RuleType::ARRAY_DIMENSIONS))},
        {"EXPRESSION", new Rule(RuleType::EXPRESSION, FIRST.at(RuleType::EXPRESSION), FOLLOW.at(RuleType::EXPRESSION), RHS.at(RuleType::EXPRESSION))},
        {"REL_EXPRESSION_OR_NULL", new Rule(RuleType::REL_EXPRESSION_OR_NULL, FIRST.at(RuleType::REL_EXPRESSION_OR_NULL), FOLLOW.at(RuleType::REL_EXPRESSION_OR_NULL), RHS.at(RuleType::REL_EXPRESSION_OR_NULL))},
        {"STATEMENTS", new Rule(RuleType::STATEMENTS, FIRST.at(RuleType::STATEMENTS), FOLLOW.at(RuleType::STATEMENTS), RHS.at(RuleType::STATEMENTS))},
        {"ARITH_EXPRESSION", new Rule(RuleType::ARITH_EXPRESSION, FIRST.at(RuleType::ARITH_EXPRESSION), FOLLOW.at(RuleType::ARITH_EXPRESSION), RHS.at(RuleType::ARITH_EXPRESSION))},
        {"RIGHT_REC_ARITH_EXPRESSION", new Rule(RuleType::RIGHT_REC_ARITH_EXPRESSION, FIRST.at(RuleType::RIGHT_REC_ARITH_EXPRESSION), FOLLOW.at(RuleType::RIGHT_REC_ARITH_EXPRESSION), RHS.at(RuleType::RIGHT_REC_ARITH_EXPRESSION))},
        {"FUNCTION_SIGNATURE", new Rule(RuleType::FUNCTION_SIGNATURE, FIRST.at(RuleType::FUNCTION_SIGNATURE), FOLLOW.at(RuleType::FUNCTION_SIGNATURE), RHS.at(RuleType::FUNCTION_SIGNATURE))},
        {"FUNCTION_SIGNATURE_NAMESPACE", new Rule(RuleType::FUNCTION_SIGNATURE_NAMESPACE, FIRST.at(RuleType::FUNCTION_SIGNATURE_NAMESPACE), FOLLOW.at(RuleType::FUNCTION_SIGNATURE_NAMESPACE), RHS.at(RuleType::FUNCTION_SIGNATURE_NAMESPACE))},
        {"FUNCTION_SIGNATURE_EXT", new Rule(RuleType::FUNCTION_SIGNATURE_EXT, FIRST.at(RuleType::FUNCTION_SIGNATURE_EXT), FOLLOW.at(RuleType::FUNCTION_SIGNATURE_EXT), RHS.at(RuleType::FUNCTION_SIGNATURE_EXT))},
        {"FUNCTION_PARAMS_TAILS", new Rule(RuleType::FUNCTION_PARAMS_TAILS, FIRST.at(RuleType::FUNCTION_PARAMS_TAILS), FOLLOW.at(RuleType::FUNCTION_PARAMS_TAILS), RHS.at(RuleType::FUNCTION_PARAMS_TAILS))},
        {"INHERITED_CLASSES", new Rule(RuleType::INHERITED_CLASSES, FIRST.at(RuleType::INHERITED_CLASSES), FOLLOW.at(RuleType::INHERITED_CLASSES), RHS.at(RuleType::INHERITED_CLASSES))},
        {"SIGN", new Rule(RuleType::SIGN, FIRST.at(RuleType::SIGN), FOLLOW.at(RuleType::SIGN), RHS.at(RuleType::SIGN))},
        {"COMPARE_OP", new Rule(RuleType::COMPARE_OP, FIRST.at(RuleType::COMPARE_OP), FOLLOW.at(RuleType::COMPARE_OP), RHS.at(RuleType::COMPARE_OP))},
        {"INDEX", new Rule(RuleType::INDEX, FIRST.at(RuleType::INDEX), FOLLOW.at(RuleType::INDEX), RHS.at(RuleType::INDEX))},
        {"VARIABLE_DECLARATIONS", new Rule(RuleType::VARIABLE_DECLARATIONS, FIRST.at(RuleType::VARIABLE_DECLARATIONS), FOLLOW.at(RuleType::VARIABLE_DECLARATIONS), RHS.at(RuleType::VARIABLE_DECLARATIONS))},
        {"FACTOR", new Rule(RuleType::FACTOR, FIRST.at(RuleType::FACTOR), FOLLOW.at(RuleType::FACTOR), RHS.at(RuleType::FACTOR))},
        {"VARIABLE_FUNCTION_CALL", new Rule(RuleType::VARIABLE_FUNCTION_CALL, FIRST.at(RuleType::VARIABLE_FUNCTION_CALL), FOLLOW.at(RuleType::VARIABLE_FUNCTION_CALL), RHS.at(RuleType::VARIABLE_FUNCTION_CALL))},
        {"VARIABLE_OR_FUNCTION_CALL", new Rule(RuleType::VARIABLE_OR_FUNCTION_CALL, FIRST.at(RuleType::VARIABLE_OR_FUNCTION_CALL), FOLLOW.at(RuleType::VARIABLE_OR_FUNCTION_CALL), RHS.at(RuleType::VARIABLE_OR_FUNCTION_CALL))},
        {"FACTOR_VARIABLE", new Rule(RuleType::FACTOR_VARIABLE, FIRST.at(RuleType::FACTOR_VARIABLE), FOLLOW.at(RuleType::FACTOR_VARIABLE), RHS.at(RuleType::FACTOR_VARIABLE))},
        {"FACTOR_FUNCTION_CALL", new Rule(RuleType::FACTOR_FUNCTION_CALL, FIRST.at(RuleType::FACTOR_FUNCTION_CALL), FOLLOW.at(RuleType::FACTOR_FUNCTION_CALL), RHS.at(RuleType::FACTOR_FUNCTION_CALL))},
        {"TERM", new Rule(RuleType::TERM, FIRST.at(RuleType::TERM), FOLLOW.at(RuleType::TERM), RHS.at(RuleType::TERM))},
        {"MULT_OP", new Rule(RuleType::MULT_OP, FIRST.at(RuleType::MULT_OP), FOLLOW.at(RuleType::MULT_OP), RHS.at(RuleType::MULT_OP))},
        {"RIGHT_REC_TERM", new Rule(RuleType::RIGHT_REC_TERM, FIRST.at(RuleType::RIGHT_REC_TERM), FOLLOW.at(RuleType::RIGHT_REC_TERM), RHS.at(RuleType::RIGHT_REC_TERM))},
        {"TYPE_OR_VOID", new Rule(RuleType::TYPE_OR_VOID, FIRST.at(RuleType::TYPE_OR_VOID), FOLLOW.at(RuleType::TYPE_OR_VOID), RHS.at(RuleType::TYPE_OR_VOID))},
        {"TYPE", new Rule(RuleType::TYPE, FIRST.at(RuleType::TYPE), FOLLOW.at(RuleType::TYPE), RHS.at(RuleType::TYPE))},
        {"TYPE_NON_ID", new Rule(RuleType::TYPE_NON_ID, FIRST.at(RuleType::TYPE_NON_ID), FOLLOW.at(RuleType::TYPE_NON_ID), RHS.at(RuleType::TYPE_NON_ID))},
        {"ARRAY_SIZE", new Rule(RuleType::ARRAY_SIZE, FIRST.at(RuleType::ARRAY_SIZE), FOLLOW.at(RuleType::ARRAY_SIZE), RHS.at(RuleType::ARRAY_SIZE))},
        {"OPTIONAL_INT", new Rule(RuleType::OPTIONAL_INT, FIRST.at(RuleType::OPTIONAL_INT), FOLLOW.at(RuleType::OPTIONAL_INT), RHS.at(RuleType::OPTIONAL_INT))},
        {"FUNCTION_CALL_PARAMS_TAIL", new Rule(RuleType::FUNCTION_CALL_PARAMS_TAIL, FIRST.at(RuleType::FUNCTION_CALL_PARAMS_TAIL), FOLLOW.at(RuleType::FUNCTION_CALL_PARAMS_TAIL), RHS.at(RuleType::FUNCTION_CALL_PARAMS_TAIL))},
        {"FUNCTION_CALL_PARAMS", new Rule(RuleType::FUNCTION_CALL_PARAMS, FIRST.at(RuleType::FUNCTION_CALL_PARAMS), FOLLOW.at(RuleType::FUNCTION_CALL_PARAMS), RHS.at(RuleType::FUNCTION_CALL_PARAMS))},
        {"VARIABLE_DECLARATION", new Rule(RuleType::VARIABLE_DECLARATION, FIRST.at(RuleType::VARIABLE_DECLARATION), FOLLOW.at(RuleType::VARIABLE_DECLARATION), RHS.at(RuleType::VARIABLE_DECLARATION))},
        {"FUNCTION_BODY", new Rule(RuleType::FUNCTION_BODY, FIRST.at(RuleType::FUNCTION_BODY), FOLLOW.at(RuleType::FUNCTION_BODY), RHS.at(RuleType::FUNCTION_BODY))},
        {"STATEMENT_BLOCK", new Rule(RuleType::STATEMENT_BLOCK, FIRST.at(RuleType::STATEMENT_BLOCK), FOLLOW.at(RuleType::STATEMENT_BLOCK), RHS.at(RuleType::STATEMENT_BLOCK))},
        {"ASSIGNMENT_OP", new Rule(RuleType::ASSIGNMENT_OP, FIRST.at(RuleType::ASSIGNMENT_OP), FOLLOW.at(RuleType::ASSIGNMENT_OP), RHS.at(RuleType::ASSIGNMENT_OP))},
        {"FUNCTION_PARAMS_TAIL", new Rule(RuleType::FUNCTION_PARAMS_TAIL, FIRST.at(RuleType::FUNCTION_PARAMS_TAIL), FOLLOW.at(RuleType::FUNCTION_PARAMS_TAIL), RHS.at(RuleType::FUNCTION_PARAMS_TAIL))},
        {"INDICES", new Rule(RuleType::INDICES, FIRST.at(RuleType::INDICES), FOLLOW.at(RuleType::INDICES), RHS.at(RuleType::INDICES))},
};

const std::unordered_set<std::string> TERMINALS = {
        "if",
        "then",
        "else",
        "__Integer",
        "__Float",
        "while",
        "class",
        "do",
        "end",
        "public",
        "private",
        "or",
        "and",
        "not",
        "read",
        "write",
        "return",
        "main",
        "inherits",
        "local",
        "error",
        "void",
        "==",
        "<>",
        "<",
        ">",
        "<=",
        ">=",
        "+",
        "-",
        "*",
        "/",
        "=",
        "(",
        ")",
        "{",
        "}",
        "[",
        "]",
        ";",
        ",",
        ".",
        ":",
        "::",
        "#",
};

#endif //SKY_GRAMMAR_H
