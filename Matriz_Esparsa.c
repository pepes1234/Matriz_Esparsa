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

int id = 1;

Matriz_Esparsa *Cria_Nodo();
Lista_Matrizes *Cria_Nodo_Matriz();
void cria_matriz(Lista_Matrizes **lista);
void insere_lista(Lista_Matrizes **lista, Lista_Matrizes *nova);
void insere_valor(int linha, int coluna, float valor, Matriz_Esparsa **matriz);
void imprime_matriz(Lista_Matrizes *lista);
void imprime_diagonal_principal(Lista_Matrizes *lista);
void exclui_matriz(Lista_Matrizes **lista);
void exclui_lista(Lista_Matrizes **lista);

Matriz_Esparsa *Soma_Matrizes(Lista_Matrizes **lista, int id_m1, int id_m2);
Matriz_Esparsa *Subtrai_Matrizes(Lista_Matrizes **lista, int id_m1, int id_m2);
Matriz_Esparsa *Multiplica_Matrizes(Lista_Matrizes **lista, int id_m1, int id_m2);
Matriz_Esparsa *Matriz_Transposta(Lista_Matrizes **lista, int id);

Lista_Matrizes *pesquisa_matriz(Lista_Matrizes *lista, int id);
Matriz_Esparsa *pesquisa_posicao(Matriz_Esparsa *matriz, int linha, int coluna);
void pausa();

int main()
{
    Lista_Matrizes *lista = NULL;
    int opc;
    do {
        printf("\n=== Menu ===\n");
        printf("1-Adicionar uma matriz\n");
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
                cria_matriz(&lista);
                pausa();
                break;
            case 2:
                if (lista == NULL) {
                    printf("\nNenhuma matriz cadastrada!\n");
                    pausa();
                } else {
                    imprime_matriz(lista);
                    pausa();
                }
                break;
            case 3:
                if (lista == NULL) {
                    printf("\nNenhuma matriz cadastrada!\n");
                    pausa();
                } else {
                    imprime_diagonal_principal(lista);
                    pausa();
                }
                break;
            case 4:
                if (lista == NULL) {
                    printf("\nNenhuma matriz cadastrada!\n");
                    pausa();
                } else {
                    exclui_matriz(&lista);
                    pausa();
                }
                break;
        }
    } while (opc != 9);
    exclui_lista(&lista);
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

Lista_Matrizes *Cria_Nodo_Matriz() {
    Lista_Matrizes *p = (Lista_Matrizes*) malloc(sizeof(Lista_Matrizes));
    if (!p){
        printf("Problema de alocacao\n"); 
        exit(0); 
    }
    return p;
}

void cria_matriz(Lista_Matrizes **lista) {
    Lista_Matrizes *nova = Cria_Nodo_Matriz();
    nova->id = id++;
    printf("Digite o numero de linhas da matriz: ");
    scanf("%d", &nova->t_linhas);
    printf("Digite o numero de colunas da matriz: ");
    scanf("%d", &nova->t_colunas);
    nova->inicio = NULL;
    nova->prox = NULL;
    insere_lista(lista, nova);
    int linha, coluna;
    float valor;
    do {
        printf("Digite a linha(1-%d) do elemento(0 para finalizar): ", nova->t_linhas);
        scanf("%d", &linha);
        if (linha > 0 && linha <= nova->t_linhas) {
            printf("Digite a coluna(1-%d) do elemento: ", nova->t_colunas);
            scanf("%d", &coluna);
            if (coluna > 0 && coluna <= nova->t_colunas) {
                printf("Digite o valor do elemento: ");
                scanf("%f", &valor);
                insere_valor(linha, coluna, valor, &nova->inicio);
            } else {
                printf("Coluna invalida!\n");
            }
        } else {
            if (linha != 0) {
                printf("Linha invalida!\n");
            }
        }
    } while (linha != 0);
    printf("\nMatriz %dx%d criada com id: %d\n", nova->t_linhas, nova->t_colunas, nova->id);
}

void insere_lista(Lista_Matrizes **lista, Lista_Matrizes *nova) {
    if (*lista == NULL) {
        *lista = nova;
    } else {
        Lista_Matrizes *aux = *lista;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = nova;
    }
}

void insere_valor(int linha, int coluna, float valor, Matriz_Esparsa **matriz) {
    Matriz_Esparsa *novo = Cria_Nodo();
    novo->lin = linha;
    novo->col = coluna;
    novo->dado = valor;
    novo->prox = NULL;
    if (*matriz == NULL) {
        *matriz = novo;
    } else {
        Matriz_Esparsa *aux = *matriz;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void imprime_matriz(Lista_Matrizes *lista) {
    int id;
    printf("Digite o id da matriz a ser impressa: ");
    scanf("%d", &id);
    Lista_Matrizes *matriz = pesquisa_matriz(lista, id);
    if (matriz == NULL) {
        printf("\nMatriz com id %d nao encontrada!\n", id);
        return;
    }
    printf("Matriz %dx%d (id: %d):\n", matriz->t_linhas, matriz->t_colunas, matriz->id);
    for (int i = 1; i <= matriz->t_linhas; i++) {
        for (int j = 1; j <= matriz->t_colunas; j++) {
            Matriz_Esparsa *elemento = pesquisa_posicao(matriz->inicio, i, j);
            if (elemento != NULL) {
                printf("%.2f\t", elemento->dado);
            } else {
                printf("0.00\t");
            }
        }
        printf("\n");
    }
}

void imprime_diagonal_principal(Lista_Matrizes *lista) {
    int id;
    printf("Digite o id da matriz para imprimir a diagonal principal: ");
    scanf("%d", &id);
    Lista_Matrizes *matriz = pesquisa_matriz(lista, id);
    if (matriz == NULL) {
        printf("\nMatriz com id %d nao encontrada!\n", id);
        return;
    } else if (matriz->t_linhas != matriz->t_colunas) {
        printf("\nMatriz com id %d nao e quadrada, nao possui diagonal principal!\n", id);
        return;
    }
    printf("Diagonal principal da matriz %dx%d (id: %d):\n", matriz->t_linhas, matriz->t_colunas, matriz->id);
    for (int i = 1; i <= matriz->t_linhas && i <= matriz->t_colunas; i++) {
        Matriz_Esparsa *elemento = pesquisa_posicao(matriz->inicio, i, i);
        if (elemento != NULL) {
            printf("%.2f\t", elemento->dado);
        } else {
            printf("0.00\t");
        }
    }
    printf("\n");
}

void exclui_matriz(Lista_Matrizes **lista) {
    int id;
    printf("Digite o id da matriz a ser excluida: ");
    scanf("%d", &id);
    Lista_Matrizes *aux = *lista, *ant = NULL;
    while (aux != NULL && aux->id != id) {
        ant = aux;
        aux = aux->prox;
    }
    if (aux == NULL) {
        printf("\nMatriz com id %d nao encontrada!\n", id);
        return;
    }
    if (ant == NULL) {
        *lista = aux->prox;
    } else {
        ant->prox = aux->prox;
    }
    Matriz_Esparsa *elemento = aux->inicio, *temp;
    while (elemento != NULL) {
        temp = elemento;
        elemento = elemento->prox;
        free(temp);
    }
    free(aux);
    printf("\nMatriz com id %d excluida com sucesso!\n", id);
}

void exclui_lista(Lista_Matrizes **lista) {
    Lista_Matrizes *aux = *lista, *temp;
    while (aux != NULL) {
        temp = aux;
        aux = aux->prox;
        Matriz_Esparsa *elemento = temp->inicio, *temp_elemento;
        while (elemento != NULL) {
            temp_elemento = elemento;
            elemento = elemento->prox;
            free(temp_elemento);
        }
        free(temp);
    }
    *lista = NULL;
}

Lista_Matrizes *pesquisa_matriz(Lista_Matrizes *lista, int id) {
    Lista_Matrizes *aux = lista;
    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

Matriz_Esparsa *pesquisa_posicao(Matriz_Esparsa *matriz, int linha, int coluna) {
    Matriz_Esparsa *aux = matriz;
    while (aux != NULL) {
        if (aux->lin == linha && aux->col == coluna) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void pausa() {
    printf("\nPressione 1 para continuar...");
    scanf("%d");
}
