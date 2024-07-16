#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

regex space("\\s"); // Expressão regular para qualquer espaço em branco

int main(){
    ifstream arquivo("nome_do_arquivo.txt");

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    char c;

    while(arquivo.get(c)) {
        cout << "Caractere lido: '" << c << "'" << endl;

        if(regex_match(string(1, c), space)) {
            cout << "Espaço detectado." << endl;
        } else {
            cout << "Nao e um espaco." << endl;
        }
    }

    return 0;
}
