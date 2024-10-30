#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

unordered_map <string, unordered_map<string, string>> getTable() {
    unordered_map<string, unordered_map<string, string>> grammarRules = {
        {"S", {{"typeInt", "<BEGIN>"}}},
        {"RESERVED_TYPES", {{"typeInt", "typeInt"}, {"typeDouble", "typeDouble"}}},
        {"BEGIN", {{"typeInt", "typeInt reserved_main symbol_parameter_init symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"}}},
        {"CODE_BLOCK", {{"typeInt", "<ATTRIBUTION> <CODE_BLOCK>"},
                        {"typeDouble", "<ATTRIBUTION> <CODE_BLOCK>"},
                        {"id", "<ATTRIBUTION> <CODE_BLOCK>"},
                        {"typeBoolean", "<ATTRIBUTION_BOOL> <CODE_BLOCK>"},
                        {"reserved_prt", "<PRINT> <CODE_BLOCK>"},
                        {"reserved_scn", "<SCAN> <CODE_BLOCK>"},
                        {"laps", "<LAPS> <CODE_BLOCK>"},
                        {"circuit", "<CIRCUIT> <CODE_BLOCK>"},
                        {"pitEntry", "<PIT> <CODE_BLOCK>"},
                        {"typeStr", "<ATTRIBUTION_STR> <CODE_BLOCK>"},
                        {"symbol_op_end", "ε"}}},
                    
        {"EXPRESSION", {{"symbol_parameter_init", "<BOOL_EXPR> <EXPRESSION'> end_line "},
                        {"id", "<BOOL_EXPR> <EXPRESSION'> end_line "},
                        {"double", "<BOOL_EXPR> <EXPRESSION'> end_line "},
                        {"integer", "<BOOL_EXPR> <EXPRESSION'> end_line "},
                        {"bool_false", "<BOOL_EXPR> <EXPRESSION'> end_line"},
                        {"bool_true", "<BOOL_EXPR> <EXPRESSION'> end_line"}}},

        {"EXPRESSION'", {{"op_arit_sum", "op_arit_sum <MULT_DIV> <EXPRESSION'>"},
                        {"op_arit_sub", "op_arit_sub <MULT_DIV> <EXPRESSION'>"},
                        {"end_line", "ε"}}},

        {"BOOL_EXPR", {{"symbol_parameter_init", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"id", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"double", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"integer", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"bool_false", "<MULT_DIV> <BOOL_EXPR'>"},
                        {"bool_true", "<MULT_DIV> <BOOL_EXPR'>"}}},

        {"BOOL_EXPR'", {{"op_log_e", "op_bool_e <MULT_DIV> <BOOL_EXPR'>"},
                        {"op_log_or", "op_bool_or <MULT_DIV> <BOOL_EXPR'>"},
                        {"op_arit_sum", "ε"},
                        {"op_arit_sub", "ε"},
                        {"end_line", "ε"}}},

        {"MULT_DIV", {{"symbol_parameter_init", "<POW> <MULT_DIV>'"}, 
                        {"id", "<POW> <MULT_DIV>'"}, 
                        {"double", "<POW> <MULT_DIV>'"}, 
                        {"integer", "<POW> <MULT_DIV>'"},
                        {"bool_false", "<POW> <MULT_DIV'>"},
                        {"bool_true", "<POW> <MULT_DIV'>"}}},

        {"MULT_DIV'", {{"op_arit_mult", "op_arit_mult <POW> <MULT_DIV'>"}, 
                        {"op_arit_div", "op_arit_div <POW> <MULT_DIV'>"}, 
                        {"end_line", "ε"},
                        {"op_arit_sum", "ε"},
                        {"op_arit_sub", "ε"},
                        {"op_log_e", "ε"},
                        {"op_log_or", "ε"}}},

        {"POW", {{"symbol_parameter_init", "<VAR> <POW>'"}, 
                {"id", "<VAR> <POW>'"}, 
                {"double", "<VAR> <POW>'"}, 
                {"integer", "<VAR> <POW>'"},
                {"bool_false", "<VAR> <POW>"},
                {"bool_true", "<VAR> <POW>"}}},

        {"POW'", {{"op_arit_pow", "op_arit_pow <VAR> <POW'>"}, 
                        {"end_line", "ε"},
                        {"op_arit_mult", "ε"},
                        {"op_arit_div", "ε"},
                        {"op_arit_sum", "ε"},
                        {"op_arit_sub", "ε"},
                        {"op_log_e", "ε"},
                        {"op_log_or", "ε"}}},

        {"VAR", {{"symbol_parameter_init", "symbol_parameter_init <EXPRESSION> symbol_parameter_end"},
                 {"id", "id"},	
                 {"double", "double"},
                 {"integer", "integer"},
                 {"bool_false", "<VAR> <POW>"},
                {"bool_true", "<VAR> <POW>"}}},

        {"ATTRIBUTION", {{"typeInt", "<RESERVED_TYPES> <ATTRIBUTION>'"},
                 {"typeDouble", "<RESERVED_TYPES> <ATTRIBUTION>'"},
                 {"id", "<ATTRIBUTION'>"}}},

        {"ATTRIBUTION'", {{"id", "id <ATTRIBUTION''>"}}},

        {"ATTRIBUTION''", {{"op_rel_equal", "op_rel_equal <ATTRIBUTION_VALUE> end_line"},
                 {"end_line", "end_line"}}},

        {"ATTRIBUTION_BOOL", {{"typeBoolean", "typeBoolean id <ATTRIBUTION_BOOL'>"},
                 {"symbol_parameter_end", "ε"},
                 {"typeInt", "ε"},
                 {"typeDouble", "ε"},
                 {"reserved_prt", "ε"},
                 {"reserved_scn", "ε"},
                 {"laps", "ε"},
                 {"circuit", "ε"},
                 {"pitEntry", "ε"},
                 {"typeStr", "ε"},
                 {"id", "ε"}}},

        {"ATTRIBUTION_BOOL'", {{"op_rel_equal", "op_rel_equal <ATTRIBUTION_BOOL''> "},
                              {"end_line", "endline"},
                            {"symbol_parameter_end", "ε"},
                 {"typeInt", "ε"},
                 {"typeDouble", "ε"},
                 {"typeBoolean", "ε"},
                 {"reserved_prt", "ε"},
                 {"reserved_scn", "ε"},
                 {"laps", "ε"},
                 {"circuit", "ε"},
                 {"pitEntry", "ε"},
                 {"typeStr", "ε"},
                 {"id", "ε"}}},


        {"ATTRIBUTION_BOOL''", {{"bool_false", "bool_false end_line"},
                               {"bool_true", "bool_true end_line"},
                 {"symbol_parameter_end", "ε"},
                 {"typeInt", "ε"},
                 {"typeDouble", "ε"},
                 {"typeBoolean", "ε"},
                 {"reserved_prt", "ε"},
                 {"reserved_scn", "ε"},
                 {"laps", "ε"},
                 {"circuit", "ε"},
                 {"pitEntry", "ε"},
                 {"typeStr", "ε"},
                 {"id", "ε"}}},

        {"ATTRIBUTION_STR", {{"typeStr", "typeStr id <ATTRIBUTION_STR'>"},
                         {"symbol_parameter_end", "ε"},
                 {"typeInt", "ε"},
                 {"typeDouble", "ε"},
                 {"typeBoolean", "ε"},
                 {"reserved_prt", "ε"},
                 {"reserved_scn", "ε"},
                 {"laps", "ε"},
                 {"circuit", "ε"},
                 {"pitEntry", "ε"},
                 {"id", "ε"}}},

        {"ATTRIBUTION_STR'", {{"op_rel_equal", "op_rel_equal text_between_quotes end_line"},
                              {"end_line", "end_line"},
                                               {"symbol_parameter_end", "ε"},
                 {"typeInt", "ε"},
                 {"typeDouble", "ε"},
                 {"typeBoolean", "ε"},
                 {"reserved_prt", "ε"},
                 {"reserved_scn", "ε"},
                 {"laps", "ε"},
                 {"circuit", "ε"},
                 {"pitEntry", "ε"},
                 {"typeStr", "ε"},
                 {"id", "ε"}}},

        {"PRINT", {{"reserved_prt", "reserved_prt symbol_parameter_init <ID_OR_STRING> symbol_parameter_end end_line"}}},

        {"ID_OR_STRING", {{"id", "id <ID_OR_STRING'>"},
                          {"double", "double <ID_OR_STRING'>"},
                          {"integer", "integer <ID_OR_STRING'>"},
                          {"text_between_quotes", "text_between_quotes <ID_OR_STRING'>"}}},

        {"ID_OR_STRING'", {{"op_arit_sum", "op_arit_sum <ID_OR_STRING''> <ID_OR_STRING'>"},
                           {"symbol_parameter_end", "ε"}}},   

        {"ID_OR_STRING''", {{"id", "id"},
                            {"double", "double"},
                            {"integer", "integer"},
                            {"text_between_quotes", "text_between_quotes"}}},


        {"SCAN", {{"reserved_scn", "reserved_scn symbol_parameter_init id symbol_parameter_end end_line"}}},

        {"LAPS", {{"laps", "laps symbol_parameter_init <INIT_LAPS> op_rel_equal <ID_OR_VALUE> symbol_op_mid id <REL_SYMBOLS> <ID_OR_VALUE> symbol_op_mid id op_rel_equal <LAPS_INC> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"}}},
        
        {"INIT_LAPS", {{"typeInt", "typeInt id"},
                       {"id", "id"}}},

        {"LAPS_INC", {{"id", "id"},
                       {"brake", "brake"},
                       {"overtake", "overtake"}}},

        {"LAPS_SYMBOLS", {{"op_arit_sum", "op_arit_sum"},
                       {"op_arit_sub", "op_arit_sub"},
                       {"op_arit_mult", "op_arit_mult"},
                       {"op_arit_div", "op_arit_div"}}},
        
        {"ID_OR_VALUE", {{"id", "id"},
                         {"integer", "integer"}}},

        {"INIT_LAPS", {{"id", "id"},
                       {"integer", "integer"}}},
         
        {"CIRCUIT", {{"circuit", "circuit symbol_parameter_init <CIRCUIT_LOG> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end"}}},

        {"CIRCUIT_LOG", {{"id", "id <CIRCUIT_LOG'>"},
                         {"integer", "integer <CIRCUIT_LOG'>"},
                         {"double", "double <CIRCUIT_LOG'>"}}},

        {"CIRCUIT_LOG'", {{"op_arit_sum", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_sub", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_mult", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_div", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_arit_pow", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_minor", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_bigger", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_double_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_minor_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_bigger_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_not_equal", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_and", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"op_rel_or", "<LOOPS_SYMBOLS> <CIRCUIT_LOG>"},
                           {"symbol_parameter_end", "ε"}}},

        {"LOOPS_SYMBOLS", {{"op_arit_sum", "<ARIT_SYMBOLS>"},
                           {"op_arit_sub", "<ARIT_SYMBOLS>"},
                           {"op_arit_mult", "<ARIT_SYMBOLS>"},
                           {"op_arit_div", "<ARIT_SYMBOLS>"},
                           {"op_arit_pow", "<ARIT_SYMBOLS>"},
                           {"op_rel_minor", "<REL_SYMBOLS>"},
                           {"op_rel_bigger", "<REL_SYMBOLS>"},
                           {"op_rel_equal", "<REL_SYMBOLS>"},
                           {"op_rel_double_equal", "<REL_SYMBOLS>"},
                           {"op_rel_minor_equal", "<REL_SYMBOLS>"},
                           {"op_rel_bigger_equal", "<REL_SYMBOLS>"},
                           {"op_rel_not_equal", "<REL_SYMBOLS>"},
                           {"op_rel_and", "<LOG_SYMBOLS>"}, 
                           {"op_rel_or", "<LOG_SYMBOLS>"}}},  

        {"ARIT_SYMBOLS", {{"op_arit_sum", "op_arit_sum"},
                           {"op_arit_sub", "op_arit_sub"},
                           {"op_arit_mult", "op_arit_mult"},
                           {"op_arit_div", "op_arit_div"},
                           {"op_arit_pow", "op_arit_pow"}}},

        {"REL_SYMBOLS", {{"op_rel_minor", "op_rel_minor"},
                         {"op_rel_bigger", "op_rel_bigger"},
                         {"op_rel_double_equal", "op_rel_double_equal"},
                         {"op_rel_minor_equal", "op_rel_minor_equal"},
                         {"op_rel_bigger_equal", "op_rel_bigger_equal"},
                         {"op_rel_not_equal", "op_rel_not_equal"}}},

        {"LOG_SYMBOLS", {{"op_log_e", "op_log_e"},
                 {"op_log_or", "op_log_or"}}},

        {"PIT", {{"pitEntry", "pitEntry symbol_parameter_init <PIT_LOG> symbol_parameter_end symbol_op_init <CODE_BLOCK> symbol_op_end <PIT_EXIT>"}}},
        
        {"PIT_LOG", {{"id", "id <PIT_LOG'>"},
                     {"integer", "integer <PIT_LOG'>"},
                     {"double", "double <PIT_LOG'>"}}},

        {"PIT_LOG'", {{"op_arit_sum", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_sub", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_mult", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_div", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_arit_pow", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_minor", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_bigger", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_double_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_minor_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_bigger_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_not_equal", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_and", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"op_rel_or", "<LOOPS_SYMBOLS> <PIT_LOG>"},
                      {"symbol_parameter_end", "ε"}}},

        {"PIT_EXIT", {{"pitExit", "pitExit symbol_op_init <CODE_BLOCK> symbol_op_end"},
                        {"symbol_op_end", "ε"}}},


    };
    return grammarRules;
}

struct GrammarRule {
   string nonTerminal;
   string terminal;
   string production;
};


