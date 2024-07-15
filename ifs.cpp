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

    char c;
    int estado_atual = 1;
    while(!arquivo.eof()) {
        // saiu e foi pro 2
        // ou seja pega tudo que foi lido, e transforma em um token
        while(estado_atual == 1 || estado_atual == 3 || estado_atual == 4 || estado_atual == 5 || estado_atual == 7 || estado_atual == 8 || estado_atual == 10 || estado_atual == 12 || estado_atual == 13) {
        arquivo.get(c);
         // cout << c;
            if(regex_match(string(1, c), op_arit_sum)) { // Lendo um + 
                estado_atual = 3; 
                arquivo.get(c);
                //armazena
                if(regex_match(string(1, c), integer)) { // Lendo um inteiro
                    estado_atual = 5;
                    arquivo.get(c);
                    //armazena
                    while(estado_atual == 5){
                        if(regex_match(string(1, c), integer)){ // lendo um inteiro loop
                        estado_atual = 5;
                        arquivo.get(c);
                        // armazena
                        }
                        if(regex_match(string(1, c), comma)) { // lendo uma virgula
                        estado_atual = 7;
                        arquivo.get(c);
                            if(regex_match(string(1, c), integer)){ // lendo um inteiro
                            estado_atual = 8;
                            arquivo.get(c);
                            // armazena
                                while(estado_atual == 8){ 
                                    if(regex_match(string(1, c), integer)){ // lendo um inteiro loop
                                    estado_atual = 8;
                                    arquivo.get(c);
                                    // armazena
                                    }
                                    else{
                                    estado_atual = 2;
                                    }
                                }
                            }
                            else{
                            estado_atual = 2;
                            }
                        }
                    }

                }
                else{
                    estado_atual = 2;
                }
            }
            if(regex_match(string(1, c), op_arit_sub)) { // Lendo um -
                estado_atual = 4;
                arquivo.get(c);
                //armazena
            }
            else{
                estado_atual = 2;
            }
        }
    }
    arquivo.close();

    return 0;
}