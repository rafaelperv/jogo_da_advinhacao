// Inclusão das bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<Windows.h>
#include<time.h>
#include<locale.h>

// Constantes
#define MAX 10

// Estrutura da matriz
typedef struct
{
    int matriz[3][3];
}matriz;

// Estrutura da lista
typedef struct
{
    int lista[9], n;
}lista;

typedef struct
{
    int acertos, erros;
    float porAcerto, porErros;
}qtdAE;

// Prototipação funções
void menu_principal();
void menu_ajuda();
void menu_creditos();
bool pesquisaNum(int valores[], int tamanho, int valor);
void new_matriz(matriz *umaMatriz);
void print_matriz(matriz umaMatriz);
void set_valores_lista(lista *umaLista);
void print_lista(lista umaLista);
void teste_valores(matriz umaMatriz, lista umaLista, qtdAE *AEusuario);

int main() {
    system("Title Jogo da advinhação");
    setlocale(LC_ALL, "Portuguese");
    matriz umaMatriz;
    lista umaLista;
    qtdAE AEusuario;
    int op = 0;

    // Setando os valores das variaveis dentro da estrutura da variavel AEusuario para 0
    AEusuario.acertos = 0;
    AEusuario.erros = 0;
    AEusuario.porAcerto = 0.0;
    AEusuario.porErros = 0.0;

    do
    {
        system("cls");
        menu_principal();
        printf("\nDigite uma opção: ");
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                printf("\n\tIniciando jogo...\n\n");
                Sleep(5000);
                system("cls");
                new_matriz(&umaMatriz);
                set_valores_lista(&umaLista);

                system("cls");
                print_matriz(umaMatriz);
                print_lista(umaLista);
                teste_valores(umaMatriz, umaLista, &AEusuario);
                printf("\nQtd Acertos: %d - Qtd Erros: %d \nPorcentagem de Acertos: %.0f%% - Porcentagem de Erros: %.0f%%\n\n",
                        AEusuario.acertos, AEusuario.erros, AEusuario.porAcerto, AEusuario.porErros);
                system("pause");
                break;
            case 2:
                system("cls");
                menu_ajuda();
                puts("");
                system("pause");
                break;
            case 3:
                system("cls");
                menu_creditos();
                puts("");
                system("pause");
                break;
            case 0:
                system("cls");
                printf("\nObrigado por jogar!");
                puts("\n");
                system("pause");
                break;
            default:
                printf("\nOpção INVALIDA... Digite uma opção VALIDA\n");
                puts("");
                system("pause");
        }

    }while(op != 0);


    return 0;
}

void menu_principal()
{
    printf("################################################################################");
    printf("#                                                                              #");
    printf("#\tOla, bem vindo!                                                        #");
    printf("#\tEscolha uma opção                                                      #");
    printf("#                                                                              #");
    printf("#                                                                              #");
    printf("#\t1 - Iniciar Jogo                                                       #");
    printf("#\t2 - Ajuda                                                              #");
    printf("#\t3 - Creditos                                                           #");
    printf("#\t0 - Sair                                                               #");
    printf("#                                                                              #");
    printf("################################################################################");
}

void menu_ajuda()
{
    printf("################################################################################");
    printf("#                                                                              #");
    printf("#\tBem vindo!                                                             #");
    printf("#\tComo jogar:                                                            #");
    printf("#\tInsira numeros de 1 a 9                                                #");
    printf("#\tEm seguida o programa vai te dizer quantos numeros você acertou        #");
    printf("#\tBoa Sorte!                                                             #");
    printf("#                                                                              #");
    printf("################################################################################");
}

void menu_creditos()
{
    printf("################################################################################");
    printf("#                                                                              #");
    printf("#                                                                              #");
    printf("#                                                                              #");
    printf("#\tCriado por: Rafael Vicente                                             #");
    printf("#                                                                              #");
    printf("#                                                                              #");
    printf("#                                                                              #");
    printf("################################################################################");
}

bool pesquisaNum(int valores[], int tamanho, int valor)
{
    int i;

    for(i = 0; i < tamanho; i++)
    {
        if(valores[i] == valor)
        {
            return true;
        }
    }
    return false;
}

void new_matriz(matriz *umaMatriz)
{
    int i, j, aux_matriz[9], aux = 0, cont = 0;
    srand(time(NULL));
    for(i = 0; i < 9; i++)
    {
        aux = (rand() % 9 + 1);
        while(pesquisaNum(aux_matriz, i,aux))
        {
            aux = (rand() % 9 + 1);
        }
        aux_matriz[i] = aux;
    }

    for(int x = 0; x < 3; x++)
    {
        for(int y = 0; y < 3; y++)
        {
            umaMatriz->matriz[x][y] = aux_matriz[cont];
            cont++;
        }
    }
}

void print_matriz(matriz umaMatriz)
{
    int i, j;

    puts("\n");

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            printf("\t[%d] ", umaMatriz.matriz[i][j]);
        }
        puts("");
    }
}

void set_valores_lista(lista *umaLista)
{
    int i;
    umaLista->n = 0;
    printf("\nDigite os valores a ser chutados!\n");

    for(i = umaLista->n; i < 9; i++)
    {
        printf("\n\tDigite um numero: ");
        scanf("%d", &umaLista->lista[umaLista->n]);
        (umaLista->n)++;
    }
}

void print_lista(lista umaLista)
{
    int i;
    printf("\nValores inseridos: \n");
    for(i = 0; i < umaLista.n; i++)
    {
        printf("\t%d ", umaLista.lista[i]);
    }
}

void teste_valores(matriz umaMatriz, lista umaLista, qtdAE *AEusuario)
{
    int i, j, cont = 0;

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(umaLista.lista[cont] == umaMatriz.matriz[i][j])
            {
                (AEusuario->acertos)++;
            }
            else
            {
                (AEusuario->erros)++;
            }
            cont++;
        }
    }

    float convAcertosFloat = AEusuario->acertos;
    float convErrosFloat = AEusuario->erros;

    AEusuario->porAcerto = (convAcertosFloat/9) * 100;
    AEusuario->porErros = (convErrosFloat/9) * 100;

}
