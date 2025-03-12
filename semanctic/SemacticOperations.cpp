#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;


class Operations {
    public:
    bool validateLine(map<string, string> orderedEntry) {
        if()
    }

    unordered_map<string, string> getTabelaDeSimbolos() {
        return tabelaDeSimbolos;
    }

    void addIntoTabelaDeSimbolos(string key, string value) {
        tabelaDeSimbolos[key] = value;
    }

    tuple<string, string> verifyKeyTypeInTabelaDeSimbolos(string key) {
        auto tableKey = tabelaDeSimbolos.find(key);
        if (tableKey != tabelaDeSimbolos.end()) {
            tuple<string, string> data = make_tuple(tableKey->first, tableKey->second);
            return data;
        }
    }
    
};