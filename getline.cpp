#include <iostream>
#include <string>
#include <regex>

using namespace std;

#include <fstream>


regex integer("[0-9]+");
regex integer_signal("(\\+|-)?[0-9]+");
regex double_regex("(\\+|-)?[0-9]+(,[0-9]+)?(E(\\+|-)?[0-9]+)?");
regex char_regex("[a-zA-Z]");
regex digit("[0-9]");

regex symbol_id("[_]");
regex symbol_parameter_init("[(]");
regex symbol_parameter_end("[)]");

regex symbol_op_init("[{]");
regex symbol_op_end("[}]");

regex id("[a-zA-Z]([a-zA-Z0-9]|[_])*");
regex comma(",");

regex reserved_loops("(laps|circuit)");
regex reserved_condition("(pitEntry|pitExit)");
regex reserved_arit("(overtake|brake)");
regex reserved_main("(race)");
regex reserved_comment("(Radio)");
regex reserved_types("(int|double|char|boolean|str)");

regex op_log_and("&&");
regex op_log_or("\\|\\|");  // Dupla contrabarra para escapar o pipe "|"
regex op_log_not("!");

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

regex spaces("[\\s\t\n]+");
regex all_symbols(".");
regex comment("Radio[{][.\\s\t\n]*[}]");

regex op_arit_sum("\\+");


int main() {
    ifstream arquivo("nome_do_arquivo.txt");

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    string linha;
    smatch match;

    while (getline(arquivo, linha)) {
        // Usamos um stringstream para ler caractere por caractere
        stringstream ss(linha);
        char c;

        while (ss.get(c)) {
            string token(1, c); // Inicia o token com o caractere atual

            // Verifica qual expressão regular corresponde ao token
            if (regex_match(token, integer_regex)) {
                cout << "Token encontrado: " << token << " (INT)" << endl;
            } else if (regex_match(token, double_regex)) {
                cout << "Token encontrado: " << token << " (DOUBLE)" << endl;
            } else if (regex_match(token, char_regex)) {
                cout << "Token encontrado: " << token << " (CHAR)" << endl;
            } else if (regex_match(token, id_regex)) {
                // Verifica se é uma palavra reservada
                if (regex_match(token, reserved_regex)) {
                    cout << "Token encontrado: " << token << " (PALAVRA RESERVADA)" << endl;
                } else {
                    cout << "Token encontrado: " << token << " (ID)" << endl;
                }
            } else if (regex_match(token, symbol_regex)) {
                cout << "Token encontrado: " << token << " (SÍMBOLO)" << endl;
            } else if (regex_match(token, op_arit_regex)) {
                cout << "Token encontrado: " << token << " (OP ARITMÉTICO)" << endl;
            } else if (regex_match(token, op_rel_regex)) {
                cout << "Token encontrado: " << token << " (OP RELACIONAL)" << endl;
            } else if (regex_match(token, op_log_regex)) {
                cout << "Token encontrado: " << token << " (OP LÓGICO)" << endl;
            } else {
                cout << "Token não reconhecido: " << token << endl;
            }
        }
    }

    arquivo.close();

    return 0;
}