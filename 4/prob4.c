#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Renan

gcc prob4.c -o main
*/  
  
//Retorna o número minimo de edicoes entre as duas sequencias
int recDNA(char linha1[], char linha2[], int tam1, int tam2)
{
	int matriz[tam1+1][tam2+1]; //matriz para armazenar a qtd de edicoes
	//variaveis auxiliares
	int minimo;
	int inserir, remover, substituir; //ira armazenar a qtd de edicoes em cada caso
	int i, j;

	 for (i=0; i<=tam1; i++) 
    { 
        for (j=0; j<=tam2; j++) 
        { 
        	//caso i==0 significa que a linha1 chegou ao final
        	//retorna a qtd que restou da linha2
            if(i==0) 
                matriz[i][j] = j;  
        	//caso j==0 significa que a linha2 chegou ao final
        	//retorna a qtd que restou da linha1
            else if(j==0) 
                matriz[i][j] = i;
            //Caso os caracteres sejam iguais
            //Verifica proximo caracter
            //nao modifica a qtd de edicoes
            else if (linha1[i-1] == linha2[j-1]) 
                matriz[i][j] = matriz[i-1][j-1]; 
            else
            {
            	//Caso os caracteres sejam diferentes
            	//Verifica a qtd de edicoes em cada caso
            	inserir = matriz[i][j-1];
            	remover = matriz[i-1][j];
            	substituir = matriz[i-1][j-1];

            	//Obtem o menor valor entre as 3 possibilidades
            	minimo = inserir;
				if(remover < minimo)
					minimo = remover;
				if(substituir < minimo)
					minimo = substituir;
				//acrescenta uma edicao
				minimo++;
				//armazena qtd de edicoes ate o momento
                matriz[i][j] = minimo;
            }
            
        } 
    }   
    //retorna qtd minima de edicoes
    return matriz[tam1][tam2]; 
}

int main(int argc, char **argv)
{
   char linha1[1000], linha2[1000];

   scanf("%s", linha1); //ler primeira sequencia de DNA
   scanf("%s", linha2); //segunda sequencia DNA

   //exibe resposta
   printf("%d", recDNA(linha1, linha2, strlen(linha1), strlen(linha2)));

   return 0;
}