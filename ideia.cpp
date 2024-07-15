enum Estado {
    INICIAL,
    RECONHECENDO_INT,
    RECONHECENDO_DOUBLE,
    RECONHECENDO_ID,
    RECONHECENDO_OP_ARIT,
    RECONHECENDO_OP_LOG,
    RECONHECENDO_OP_REL,
    RECONHECENDO_SYMBOL,
    RECONHECENDO_COMENTARIO,
    RECONHECENDO_ESPACO,
    ERRO
};

Estado estado_atual = INICIAL;
string token_atual;

while (arquivo.hasNext()) {
    char c = arquivo.getNextChar();

    switch (estado_atual) {
        case INICIAL:
            if (isdigit(c)) {
                estado_atual = RECONHECENDO_INT;
                token_atual += c;
            } else if (c == '+' || c == '-') {
                estado_atual = RECONHECENDO_OP_ARIT;
                token_atual += c;
            } else if (isalpha(c) || c == '_') {
                estado_atual = RECONHECENDO_ID;
                token_atual += c;
            } else if (c == '{' || c == '}') {
                estado_atual = RECONHECENDO_SYMBOL;
                token_atual += c;
            } else if (c == '(' || c == ')') {
                estado_atual = RECONHECENDO_SYMBOL;
                token_atual += c;
            } else if (c == '/' && arquivo.peekNextChar() == '*') {
                estado_atual = RECONHECENDO_COMENTARIO;
                token_atual += c;
                arquivo.getNextChar(); // Consumir o próximo caractere '*'
            } else if (isspace(c)) {
                estado_atual = RECONHECENDO_ESPACO;
            } else {
                estado_atual = ERRO;
            }
            break;

        case RECONHECENDO_INT:
            if (isdigit(c)) {
                token_atual += c;
            } else {
                // Token inteiro reconhecido
                processarToken(token_atual, "INT");
                token_atual = "";
                estado_atual = INICIAL;
                arquivo.devolverCaractere(c); // Devolver caractere não consumido
            }
            break;

        case RECONHECENDO_OP_ARIT:
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                token_atual += c;
            } else {
                // Token de operador aritmético reconhecido
                processarToken(token_atual, "OP_ARIT");
                token_atual = "";
                estado_atual = INICIAL;
                arquivo.devolverCaractere(c); // Devolver caractere não consumido
            }
            break;

        case RECONHECENDO_ID:
            if (isalnum(c) || c == '_') {
                token_atual += c;
            } else {
                // Verificar se é uma palavra reservada
                if (éPalavraReservada(token_atual)) {
                    processarToken(token_atual, "PALAVRA_RESERVADA");
                } else {
                    processarToken(token_atual, "ID");
                }
                token_atual = "";
                estado_atual = INICIAL;
                arquivo.devolverCaractere(c); // Devolver caractere não consumido
            }
            break;

        // Outros casos para reconhecimento de tokens de acordo com as especificações
        // Implementar RECONHECENDO_DOUBLE, RECONHECENDO_OP_LOG, RECONHECENDO_OP_REL, etc.

        case RECONHECENDO_COMENTARIO:
            token_atual += c;
            if (c == '}' && token_atual.size() >= 6 && token_atual.substr(token_atual.size() - 6) == "Radio{") {
                // Token de comentário reconhecido
                processarToken(token_atual, "COMENTARIO");
                token_atual = "";
                estado_atual = INICIAL;
            }
            break;

        case RECONHECENDO_ESPACO:
            if (!isspace(c)) {
                estado_atual = INICIAL;
                arquivo.devolverCaractere(c); // Devolver caractere não consumido
            }
            break;

        case ERRO:
            // Tratar erro léxico
            cout << "Erro léxico ao ler o caractere: " << c << endl;
            return 1;
    }
}

// Função para verificar se é uma palavra reservada
bool éPalavraReservada(string token) {
    return (token == "laps" || token == "circuit" || token == "pitEntry" || token == "pitExit" ||
            token == "overtake" || token == "brake" || token == "Radio" || token == "race" ||
            token == "int" || token == "double" || token == "char" || token == "boolean" || token == "str");
}

// Função para processar tokens reconhecidos
void processarToken(string token, string tipo) {
    cout << "Token encontrado: " << token << " do tipo " << tipo << endl;
    // Aqui você pode adicionar lógica para tratamento posterior do token
}
