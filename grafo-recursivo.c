// Cria um grafo, acha um caminho e retorna seu custo usando recursão
#include <stdio.h>
#include <stdlib.h>

// PROTÓTIPOS DAS FUNÇÕES
// FUNÇÕES PARA MANIPULAR O GRAFO
int **ler_grafo(int *qtd_vertice, int *qtd_aresta);
void printa_grafo(int qtd_vertice, int **grafo);
int zera_grafo(int qtd_vertice, int **grafo);
void destroi_grafo(int qtd_vertice, int **grafo);
int **cria_grafo(int qtd_vertice);

// FUNÇÃO PARA CHECAR A EXISTÊNCIA DE CAMINHO
int existe_caminho(int v_saida, int v_chegada, int qtd_vertice, int **grafo);

int main(void)
{
    // Para algo ser vizinho de N, tenho que grafo[N][i] != 0

    int qtd_vertice, qtd_arestas;

    int **grafo = ler_grafo(&qtd_vertice, &qtd_arestas);

    printa_grafo(qtd_vertice, grafo);
    printf("\n");

    printf("Digite os vertices para encontrar o caminho entre: ");
    int v_saida, v_chegada; // Vertices de saída e chegada
    scanf("%d", &v_saida);
    scanf("%d", &v_chegada);

    // Decrementa os valores para indicarem a posição correta no grafo
    v_saida--;
    v_chegada--;

    int resultado = existe_caminho(v_saida, v_chegada, qtd_vertice, grafo);
    printf("Custo do caminho: %d\n", resultado);

    destroi_grafo(qtd_vertice, grafo);
    return 0;
}

// Esta função está limitada a buscar um caminho por vértices que tenham mais de um vizinho
int existe_caminho(int v_saida, int v_chegada, int qtd_vertice, int **grafo)
{
    // Checa se os vértices são valores válidos
    if (v_saida < 0 || v_chegada < 0)
        return -1;
    if (v_saida >= qtd_vertice || v_chegada >= qtd_vertice)
        return -1;

    int j;
    int custo_caminho = 0;

    // Se o vértice de saída (v_saida) é vizinho do vértice de chegada (v_chegada)
    if (grafo[v_saida][v_chegada] != 0)
    {
        // Retorna o custo do caminho entre o vértice de saída e o vértice de chegada
        return grafo[v_saida][v_chegada];
    }
    // Percorre a base de dados buscando um vértice vizinho
    for (j = 0; j < qtd_vertice; j++)
    {
        // Se o vértice de saída tem um vizinho
        if (grafo[v_saida][j] != 0)
        {
            // Checa se existe um caminho entre o vértice j e o vértice de chegada
            custo_caminho = existe_caminho(j, v_chegada, qtd_vertice, grafo);
            if (custo_caminho != -1)
            {
                custo_caminho += grafo[v_saida][j];
                return custo_caminho;
            }
        }
    }
    // Retorna -1 para indicar que um vértice em questão não tem vizinhos
    return -1;
}

//
//
// FUNÇÕES QUE TRATAM O GRAFO //
//
//

// Na prática esta função cria uma matriz quadrada de tamanho vértice usando alocação dinâmica
int **cria_grafo(int qtd_vertice)
{
    // Aloca memória para um ponteiro que guardará vértices de tamanho int * (ponteiro pra inteiro)
    int **grafo = malloc(qtd_vertice * sizeof(int *));
    if (grafo == NULL)
        return NULL;

    // Aloca memória para um ponteiro para inteiro de tamanho vértice
    int i;
    for (i = 0; i < qtd_vertice; i++)
    {
        grafo[i] = malloc(qtd_vertice * sizeof(int));
        if (grafo[i] == NULL)
            return NULL;
    }

    return grafo;
}

void destroi_grafo(int qtd_vertice, int **grafo)
{
    int i;
    for (i = 0; i < qtd_vertice; i++)
    {
        // Libera cada vetor alocado para grafo
        free(grafo[i]);
    }
    // Libera o vetor de vetores grafo
    free(grafo);

    return;
}

int zera_grafo(int qtd_vertice, int **grafo)
{
    // Checa se o vértice ou grafo são válidos
    if (qtd_vertice <= 0 || grafo == NULL)
        return -1;

    // Zera o grafo
    int i, j;
    for (i = 0; i < qtd_vertice; i++)
    {
        for (j = 0; j < qtd_vertice; j++)
        {
            grafo[i][j] = 0;
        }
    }

    return 1;
}

void printa_grafo(int qtd_vertice, int **grafo)
{
    int i, j;

    // Checa se o vértice ou grafo são válidos
    if (qtd_vertice <= 0 || grafo == NULL)
        return;

    // Printa o grafo na tela como uma matriz
    printf("\n");
    for (i = 0; i < qtd_vertice; i++)
    {
        for (j = 0; j < qtd_vertice; j++)
        {
            printf("%.3d ", grafo[i][j]);
            printf(" ");
        }

        printf("\n");
    }
}

int **ler_grafo(int *qtd_vertice, int *qtd_aresta)
{
    // Inicia os vertices, arestas e grafos a serem utilizados
    printf("Digite a quantidade de vertices e a quantidade de arestas (respectivamente): ");

    *qtd_vertice = -1;
    scanf("%d", qtd_vertice);

    *qtd_aresta = -1;
    scanf("%d", qtd_aresta);

    // Exige que o usuário digite um valor maior que zero (assumi que ele não sabe que indexamos em 0)
    if (*qtd_vertice <= 0 || *qtd_aresta <= 0)
        return NULL;

    // Cria um matriz chamada grafo usando alocação dinâmica
    int **grafo = cria_grafo(*qtd_vertice);

    // Zera o grafo para indicar que ninguém e vizinho de ninguém
    if (zera_grafo(*qtd_vertice, grafo) == -1)
        return NULL;

    int vertice_a = -1;
    int vertice_b = -1;
    int aresta = 0; // O custo da aresta
    // Esta é uma cópia da quantidade de arestas, para não alterar o valor dela
    int copia_qtd_aresta = *qtd_aresta;

    printf("Digite os vertices a serem vizinhos e o custo da aresta que os conecta (respectivamente)\n");
    // Lê as entradas do usuário e as coloca dentro do vetor grafo
    while(copia_qtd_aresta > 0)
    {
        scanf("%d", &vertice_a);
        scanf("%d", &vertice_b);
        scanf("%d", &aresta);

        // Caso a leitura de alguma das variáveis dê erro, ou o usuário digite um número negativo, a função retorna erro
        if (vertice_a <= 0 || vertice_b <= 0)
            return NULL;

        // Caso o usuário resolva colocar o valor de um vertice inválido, a função retorna erro
        if (vertice_a == vertice_b || vertice_a > *qtd_vertice || vertice_b > *qtd_vertice)
            return NULL;

        // Coloca as arestas nas posições correspondentes do grafo
        grafo[vertice_a - 1][vertice_b - 1] = aresta;

        // Atualiza as variáveis para um novo ciclo de checagens
        vertice_a = -1;
        vertice_b = -1;
        copia_qtd_aresta--;
    }

    return grafo;
}
