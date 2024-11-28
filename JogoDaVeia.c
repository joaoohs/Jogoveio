#include "Bib.h"

char Tab[3][3];
char Escolha();
char Dif();

void resetTab();
void printTab();
void playaMove();
void CPUMove();
void PrintGanhador(char);

int checkEspVaz();

char checkGanhador();


int main()
{
char PLAYA = Escolha();
    printf("Você escolheu %c\n", PLAYA);

char ganhador = ' ';

resetTab();

return 0;
}

char Escolha()
{
char escolha;
do
{
    printf("Escolha seu simbolo (X ou O): ");
    scanf("%c", &escolha)
    
    escolha = toupper(escolha);

    if (escolha != 'X' && escolha != 'O')
    {
        printf("Escolha invalida! Tente Novamente.\n");
    }
} while (escolha != 'X' && escolha != 'O');

return escolha;
}

char Dif();
void resetTab()
{

}
void printTab()
{

}
void playaMove()
{

}
void CPUMove()
{

}
void PrintGanhador(char Ganhador)
{

}

int checkEspVaz()
{

}

char checkGanhador()
{

}
