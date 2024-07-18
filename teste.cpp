#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    std::ifstream file("exemplo.txt");
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo." << std::endl;
        return 1;
    }

    std::regex brace_regex("\\{");
    char ch;
    int position = 0;
    std::string character;

    while (file.get(ch)) {
        position++;
        character = ch;
        if (std::regex_match(character, brace_regex)) {
            std::cout << "Encontrado '{' na posição " << position << std::endl;
        }
    }

    file.close();
    return 0;
}
