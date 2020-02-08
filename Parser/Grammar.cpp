//
// Created by Morteza Ahmadi on 2020-02-07.
//

#include "Grammar.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>

Rule* rule = new Rule(RuleType::START, {"main"}, {"id"}, {"PROGRAM"});
const std::unordered_map<std::string, Rule*> RULES = {

        {"START", new Rule(RuleType::START, {"main", "class", "id"}, {"$"}, {"PROGRAM"})},
        {"PROGRAM", new Rule(RuleType::PROGRAM, {"main", "class", "id"}, {"$"}, {"CLASS_DECLARATIONS FUNCTION"})}
};

std::unordered_map<RuleType, std::vector<std::string>> RHS = {
        {RuleType::START, {"PROGRAM"}},
        {RuleType::PROGRAM, {"CLASS_DECLARATIONS FUNCTION_DEFINITIONS main FUNCTION_BODY"}},
        {RuleType::CLASS_DECLARATIONS, {"CLASS_DECLARATION CLASS_DECLARATIONS", "#"}},
        {RuleType::CLASS_DECLARATION, {"class id OPTIONAL_INHERITS { MEMBER_DECLARATIONS } ;"}},
        {RuleType::FUNCTION_DEFINITIONS, {"FUNCTION_DEFINITION FUNCTION_DEFINITIONS", "#"}},
        {RuleType::FUNCTION_DEFINITION, {"FUNCTION_SIGNATURE FUNCTION_BODY ;"}},
        {RuleType::MEMBER_DECLARATIONS, {"VISIBILITY MEMBER_DECLARATION MEMBER_DECLARATIONS", "#"}},
        {RuleType::MEMBER_DECLARATION, {"id FUNCTION_OR_VARIABLE_DECLARATION", "TYPE_NON_ID VARIABLE_DECLARATION"}},
        {RuleType::FUNCTION_OR_VARIABLE_DECLARATION, {"FUNCTION_DECLARATION", "VARIABLE_DECLARATION"}},
        {RuleType::VISIBILITY, {"public", "private"}},
        {RuleType::STATEMENT, {"if ( REL_EXPRESSION ) then STATEMENT_BLOCK else STATEMENT_BLOCK ;",
                               "while ( REL_EXPRESSION ) STATEMENT_BLOCK ;",
                               "read ( STATEMENT_VARIABLE ) ;",
                               "write ( EXPRESSION ) ;",
                               "return ( EXPRESSION ) ;",
                               "ASSIGN_STATEMENT_OR_FUNCTION_CALL"}},
        {RuleType::STATEMENT_VARIABLE, {"id STATEMENT_VARIABLE_OR_FUNCTION_CALL"}},
        {RuleType::STATEMENT_VARIABLE_OR_FUNCTION_CALL, {"INDICES STATEMENT_VARIABLE_EXT",
                                                         "( FUNCTION_CALL_PARAMS ) STATEMENT_FUNCTION_CALL"}},
        {RuleType::STATEMENT_VARIABLE_EXT, {". STATEMENT_VARIABLE", "#"}},
        {RuleType::STATEMENT_FUNCTION_CALL, {". STATEMENT_VARIABLE"}},
        {RuleType::ASSIGN_STATEMENT_OR_FUNCTION_CALL, {"id VARIABLE_OR_FUNCTION_CALL_EXT"}},
        {RuleType::VARIABLE_OR_FUNCTION_CALL_EXT, {"INDICES VARIABLE_EXT",
                                                   "( FUNCTION_CALL_PARAMS ) FUNCTION_CALL_EXT"}},
        {RuleType::VARIABLE_EXT, {"ASSIGNMENT_OP EXPRESSION ;", ". ASSIGN_STATEMENT_OR_FUNCTION_CALL"}},
        {RuleType::FUNCTION_CALL_EXT, {";", ". ASSIGN_STATEMENT_OR_FUNCTION_CALL"}},
        {RuleType::FUNCTION_PARAMS, {"TYPE id ARRAY_DIMENSIONS FUNCTION_PARAMS_TAILS", "#"}},
        {RuleType::ADD_OP, {"+", "-", "or"}},
        {RuleType::OPTIONAL_INHERITS, {"inherits id INHERITED_CLASSES", "#"}},
        {RuleType::REL_EXPRESSION, {"ARITH_EXPRESSION COMPARE_OP INHERITED_CLASSES", "#"}},
        {RuleType::FUNCTION_DECLARATION, {"( FUNCTION_PARAMS ) : TYPE_OR_VOID ;"}},
        {RuleType::FUNCTION_CALL_PARAMS_TAILS, {"FUNCTION_CALL_PARAMS_TAIL FUNCTION_CALL_PARAM_TAILS", "#"}},
        {RuleType::LOCAL_SCOPE, {"local VARIABLE_DECLARATIONS", "#"}},
        {RuleType::ARRAY_DIMENSIONS, {"ARRAY_SIZE ARRAY_DIMENSIONS", "#"}},
        {RuleType::EXPRESSION, {"ARITH_EXPRESSION REL_EXPRESSION_OR_NULL"}},
        {RuleType::REL_EXPRESSION_OR_NULL, {"COMPARE_OP ARITH_EXPRESSION", "#"}},
        {RuleType::STATEMENTS, {"STATEMENT STATEMENTS", "#"}},
        {RuleType::ARITH_EXPRESSION, {"TERM RIGHT_REC_ARITH_EXPRESSION"}},
        {RuleType::RIGHT_REC_ARITH_EXPRESSION, {"ADD_OP TERM RIGHT_REC_ARITH_EXPRESSION", "#"}},
        {RuleType::FUNCTION_SIGNATURE, {"id FUNCTION_SIGNATURE_NAMESPACE"}},
        {RuleType::FUNCTION_SIGNATURE_NAMESPACE, {"FUNCTION_SIGNATURE_EXT", ":: id FUNCTION_SIGNATURE_EXT"}},
        {RuleType::FUNCTION_SIGNATURE_EXT, {"( FUNCTION_PARAMS ) : TYPE_OR_VOID"}},
        {RuleType::FUNCTION_PARAMS_TAILS, {"FUNCTION_PARAMS_TAIL FUNCTION_PARAMS_TAILS", "#"}},
        {RuleType::INHERITED_CLASSES, {", id INHERITED_CLASSES"}},
        {RuleType::SIGN, {"+", "-"}},
        {RuleType::COMPARE_OP, {"==", "<>", "<", ">", "<=", ">="}},
        {RuleType::INDEX, {"[ ARITH_EXPRESSION ]"}},
        {RuleType::VARIABLE_DECLARATIONS, {"VARIABLE_DECLARATION VARIABLE_DECLARATIONS", "#"}},
        {RuleType::FACTOR, {"VARIABLE_FUNCTION_CALL", "integer", "float", "( ARITH_EXPRESSION )", "not FACTOR", "SIGN FACTOR"}},
        {RuleType::VARIABLE_FUNCTION_CALL, {"id VARIABLE_OR_FUNCTION_CALL"}},

};