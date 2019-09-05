#include <stdio.h>
#include <stdlib.h>
/*

Renan

gcc prob2.c -o prog
*/  

void exibeMatriz(int **matriz, int n)
{
    int i, j;
    printf("  ");
    for(i = 1; i <= n; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    for(i = 0; i < n; i++)
    {
        printf("%d ", (i+1));
        for(j = 0; j < n+1; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

//retorna a quantidade de pessoas que podem ir na festa
int buscaRelacoes(int **matriz, int n, int k)
{
    int out = 1;
    int soma = 0, i, j;
    int resp = 0;

    while(out) //enquanto ao menos uma relacao for excluida na rodada anterior
    {
        out = 0;
        for(i = 0; i < n; i++) //percorre colunas
        {
            if(matriz[i][n] != -1) //Nao percorre a linha pois ja foi excluida
            {
                soma = 0;
                for(j = 0; j < n; j++) //percorre a linha
                {
                    if(matriz[i][j] == 1) //se existir relacao
                    {
                        soma++; //soma as relacoes
                    }
                }
                if(soma < k) //Caso a qtd de relacoes for menor do que a quantidade solicitada
                {
                    out = 1; //while ira executar mais uma vez
                    matriz[i][n] = -1; //exclui a linha para OTIMIZAR, nao precisa percorrer a linha
                    for(j = 0; j < n; j++) //percorre a coluna para excluir a relacao em outras linhas
                    {
                        matriz[j][i] = 0; //excluir a relacao
                    }
                }
            }            
        }

    }

    for(i = 0; i < n; i++) //conta quantidade de pessoas que podem ir na festa
    {
        if(matriz[i][n] != -1) //se a linha nao foi excluida
        {
            resp++;
        }
    }

    return resp;
}

int main(int argc, char *argv)
{
    int n; //qtd pessoas
    int p; //total relacoes
    int k; //minimo relacoes por pessoa

    int a, b;
    int i, j;
    scanf("%d %d %d", &n, &p, &k); //numero de pessoa, total relacoes, minimo de relacoes
    int **matriz;
    matriz = (int**)calloc (n, sizeof(int*)); //declara qtd de colunas
    for(i=0;i<n;i++)
    {
        //declara qtd de linhas.
        //n+1 pois a ultima posicao de cada linha 
        //representa se a linha foi excluida ou nao
        matriz[i] = (int*) calloc (n+1, sizeof(int));
    }

    for(i = 0; i < p; i++)
    {
        //ler as relacoes
        //e acrescentar na matriz de adjacencia
        scanf("%d %d", &a, &b);
        a--;
        b--;
        matriz[a][b] = 1;
        matriz[b][a] = 1;
    }

    // exibeMatriz(matriz, n);

    //exibe resposta
    printf("%d", buscaRelacoes(matriz, n, k)); 

    return 0;
}

