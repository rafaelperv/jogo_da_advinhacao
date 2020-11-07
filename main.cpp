/*
* Inclusão das bibliotecas
* stdio: Biblioteca padrão em C
* stdlib: Biblioteca com algumas funções usada no codigo ex: system();
* Windows: Biblioteca que contem a função Sleep usada no codigo para simular um load
* time: Biblioteca para manipulação de data e hora usando a função time() que pega a data atual em segundos.
* locale: Biblioteca para a utilização de acentos da lingua portuguesa
*/
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

#ifdef WIN32
  #define pause system("pause")
  #define clean system("cls")
  #include<Windows.h>
  #include<time.h>
#else
  #include <unistd.h>
  #define pause getchar();getchar() 
  #define clean system("clear")
  #include<time.h>
#endif

/*
* Estruturas
* matriz: Estrutura utilizada para criação da matriz aleatoria utilizando a função new_matriz()
* lista: Estrutura para armazenar a lista de valores chutados pelo usuario, utilizando a função set_valores_lista
* qtdAE: Estrutura para armazenar acertos e erros e porcentagem dos mesmos, utilizando a função teste_valores
*/

typedef struct
{
    int matriz[3][3];
}matriz;

typedef struct
{
    int lista[9], n;
}lista;

typedef struct
{
    int acertos, erros;
    float porAcerto, porErros;
}qtdAE;

/*
* Prototipos das funções
*/

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

    // Setando os valores das variaveis da estrutura AEusuario para 0
    AEusuario.acertos = 0;
    AEusuario.erros = 0;
    AEusuario.porAcerto = 0.0;
    AEusuario.porErros = 0.0;

    /*
    * Laço principal da aplicação
    * 1: Inicia jogo
    * 2: Apresentar menu de ajuda
    * 3: Apresentar menu de creditos
    * 0: Sair da aplicação
    */
    do
    {
        clean;
        menu_principal();
        printf("\nDigite uma opção: ");
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                printf("\n\tIniciando jogo...\n\n");
                clean;
                new_matriz(&umaMatriz);
                set_valores_lista(&umaLista);

                clean;
                print_matriz(umaMatriz);
                print_lista(umaLista);
                teste_valores(umaMatriz, umaLista, &AEusuario);
                printf("\nQtd Acertos: %d - Qtd Erros: %d \nPorcentagem de Acertos: %.0f%% - Porcentagem de Erros: %.0f%%\n\n",
                        AEusuario.acertos, AEusuario.erros, AEusuario.porAcerto, AEusuario.porErros);
                pause;
                break;
            case 2:
                clean;
                menu_ajuda();
                puts("");
                pause;
                break;
            case 3:
                clean;
                menu_creditos();
                pause;
                break;
            case 0:
                clean;
                printf("\nObrigado por jogar!");
                puts("\n");
                pause;
                break;
            default:
                printf("\nOpção INVALIDA... Digite uma opção VALIDA\n");
                puts("");
                pause;
        }

    }while(op != 0);


    return 0;
}

/*
* Função criada como menu principal da aplicação
*/

void menu_principal()
{
    printf("#########################################################################");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#\tOla, bem vindo!\t\t\t\t\t\t\t#");
    printf("\n#\tEscolha uma opção\t\t\t\t\t\t#");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#\t1 - Iniciar Jogo\t\t\t\t\t\t#");
    printf("\n#\t2 - Ajuda\t\t\t\t\t\t\t#");
    printf("\n#\t3 - Creditos\t\t\t\t\t\t\t#");
    printf("\n#\t0 - Sair\t\t\t\t\t\t\t#");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#########################################################################");
}

/*
* Função criada como menu de ajuda para o usuario
*/

void menu_ajuda()
{
    printf("#########################################################################");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#\tBem vindo!\t\t\t\t\t\t\t#");
    printf("\n#\tComo jogar:\t\t\t\t\t\t\t#");
    printf("\n#\tInsira numeros de 1 a 9\t\t\t\t\t\t#");
    printf("\n#\tEm seguida o programa vai te dizer quantos numeros você acertou#");
    printf("\n#\tBoa Sorte!\t\t\t\t\t\t\t#");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#########################################################################");
}

/*
* Função criada como menu de apresentação dos creditos
*/

void menu_creditos()
{
    printf("#########################################################################");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#\tCriado por: Rafael Vicente\t\t\t\t\t#");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#\t\t\t\t\t\t\t\t\t#");
    printf("\n#########################################################################");
}

/*
* Função utilizada para verificação dos valores contidos no vetor.
* Caso igual a um valor contido no vetor a função retorna o valor True para a função chamadora.
*/
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

/*
* Função para a criação da matriz utilizando valores da data do SO convertida em segundos.
* A função faz o armazenamento a principio em um vetor auxiliar para logo depois das verificações armazenar na matriz final.
*/

void new_matriz(matriz *umaMatriz)
{
    int i, aux_matriz[9], aux = 0, cont = 0;
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

/*
* Função utilizada para imprimir a matriz.
* A função utiliza de dois laços for para a impressão da matriz.
*/
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

/*
* Função utilizada para armazenar os valores inseridos pelo usuario.
* A função utiliza a estrutura lista para ser armazenado os valores inseridos atravez de um laço for.
*/

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

/*
* Função utilizada para imprimir a lista de chutes do usuario.
* A função utiliza de um laço for para a impressão da lista de chutes.
*/

void print_lista(lista umaLista)
{
    int i;
    printf("\nValores inseridos: \n");
    for(i = 0; i < umaLista.n; i++)
    {
        printf("\t%d ", umaLista.lista[i]);
    }
}

/*
* Função para comparação dos valores digitados pelo usuario com os valores contidos na matriz criada aleatoriamente.
* A função utiliza a principio de dois laços for para percorrer sobre a matriz e utiliza uma variavel auxiliar chamada cont para percorrer a lista do usuario.
* Essas comparações são armazenadas nas variaveis da estrutura qtdAE AEusuario.
* Acrescentando +1 a cada vez que encontra um acerto ou um erro.
* A função finaliza convertendo os valores de acertos e erros para float para os calculos finais, e assim calculando a porcentagem de acertos e de erros.
*/

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
