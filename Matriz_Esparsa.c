#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    float dado;
    int lin, col;
    struct nodo *prox;
}Matriz_Esparsa;

typedef struct matriz
{
    int id;
    int t_linhas, t_colunas;
    Matriz_Esparsa *inicio;
    struct matriz *prox;
} Lista_Matrizes;

int id = 0;

Matriz_Esparsa *Cria_Nodo();
void insere_fim(int linha, int coluna, float valor, Matriz_Esparsa **matriz);
void inserir_lista(Lista_Matrizes **lista, Lista_Matrizes *nova);
void cria_matriz(int linhas, int colunas, Lista_Matrizes **lista);
void imprimir_matriz(Lista_Matrizes *lista, int id);
void imprimir_diagonal_principal(Lista_Matrizes *lista, int id);
void excluir_matriz(Lista_Matrizes **lista);
void excluir_lista(Lista_Matrizes **lista);

Matriz_Esparsa *Soma_Matrizes(Lista_Matrizes **lista, int id_m1, int id_m2);
Matriz_Esparsa *Subtrai_Matrizes(Lista_Matrizes **lista, int id_m1, int id_m2);
Matriz_Esparsa *Multiplica_Matrizes(Lista_Matrizes **lista, int id_m1, int id_m2);
Matriz_Esparsa *Matriz_Transposta(Lista_Matrizes **lista, int id);

Lista_Matrizes *pesquisa_matriz(Lista_Matrizes *lista, int id);
Matriz_Esparsa *pesquisa_posicao(Matriz_Esparsa *matriz, int linha, int coluna);

int main()
{
    Lista_Matrizes *lista = NULL;
    int opc;
    do {
        printf("\n1-Inserir uma matriz\n");
        printf("2-Imprimir uma matriz\n");
        printf("3-Imprimir a diagonal principal de uma matriz\n");
        printf("4-Excluir uma matriz\n");
        printf("5-Somar duas matrizes\n");
        printf("6-Subtrair duas matrizes\n");
        printf("7-Multiplicar duas matrizes\n");
        printf("8-Transpor uma matriz\n");
        printf("9-Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                break;
            case 2:
                int id_m;
                printf("Digite o id da matriz a ser impressa: ");
                scanf("%d", &id_m);
                imprimir_matriz(lista, id_m);
                break;
            
        }
    } while (opc != 9);
    return 0;
}

Matriz_Esparsa *Cria_Nodo() {
    Matriz_Esparsa *p = (Matriz_Esparsa*) malloc(sizeof(Matriz_Esparsa));
    if (!p){
        printf("Problema de alocacao\n"); 
        exit(0); 
    }
    return p;
}
