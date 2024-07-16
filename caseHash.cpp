#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <unordered_map>

using namespace std;
unordered_map<string, string> lex;

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
    if(regex_match(token, reserved_loops)) {
        lex["reserved_loops"] = token;
        return true;
    } else if (regex_match(token, reserved_condition)) {
        lex["reserved_condition"] = token;
        return true;
    } else if (regex_match(token, reserved_arit)) {
        lex["reserved_arit"] = token;
        return true;
    } else if (regex_match(token, reserved_main)) {
        lex["reserved_main"] = token;
        return true;
    } else if (regex_match(token, reserved_comment)) {
        lex["reserved_comment"] = token;
        return true;
    } else if (regex_match(token, reserved_types)) {
        lex["reserved_types"] = token;
        return true;
    } else if (regex_match(token, id)) {
        return true;
    }
    return false;   
}

bool get_integer(string token){

  if(regex_match(token, integer_signal)) {
    lex["integer_signal"] = token;
    return true;
  } else if (regex_match(token, integer)) {
    lex["integer"] = token;
    return true;
  }
  return false;
}

bool get_double(string token){
    if(regex_match(token, double_regex)) {
        lex["double"] = token;
        return true;
    }
    return false;
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
                // if()

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
                    if(get_integer(token)){
                        estado_atual = 1;
                        token.clear();
                    } else {
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
                    if(get_double(token)){
                        estado_atual = 1;
                        token.clear();
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
                    token = token; // abc                    
                    get_token(token);
                    estado_atual = 1;
                    token.clear();                    
                }
                // break;
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
    cout << "sou o roedor" << endl;
    // for(int i = 0; i < lex.size(); i++){
        
    // }
    if (!lex.empty()) {
        for (const auto& pair : lex) {
            cout << "frio ne" << endl;
            cout << pair.first << ": " << pair.second << endl;
        }
    } else {
        cout << "O mapa lex está vazio." << endl;
    }
    return 0;
}

