/*Lorenzo Paciello -- NUSP: 10734182*/
/*Rodolfo Luis Cassimiro -- NUSP: 10295238*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "fila.h"

int main()
{
    Grafo *grafo = NULL; /*grafo que armazenara os vertices e arestas*/
    FILE *f = fopen("input-top-grossing.txt", "r");
    char *aux, ator[40], op; /*auxiliares*/
    int pos = 0; /*variavel de controle da posicao dos vertices e do total de vertices do grafo*/
    int flag = 0;
    float mediaTotal, somaD; /*variaveis que armazenam a media e o desvio*/

    aux = malloc(2000 * sizeof(char));/*aloca memoria equilavente ao maior numero de elementos de um filme*/

    printf("Carregando grafo...\n");
    while (fgets(aux, 2000, f)) /*enquanto nao chegar ao final do arquivo*/
    {
        separaCampos(aux, &grafo, &pos); /*separa os campos em vertices e arestas, e incrementa a variavel de posicao*/
    }
    free(aux); /*desaloca a memoria da auxiliar*/
    printf("Grafo carregado!\n\n");

    do
    {
        printf("1 - Pesquisar KB\n2 - Sair\n\n"); /*menu de opcoes*/
        printf("Opcao: ");
        scanf(" %c", &op); /*entrada do usuario*/

        switch (op)
        {
        case '1':; /*Pesquisar KB*/
            Antecessor *contador = NULL; /*variavel que armazena o caminho de forma linear*/
            int auxAntecessor; /*variavel que armazena o KB*/
            printf("Utilize o arquivo texto como referencia.\n");
            printf("Digite o nome do ator/atriz: ");
            scanf(" %[^\n]", ator);
            if(buscaKB(grafo, &pos, ator, &auxAntecessor, &contador) == 0) /*vertice inexistente*/
            {
                printf("Ator/Atriz inexistente!\n\n");
            }
            else if (buscaKB(grafo, &pos, ator, &auxAntecessor, &contador) == 1) /*encontrou caminho ate "Bacon, Kevin"*/
            {
                int i;
                printf("\n'%s' tem KB = %d\n", ator, auxAntecessor - 1);

                for (i = auxAntecessor - 2; i >= 0; i--) /*percorre o vetor de tras pra frente para visualizacao dos dados em ordem*/
                {
                    printf("'%s' atuou em '%s' com '%s'\n", contador[i].atorAtual, contador[i].filme, contador[i].atorAnterior);
                }
                printf("\n");
                free(contador);
            }
            else
            {
                printf("'%s' tem KB = infinito\n\n", ator); /*retornou 2, ou seja, nao ha caminho*/
            }    
            break;
        }

    } while (op != '2'); /*Sair*/

    printf("\nFinalizando...\n\n");

    liberaGrafo(grafo); /*desaloca a memoria do grafo*/
    fclose(f);/*fecha o arquivo*/

    return 0;
}
