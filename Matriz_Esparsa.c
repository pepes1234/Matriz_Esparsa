#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    float dado;
    int lin, col;
    struct nodo *prox;
}Matriz_Esparsa; 

Matriz_Esparsa *Cria_Nodo();
void Inicializa(Matriz_Esparsa **matriz);
void Insere_fim(Matriz_Esparsa **matriz, Matriz_Esparsa *nodo);
float Pesquisa(Matriz_Esparsa *matriz, int lin, int col);
void Excluir_lista(Matriz_Esparsa **matriz);
void Inserir_lista(Matriz_Esparsa **matriz);
void Inserir_Valor(Matriz_Esparsa *matriz);
Matriz_Esparsa *Soma_Matrizes(Matriz_Esparsa *matriz1, Matriz_Esparsa *matriz2, int tamanhoI, int tamanhoJ);
Matriz_Esparsa *Subtrai_Matrizes(Matriz_Esparsa *matriz1, Matriz_Esparsa *matriz2, int tamanhoI, int tamanhoJ);
Matriz_Esparsa *Multiplica_Matrizes(Matriz_Esparsa *matriz1, Matriz_Esparsa *matriz2, int linhasA, int colunasA, int linhasB, int colunasB);
Matriz_Esparsa *Matriz_Transposta(Matriz_Esparsa *matriz, int linhas, int colunas);
void Imprimir_Matriz(Matriz_Esparsa *matriz);
void Imprimir_Diagonal_Principal(Matriz_Esparsa *matriz);

static Matriz_Esparsa *cria_cabeca();
static void define_dimensoes(Matriz_Esparsa *matriz, int linhas, int colunas);
static void obtem_dimensoes(Matriz_Esparsa *matriz, int *linhas, int *colunas);

int main()
{
    Matriz_Esparsa *A = NULL, *B = NULL, *R = NULL;
    int linhasA = 0, colunasA = 0, linhasB = 0, colunasB = 0;
    int opc;

    printf("Matriz A:\n"); 
    Inserir_lista(&A); 
    obtem_dimensoes(A, &linhasA, &colunasA);
    printf("Matriz B:\n"); 
    Inserir_lista(&B); 
    obtem_dimensoes(B, &linhasB, &colunasB);

    do {
        printf("\n1-Imprimir A\n2-Imprimir B\n3-Inserir em A\n4-Inserir em B\n5-Soma A+B\n6-Subtrai A-B\n7-Multiplica A*B\n8-Transposta A\n9-Diagonal A\n10-Sair\nOpc: ");
        if (scanf("%d", &opc) != 1) break;
        switch (opc) {
            case 1: Imprimir_Matriz(A); break;
            case 2: Imprimir_Matriz(B); break;
            case 3: Inserir_Valor(A); break;
            case 4: Inserir_Valor(B); break;
            case 5:
                if (linhasA==linhasB && colunasA==colunasB) 
                { 
                    R = Soma_Matrizes(A,B,linhasA,colunasA); 
                    Imprimir_Matriz(R); 
                    Excluir_lista(&R); 
                }
                else printf("Dimensoes incompativeis para soma\n");
                break;
            case 6:
                if (linhasA==linhasB && colunasA==colunasB) 
                { 
                    R = Subtrai_Matrizes(A,B,linhasA,colunasA); 
                    Imprimir_Matriz(R); 
                    Excluir_lista(&R); 
                }
                else printf("Dimensoes incompativeis para subtracao\n");
                break;
            // case 7:
            //     if (colunasA==linhasB) { R = Multiplica_Matrizes(A,B,linhasA,colunasA,linhasB,colunasB); Imprimir_Matriz(R); Excluir_lista(&R); }
            //     else printf("Dimensoes incompativeis para multiplicacao\n");
            //     break;
            // case 8: R = Matriz_Transposta(A, linhasA, colunasA); Imprimir_Matriz(R); Excluir_lista(&R); break;
            // case 9: Imprimir_Diagonal_Principal(A); break;
            case 10: break;
            default: printf("Opcao invalida\n");
        }
    } while (opc != 10);

    Excluir_lista(&A); Excluir_lista(&B); Excluir_lista(&R);
    return 0;
}

static Matriz_Esparsa *cria_cabeca()
{ 
    Matriz_Esparsa *cab = (Matriz_Esparsa *)malloc(sizeof(Matriz_Esparsa));
    if (!cab){ printf("Problema de alocacao\n"); exit(0); }
    cab->dado = 0.0f; cab->lin = 0; cab->col = 0; cab->prox = NULL;
    return cab;
}

static void define_dimensoes(Matriz_Esparsa *matriz, int linhas, int colunas)
{
    if (!matriz) return; matriz->lin = linhas; matriz->col = colunas;
}

static void obtem_dimensoes(Matriz_Esparsa *matriz, int *linhas, int *colunas)
{
    if (!matriz) { *linhas = 0; *colunas = 0; return; }
    *linhas = matriz->lin; *colunas = matriz->col;
}

Matriz_Esparsa *Cria_Nodo()
{
    Matriz_Esparsa *p = (Matriz_Esparsa *)malloc(sizeof(Matriz_Esparsa));
    if (!p) { printf("Problema de alocacao\n"); exit(0); }
    return p;
}

void Inicializa(Matriz_Esparsa **matriz)
{
    if (!matriz) return; 
    if (*matriz) Excluir_lista(matriz); 
    *matriz = cria_cabeca();
}

void Insere_fim(Matriz_Esparsa **matriz, Matriz_Esparsa *nodo)
{
    if (!matriz || !*matriz || !nodo) return;

    Matriz_Esparsa *aux = *matriz; 
    while (aux->prox) 
    {
        aux = aux->prox; 
    }
    aux->prox = nodo;
    nodo->prox = NULL;
}

void Imprimir_Matriz(Matriz_Esparsa *matriz)
{
    if (!matriz) return; 
    int linhas, colunas; 
    obtem_dimensoes(matriz, &linhas, &colunas);
    for (int i = 0; i < linhas; ++i) 
    { 
        for (int j = 0; j < colunas; ++j) 
        {
            printf("%.2f ", Pesquisa(matriz, i, j)); 
            printf("\n"); 
        }   
    }
}

float Pesquisa(Matriz_Esparsa *matriz, int lin, int col)
{
    if (!matriz) return 0.0f;

    for (Matriz_Esparsa *aux = matriz->prox; aux; aux = aux->prox)
        if (aux->lin == lin && aux->col == col) 
            return aux->dado;
    return 0.0f;
}

void Excluir_lista(Matriz_Esparsa **matriz)
{
    if (!matriz || !*matriz) return;
    Matriz_Esparsa *p = *matriz; 

    while (p) 
    { 
        Matriz_Esparsa *prox = p->prox; 
        free(p); p = prox; 
    }
    *matriz = NULL;
}

void Inserir_lista(Matriz_Esparsa **matriz)
{
    int linhas, colunas;
    if (!matriz) return;
    Inicializa(matriz);
    printf("Digite o numero de linhas: ");
    scanf("%d", &linhas);
    printf("Digite o numero de colunas: ");
    scanf("%d", &colunas);
    define_dimensoes(*matriz, linhas, colunas);
    Inserir_Valor(*matriz);
}

void Inserir_Valor(Matriz_Esparsa *matriz)
{
    if (!matriz) return;
    int lin, col, linhas, colunas;
    float valor;
    obtem_dimensoes(matriz, &linhas, &colunas);

    printf("Digite os valores (0 em linha para parar):\n");
    while (1)
    {
        printf("lin: ");
        scanf("%d", &lin);
        if (lin == 0) break;

        printf("col: ");
        scanf("%d", &col);
        printf("valor: ");
        scanf("%f", &valor);

        if (lin < 0 || lin >= linhas || col < 0 || col >= colunas)
        {
            printf("Posicao invalida! Digite dentro dos limites (0-%d, 0-%d)\n", linhas - 1, colunas - 1);
            continue;
        }

        if (valor != 0.0f)
        {
            Matriz_Esparsa *n = Cria_Nodo();
            n->dado = valor;
            n->lin = lin;
            n->col = col;
            n->prox = NULL;
            Insere_fim(&matriz, n);
        }
    }
}

Matriz_Esparsa *Soma_Matrizes(Matriz_Esparsa *m1, Matriz_Esparsa *m2, int tamanhoI, int tamanhoJ)
{
    Matriz_Esparsa *res = NULL; 
    Inicializa(&res); 
    define_dimensoes(res, tamanhoI, tamanhoJ);

    for (int i = 0; i < tamanhoI; ++i)
        for (int j = 0; j < tamanhoJ; ++j)
        {
            float v = Pesquisa(m1, i, j) + Pesquisa(m2, i, j);
            if (v != 0.0f) 
            { 
                Matriz_Esparsa *n = Cria_Nodo(); 
                n->dado = v; 
                n->lin = i; n->col = j; 
                n->prox = NULL; 
                Insere_fim(&res, n); 
            }
        }
    return res;
}

Matriz_Esparsa *Subtrai_Matrizes(Matriz_Esparsa *m1, Matriz_Esparsa *m2, int tamanhoI, int tamanhoJ)
{
    Matriz_Esparsa *res = NULL; 
    Inicializa(&res); 
    define_dimensoes(res, tamanhoI, tamanhoJ);
    
    for (int i = 0; i < tamanhoI; ++i)
        for (int j = 0; j < tamanhoJ; ++j)
        {
            float v = Pesquisa(m1, i, j) - Pesquisa(m2, i, j);
            if (v != 0.0f) 
            { 
                Matriz_Esparsa *n = Cria_Nodo(); 
                n->dado = v; 
                n->lin = i; 
                n->col = j; 
                n->prox = NULL; 
                Insere_fim(&res, n); 
            }
        }
    return res;
}