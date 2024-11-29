#include "Bib.h"

// Estrutura para representar um movimento para a CPU
struct Move {
    int row, col;
};

char Tab[3][3];
char PLAYA, opponent;
char dificuldade;

void resetTab();
void printTab();
void playaMove();
void CPUMove();
void PrintGanhador(char);
void playRandom();

int checkEspVaz();
int criticalMove(char);
int checkCritical(char symbol, int x1, int y1, int x2, int y2, int x3, int y3);
int playCorner();
int avaliar(char Tab[3][3]);
int minimax(char Tab[3][3], int profundidade, int ehMax);
int haMovimentosRestantes(char Tab[3][3]);

char checkGanhador();

struct Move encontrarMelhorJogada(char Tab[3][3]);

char Escolha();
char Dif();

int main() {
    PLAYA = Escolha();
    opponent = (PLAYA == 'X') ? 'O' : 'X';  // Define o símbolo do oponente
    printf("Voce escolheu %c\n", PLAYA);

    dificuldade = Dif();  // Define a dificuldade como global
    printf("Dificuldade escolhida: %c\n", dificuldade);

    char ganhador = ' ';
    resetTab();

    while (ganhador == ' ' && checkEspVaz() > 0) {
        printTab();
        playaMove();
        ganhador = checkGanhador();
        if (ganhador != ' ' || checkEspVaz() == 0) break;

        CPUMove();
        ganhador = checkGanhador();
    }

    PrintGanhador(ganhador);
    return 0;
}

char Escolha() {
    char escolha;
    do {
        printf("Escolha seu simbolo (X ou O): ");
        scanf(" %c", &escolha);
        escolha = toupper(escolha);

        if (escolha != 'X' && escolha != 'O') {
            printf("Escolha invalida! Tente novamente.\n");
        }
    } while (escolha != 'X' && escolha != 'O');

    return escolha;
}

char Dif() {
    char diff;
    do {
        printf("Escolha sua dificuldade\nFacil (F)\nMedio (M)\nDificil (D): ");
        scanf(" %c", &diff);
        diff = toupper(diff);

        if (diff != 'F' && diff != 'M' && diff != 'D') {
            printf("Escolha invalida! Tente novamente.\n");
        }
    } while (diff != 'F' && diff != 'M' && diff != 'D');

    return diff;
}

void resetTab() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Tab[i][j] = ' ';
        }
    }
}

void printTab() {
    printf(" %c | %c | %c \n", Tab[0][0], Tab[0][1], Tab[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", Tab[1][0], Tab[1][1], Tab[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", Tab[2][0], Tab[2][1], Tab[2][2]);
}

void playaMove() {
    int x, y;
    do {
        printf("Escolha uma linha (1-3): ");
        scanf("%d", &x);
        x--;  // Ajuste para índice zero

        printf("Escolha uma coluna (1-3): ");
        scanf("%d", &y);
        y--;  // Ajuste para índice zero

        if (x < 0 || x > 2 || y < 0 || y > 2 || Tab[x][y] != ' ') {
            printf("Movimento invalido! Tente novamente.\n");
        } else {
            Tab[x][y] = PLAYA;
            break;
        }
    } while (1);
}

void CPUMove() {
    if (dificuldade == 'F') {
        playRandom();
    } else if (dificuldade == 'M') {
        if (criticalMove(PLAYA)) return;  // Bloqueia vitória iminente
        if (criticalMove(opponent)) return;  // Tenta ganhar
        if (playCorner()) return;  // Joga nos cantos
        playRandom();  // Joga aleatoriamente
    } else if (dificuldade == 'D') {
        struct Move melhorMovimento = encontrarMelhorJogada(Tab);
        Tab[melhorMovimento.row][melhorMovimento.col] = opponent;
    }
}

void PrintGanhador(char ganhador) {
    // Exibe o tabuleiro final antes de anunciar o resultado
    printf("\nTabuleiro final:\n");
    printTab();

    // Mostra a mensagem de acordo com o resultado
    if (ganhador == PLAYA) {
        printf("Voce ganhou! Parabens!\n");
    } else if (ganhador == opponent) {
        printf("VOCE PERDEU PARA UMA MAQUINA KKKKKKKKKK\n");
    } else {
        printf("Empate!\n");
    }
}

int checkEspVaz() {
    int espacos = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Tab[i][j] == ' ') espacos++;
        }
    }
    return espacos;
}

char checkGanhador() {
    for (int i = 0; i < 3; i++) {
        if (Tab[i][0] == Tab[i][1] && Tab[i][0] == Tab[i][2] && Tab[i][0] != ' ') {
            return Tab[i][0];
        }
        if (Tab[0][i] == Tab[1][i] && Tab[0][i] == Tab[2][i] && Tab[0][i] != ' ') {
            return Tab[0][i];
        }
    }
    if (Tab[0][0] == Tab[1][1] && Tab[0][0] == Tab[2][2] && Tab[0][0] != ' ') {
        return Tab[0][0];
    }
    if (Tab[0][2] == Tab[1][1] && Tab[0][2] == Tab[2][0] && Tab[0][2] != ' ') {
        return Tab[0][2];
    }
    return ' ';
}
int criticalMove(char symbol) {
    // Verifica se há uma linha, coluna ou diagonal onde o jogador ou CPU pode ganhar
    if (checkCritical(symbol, 0, 0, 0, 1, 0, 2)) return 1; // Linha 0
    if (checkCritical(symbol, 1, 0, 1, 1, 1, 2)) return 1; // Linha 1
    if (checkCritical(symbol, 2, 0, 2, 1, 2, 2)) return 1; // Linha 2
    if (checkCritical(symbol, 0, 0, 1, 0, 2, 0)) return 1; // Coluna 0
    if (checkCritical(symbol, 0, 1, 1, 1, 2, 1)) return 1; // Coluna 1
    if (checkCritical(symbol, 0, 2, 1, 2, 2, 2)) return 1; // Coluna 2
    if (checkCritical(symbol, 0, 0, 1, 1, 2, 2)) return 1; // Diagonal principal
    if (checkCritical(symbol, 0, 2, 1, 1, 2, 0)) return 1; // Diagonal secundária
    return 0; // Nenhuma jogada crítica encontrada
}

int checkCritical(char symbol, int x1, int y1, int x2, int y2, int x3, int y3) {
    // Verifica combinações de dois símbolos iguais com espaço vazio
    if (Tab[x1][y1] == symbol && Tab[x2][y2] == symbol && Tab[x3][y3] == ' ') {
        Tab[x3][y3] = opponent; // CPU faz a jogada
        return 1;
    }
    if (Tab[x1][y1] == symbol && Tab[x3][y3] == symbol && Tab[x2][y2] == ' ') {
        Tab[x2][y2] = opponent;
        return 1;
    }
    if (Tab[x2][y2] == symbol && Tab[x3][y3] == symbol && Tab[x1][y1] == ' ') {
        Tab[x1][y1] = opponent;
        return 1;
    }
    return 0;
}

int playCorner() {
    // Tenta jogar nos cantos disponíveis
    int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++) {
        int x = corners[i][0];
        int y = corners[i][1];
        if (Tab[x][y] == ' ') {
            Tab[x][y] = opponent;
            return 1;
        }
    }
    return 0; // Nenhum canto disponível
}

void playRandom() {
    // Joga em uma posição aleatória disponível
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
        Tab[x][y] = opponent;
    }
}

int avaliar(char Tab[3][3]) {
    // Avalia o estado atual do tabuleiro para o algoritmo Minimax
    for (int linha = 0; linha < 3; linha++) {
        if (Tab[linha][0] == Tab[linha][1] && Tab[linha][1] == Tab[linha][2]) {
            if (Tab[linha][0] == opponent) return +10;
            if (Tab[linha][0] == PLAYA) return -10;
        }
    }
    for (int coluna = 0; coluna < 3; coluna++) {
        if (Tab[0][coluna] == Tab[1][coluna] && Tab[1][coluna] == Tab[2][coluna]) {
            if (Tab[0][coluna] == opponent) return +10;
            if (Tab[0][coluna] == PLAYA) return -10;
        }
    }
    if (Tab[0][0] == Tab[1][1] && Tab[1][1] == Tab[2][2]) {
        if (Tab[0][0] == opponent) return +10;
        if (Tab[0][0] == PLAYA) return -10;
    }
    if (Tab[0][2] == Tab[1][1] && Tab[1][1] == Tab[2][0]) {
        if (Tab[0][2] == opponent) return +10;
        if (Tab[0][2] == PLAYA) return -10;
    }
    return 0; // Nenhum vencedor no momento
}

int minimax(char Tab[3][3], int profundidade, int ehMax) {
    int pontuacao = avaliar(Tab);

    // Retorna pontuação se o jogo terminar
    if (pontuacao == 10 || pontuacao == -10) return pontuacao;
    if (checkEspVaz() == 0) return 0; // Empate

    if (ehMax) {
        int melhor = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (Tab[i][j] == ' ') {
                    Tab[i][j] = opponent;
                    melhor = (melhor > minimax(Tab, profundidade + 1, 0)) ? melhor : minimax(Tab, profundidade + 1, 0);
                    Tab[i][j] = ' ';
                }
            }
        }
        return melhor;
    } else {
        int melhor = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (Tab[i][j] == ' ') {
                    Tab[i][j] = PLAYA;
                    melhor = (melhor < minimax(Tab, profundidade + 1, 1)) ? melhor : minimax(Tab, profundidade + 1, 1);
                    Tab[i][j] = ' ';
                }
            }
        }
        return melhor;
    }
}

struct Move encontrarMelhorJogada(char Tab[3][3]) {
    struct Move melhorMovimento = {-1, -1};
    int melhorValor = -1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Tab[i][j] == ' ') {
                Tab[i][j] = opponent;
                int valorMovimento = minimax(Tab, 0, 0);
                Tab[i][j] = ' ';
                if (valorMovimento > melhorValor) {
                    melhorMovimento.row = i;
                    melhorMovimento.col = j;
                    melhorValor = valorMovimento;
                }
            }
        }
    }
    return melhorMovimento;
}