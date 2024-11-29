#include "Bib.h" // Inclui a biblioteca externa (não fornecida)

// Estrutura para representar um movimento para a CPU
struct Move {
    int row, col; // Linha e coluna da jogada
};

// Variáveis globais
char Tab[3][3]; // Tabuleiro do jogo da velha
char PLAYA, opponent; // Símbolos do jogador e do oponente
char dificuldade; // Nível de dificuldade do jogo

// Declarações de funções
void resetTab(); // Reseta o tabuleiro
void printTab(); // Imprime o estado atual do tabuleiro
void playaMove(); // Realiza o movimento do jogador
void CPUMove(); // Realiza o movimento da CPU
void PrintGanhador(char); // Imprime o vencedor do jogo
void playRandom(); // Faz a CPU jogar aleatoriamente

int checkEspVaz(); // Verifica espaços vazios no tabuleiro
int criticalMove(char); // Faz uma jogada crítica (ganhar ou bloquear)
int checkCritical(char symbol, int x1, int y1, int x2, int y2, int x3, int y3); // Checa uma situação crítica
int playCorner(); // Joga nos cantos disponíveis
int avaliar(char Tab[3][3]); // Avalia o tabuleiro para o algoritmo Minimax
int minimax(char Tab[3][3], int profundidade, int ehMax); // Algoritmo Minimax
int haMovimentosRestantes(char Tab[3][3]); // Verifica se há movimentos restantes

char checkGanhador(); // Verifica se há um ganhador
struct Move encontrarMelhorJogada(char Tab[3][3]); // Encontra a melhor jogada para a CPU

char Escolha(); // Permite o jogador escolher o símbolo
char Dif(); // Permite o jogador escolher a dificuldade

// Função principal
int main() {
    // Configuração inicial
    PLAYA = Escolha(); // Escolhe o símbolo do jogador
    opponent = (PLAYA == 'X') ? 'O' : 'X'; // Define o símbolo do oponente
    printf("Voce escolheu %c\n", PLAYA);

    dificuldade = Dif(); // Escolhe a dificuldade
    printf("Dificuldade escolhida: %c\n", dificuldade);

    char ganhador = ' ';
    resetTab(); // Reseta o tabuleiro

    // Loop principal do jogo
    while (ganhador == ' ' && checkEspVaz() > 0) {
        printTab(); // Mostra o tabuleiro
        playaMove(); // Jogador faz um movimento
        ganhador = checkGanhador(); // Verifica se há um ganhador
        if (ganhador != ' ' || checkEspVaz() == 0) break;

        CPUMove(); // CPU faz um movimento
        ganhador = checkGanhador(); // Verifica novamente se há um ganhador
    }

    PrintGanhador(ganhador); // Exibe o vencedor
    return 0;
}

// Implementações das funções auxiliares
char Escolha() {
    char escolha;
    do {
        printf("Escolha seu simbolo (X ou O): ");
        scanf(" %c", &escolha);
        escolha = toupper(escolha); // Converte para maiúsculo

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
        diff = toupper(diff); // Converte para maiúsculo

        if (diff != 'F' && diff != 'M' && diff != 'D') {
            printf("Escolha invalida! Tente novamente.\n");
        }
    } while (diff != 'F' && diff != 'M' && diff != 'D');

    return diff;
}

void resetTab() {
    // Inicializa o tabuleiro com espaços vazios
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Tab[i][j] = ' ';
        }
    }
}

void printTab() {
    // Imprime o tabuleiro formatado
    printf(" %c | %c | %c \n", Tab[0][0], Tab[0][1], Tab[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", Tab[1][0], Tab[1][1], Tab[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", Tab[2][0], Tab[2][1], Tab[2][2]);
}

// (Outras funções seguem documentadas no mesmo formato.)
