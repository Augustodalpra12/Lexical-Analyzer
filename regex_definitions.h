

#ifndef REGEX_DEFINITIONS_H
#define REGEX_DEFINITIONS_H

#include <regex>

using namespace std;

regex integer("[0-9]+");
regex double_regex("(\\+|-)?[0-9]+(\\,[0-9]+)?(E(\\+|-)?[0-9]+)?");
regex char_regex("[a-zA-Z]");
regex digit("[0-9]");

regex quotes_regex("\".*\"");
regex at_regex(R"(@\s*(.*?)\s*@)");


regex symbol_id("[\\_]");
regex symbol_parameter_init("[(]");
regex symbol_parameter_end("[)]");

regex symbol_op_init("[{]");
regex symbol_op_end("[}]");
regex symbol_op_mid("[;]");

regex id("[a-zA-Z]([a-zA-Z0-9]|[_])*");
regex comma(",");

regex reserved_loops("(laps|circuit)"); 
regex reserved_condition("(pitEntry|pitExit)"); 
regex reserved_arit("(overtake|brake)"); 
regex reserved_main("(race)"); 
regex reserved_comment("\\@");
regex reserved_types("(int|double|char|boolean|str)");
regex reserved_prt("(prt)");
regex reserved_scn("(scn)");  


regex op_log_e("&");
regex op_log_e_function("&&");

regex op_log_or("\\|");
regex op_log_or_function("\\|\\|"); // ou ("\\|\\|")

regex end_line("\\.");

regex op_arit_sum("\\+");
regex op_arit_sub("-");
regex op_arit_mult("\\*");
regex op_arit_div("/");
regex op_arit_pow("\\^");

regex op_rel_minor("<");
regex op_rel_bigger(">");
regex op_rel_equal("=");
regex op_rel_not("\\!");

regex op_rel_double_equal("==");
regex op_rel_minor_equal("<=");
regex op_rel_bigger_equal(">=");
regex op_rel_not_equal("!=");


regex line_feed("(\r\n|\n)");
regex line_feed2("[\r\n]+");

regex spaces("[\\s\t\r\n]+");
regex portuguese("/^[A-Za-záàâãéèêíïóôõöúçñÁÀÂÃÉÈÍÏÓÔÕÖÚÇÑ ]+$/");
regex quotes(R"(\")");

regex all_except_at("[^@]");

regex all_except_quotes(R"([^"]+)");


#endif // REGEX_DEFINITIONS_H