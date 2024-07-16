#ifndef REGEX_DEFINITIONS_H
#define REGEX_DEFINITIONS_H

#include <regex>

using namespace std;

regex integer("[0-9]+");
regex integer_signal("(\\+|-)?[0-9]+");
regex double_regex("(\\+|-)?[0-9]+(\\.[0-9]+)?(E(\\+|-)?[0-9]+)?");
regex char_regex("[a-zA-Z]");
regex digit("[0-9]");

regex symbol_id("[_]");
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
regex reserved_comment("(Radio)");
regex reserved_types("(int|double|char|boolean|str)");
regex reserved_prt("(prt)");
regex reserved_scn("(scn)");  


regex op_log_and("&&");
regex op_log_or("\\|\\|");  // Dupla contrabarra para escapar o pipe "|"
regex op_log_not("!");

regex end_line("\\.");

regex op_arit_sum("\\+");
regex op_arit_sub("-");
regex op_arit_mult("\\*");
regex op_arit_div("/");
regex op_arit_pow("\\^");

regex op_rel_minor("<");
regex op_rel_bigger(">");
regex op_rel_equal("=");
regex op_rel_mEqual("≤");
regex op_rel_bEqual("≥");
regex op_rel_notEqual("≠");

regex spaces("[\\s\t\r\n]+");
// regex space(" ");
// regex space("\\s"); // espaço n ta funcionando
regex all_symbols(".");
regex comment("Radio[{][.\\s\t\n]*[}]");

#endif // REGEX_DEFINITIONS_H
