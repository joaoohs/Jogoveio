void CPUMove(char Dificuldade) {
    if (Dificuldade != 'M') return; // Executa apenas se a dificuldade for média

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // 1. Bloqueia vitória iminente do jogador
    if (criticalMove('X')) return;

    // 2. Tenta criar uma oportunidade de vitória para o computador
    if (criticalMove('O')) return;

    // 3. Prioriza jogar no centro, caso esteja disponível
    if (Tab[1][1] == ' ') {
        Tab[1][1] = 'O';
        return;
    }

    // 4. Tenta jogar em um dos cantos disponíveis
    if (playCorner()) return;

    // 5. Faz uma jogada aleatória nas bordas ou posições disponíveis
    playRandom();
}

// Função para verificar e realizar movimentos críticos
int criticalMove(char symbol) {
    // Verifica se há uma linha, coluna ou diagonal onde o computador ou jogador pode ganhar
    if (checkCritical(symbol, 0, 0, 0, 1, 0, 2)) return 1; // Linha 0
    if (checkCritical(symbol, 1, 0, 1, 1, 1, 2)) return 1; // Linha 1
    if (checkCritical(symbol, 2, 0, 2, 1, 2, 2)) return 1; // Linha 2
    if (checkCritical(symbol, 0, 0, 1, 0, 2, 0)) return 1; // Coluna 0
    if (checkCritical(symbol, 0, 1, 1, 1, 2, 1)) return 1; // Coluna 1
    if (checkCritical(symbol, 0, 2, 1, 2, 2, 2)) return 1; // Coluna 2
    if (checkCritical(symbol, 0, 0, 1, 1, 2, 2)) return 1; // Diagonal 0-2
    if (checkCritical(symbol, 0, 2, 1, 1, 2, 0)) return 1; // Diagonal 2-0

    return 0; // Nenhuma jogada crítica encontrada
}

// Função auxiliar para verificar a possibilidade de um movimento crítico em uma linha/coluna/diagonal
int checkCritical(char symbol, int x1, int y1, int x2, int y2, int x3, int y3) {
    if (Tab[x1][y1] == symbol && Tab[x2][y2] == symbol && Tab[x3][y3] == ' ') {
        Tab[x3][y3] = 'O';
        return 1;
    }
    if (Tab[x1][y1] == symbol && Tab[x3][y3] == symbol && Tab[x2][y2] == ' ') {
        Tab[x2][y2] = 'O';
        return 1;
    }
    if (Tab[x2][y2] == symbol && Tab[x3][y3] == symbol && Tab[x1][y1] == ' ') {
        Tab[x1][y1] = 'O';
        return 1;
    }
    return 0;
}

// Função para tentar jogar nos cantos
int playCorner() {
    int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++) {
        int x = corners[i][0];
        int y = corners[i][1];
        if (Tab[x][y] == ' ') {
            Tab[x][y] = 'O';
            return 1;
        }
    }
    return 0;
}

// Função para jogar em uma posição aleatória
void playRandom() {
    int availableSpaces[9][2];
    int count = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Tab[i][j] == ' ') {
                availableSpaces[count][0] = i;
                availableSpaces[count][1] = j;
                count++;
            }
        }
    }

    if (count > 0) {
        int choice = rand() % count;
        int x = availableSpaces[choice][0];
        int y = availableSpaces[choice][1];
        Tab[x][y] = 'O';
    }
}
