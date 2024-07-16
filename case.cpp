#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;


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
regex space("\\s"); // espaço n ta funcionando
regex all_symbols(".");
regex comment("Radio[{][.\\s\t\n]*[}]");

bool get_token(string token){

  return true;   
}

bool get_integer(string token){

  return true;
}

bool get_double(string token){

  return true;
}

int main(){

    ifstream arquivo("nome_do_arquivo.txt");

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    char c;
    string token;
    int estado_atual = 1;

    while(!arquivo.eof()) {
        arquivo.get(c);
        //cout << "Caractere lido:" << c << endl;
        switch(estado_atual) {
            case 1:
                if(regex_match(string(1, c), op_arit_sum)) {
                    //cout << "Token estado 3:" << token << endl;
                    estado_atual = 3;
                    token = token + c;
                }else if(regex_match(string(1, c), op_arit_sub)) {
                    //cout << "Token estado 4:" << token << endl;
                    estado_atual = 4;
                    token = token + c;
                } else if(regex_match(string(1, c), integer)) {
                    //cout << "Token estado 5:" << token << endl;
                    estado_atual = 5;
                    token = token + c;
                } else if(regex_match(string(1, c), char_regex)) {
                    //cout << "Token estado 10:" << token << endl;
                    estado_atual = 10;
                    token = token + c;
                } else if(regex_match(string(1, c), symbol_op_init)) {
                    //cout << "Token estado 12:" << token << endl;
                    estado_atual = 12;
                    token = token + c;
                } else if(regex_match(string(1, c), spaces)) {
                    //cout << "Token Spaces: " << token << endl;
                    estado_atual = 1;
                    token = token + c;
                }else{
                    //cout << "Token de Erro: " << token << endl;
                    estado_atual = 2;
                    token = token + c;
                }    
                break;
            case 2:
                // pega o cara armazenado e trata o erro
                //cout << "Token: " << token << endl;

                break;
            case 3:
                if(regex_match(string(1, c), integer)){
                    estado_atual = 5;
                    token = token + c;    
                } else{
                    estado_atual = 2;
                    token = token + c;
                }
                break;
            case 4:
                if(regex_match(string(1, c), integer)){
                    estado_atual = 5;
                    token = token + c;
                } else{
                    estado_atual = 2;
                    token = token + c;
                }
                break;
            case 5:
                if(regex_match(string(1, c), integer)){
                    estado_atual = 5;
                    token = token + c;
                } else if (regex_match(string(1, c), comma)){
                    estado_atual = 7;
                    token = token + c;
                } else{
                    token = token + c;
                    get_integer(token);
                    if(get_integer){
                        estado_atual = 1;
                    } else{
                        estado_atual = 2;
                    }
                }
                break;
            case 7:
                if(regex_match(string(1, c), integer)){
                    estado_atual = 8;
                    token = token + c;
                } else{
                    estado_atual = 2;
                    token = token + c;
                }
                break;
            case 8:
                if(regex_match(string(1, c), integer)){
                    estado_atual = 8;
                    token = token + c;
                } else{
                    token = token + c;
                    get_double(token);
                    if(get_double){
                        estado_atual = 1;
                    } else{
                        estado_atual = 2;
                    }
                }
                break;
            case 10:
                if(regex_match(string(1, c), id)){
                    estado_atual = 10;
                    token = token + c;
                    cout << "Token dentro do 10: " << token << endl;
                } else{
                    token = token + c; // abc
                    get_token(token);// abc$
                    
                    // if(get_token){
                        estado_atual = 1;
                    // } else{
                    //     estado_atual = 2;
                    // }
                }
                break;
            case 12:
                if(regex_match(string(1, c), all_symbols)){
                    estado_atual = 12;
                    token = token + c;
                } else if (regex_match(string(1, c), symbol_op_end)){
                    estado_atual = 13;
                    token = token + c;
                } else{
                    estado_atual = 2;
                    token = token + c;
                }
                break;
            case 13:
                // final do comentario, trate disso pia!
                break;
            case 14:
                // so espaços e quebras de linha, trate isso pia
                break;
        }
    }
        
    return 0;
}

