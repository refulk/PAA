#include <stdio.h>
#include <stdlib.h>
/*
Renan

gcc prob3.c -o prog
*/  

//Funcao para exibir o vetor
//utilizada para testes
void exibeVetor(int *v, int tam)
{
	int i;
	for(i = 0; i<tam;i++)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

//Dado um vetor (e o mesmo vetor invertido) e o indice de 'corte' (posicao onde ira dobrar)
// essa funcao realiza uma dobra e armazena o resultado no vetor 'retorno'
// Retorna 0 caso o tamanho da resposta seja menor que o tamanho 'm'
// Retorna 0 caso algum elemento resultante seja maior que maxElement
// Retorna 1 caso o 'retorno' seja um possivel caminho para a resposta ou seja uma possivel resposta
int dobra(int *va, int *vb, int n, int corte, int *retorno, int *tam, int maxElement, int m)
{
	int i, limite;
	int meio = n/2;
	int indA = 0;
	int indB = 0;

	//se o indice de corte for menor ou igual a metade 
	// do tamanho do vetor original
	if(corte <= meio)
	{
		//limite eh o tamanho do vetor resposta
		limite = n-corte;
	}
	else
	{
		//limite eh o tamanho do vetor resposta
		limite = corte;
	}

	(*tam) = limite; //tamanho do vetor apos a dobra

	//se o tamanho do vetor resposta for menor
	//do que o tamanho do vetor resposta
	//pode descartar esse braco de opcoes
	if(limite < m) 
	{
		//tamanho menor, ja eh descartado
		return 0;
	}

	//A cada repeticao ira gerar um elemento da resposta
	for(i = 0; i < limite; i++)
	{
		if(corte <= meio)
		{
			//corte antes do meio do vetor
			//no meio entra aqui tambem, mas tanto faz

			//seta valores dos indices dos vetores
			indA = i-(limite-corte); //indice do vetor original
			indB = i;				//indice do vetor invertido

			//caso esse indice seja positivo
			if(indA >= 0) 
			{	
				//deve realizar a soma dos valores
				retorno[i] = va[indA] + vb[indB];
			}
			else
			{
				//se for negativo, nao existe elemento para somar
				retorno[i] = vb[indB];
			}
		}
		else
		{	
			//corte apos o meio do vetor

			//seta valores dos indices dos vetores
			indA = i;					//indice do vetor original
			indB = i - (2*limite) + n;	//indice do vetor invertido

			//caso o indice de B seja positivo
			if(indB >= 0)
			{
				//deve realizar a soma dos valores
				retorno[i] = va[indA] + vb[indB];
			}
			else
			{
				//se for negativo, nao existe elemento de B para somar
				retorno[i] = va[indA];
			}
		}
		//caso um dos elementos seja maior do que todos os elementos do vetor original
		if(retorno[i] > maxElement)
		{
			return 0; //pode descartar esse ramo de recursao
		}		
	}
	return 1;
}
  
//funcao retorna 1 se a resposta for compativel
// 0 se a resposta nao for compativel
int verificaResposta(int *vet, int tam, int maxTest, int *w, int m)
{
	int i;
	//caso o tamanho seja diferente
	// ou o elementoMax seja invalido
	if(tam != m || maxTest == 0)
	{
		//nao eh valido
		return 0;
	}
	
	//compara se os vetores sao iguais
	for(i = 0; i < tam; i++)
	{
		//se houver algum elemento diferente
		//retorna zero pois nao eh compativel
		if(vet[i] != w[i])
			return 0;
	}

	//se todos os elementos forem iguais
	return 1; // resposta compativel
}

//Funcao recursiva
//que ira validar se a entrada eh uma resposta valida
int simpSenhaRec(int *va, int *w, int n, int m, int maxElement)
{
	int vb[n], retorno[n], tam = 0, maxTest = 1, resp = 0;
	int i;

	//>Se tiver apenas 1 elemento verifica esse elemento
	//>Se n<m o vetor n ja eh menor que o vetor m que estamos procurando
	// por isso tbm ja pode retornar
	if(n < m)
	{
		return 0;
	} else if (n == 1)
	{
		return verificaResposta(va, n, 1, w, m);
	}

	//vetor 'vb' é o vetor 'va' invertido
	//para facilitar as operacoes
	for(i = 0; i < n; i++) 
	{
		vb[i] = va[n-i-1];
	}

	//verifica se vetor va eh compativel
	if(verificaResposta(va, n, 1, w, m) == 1)
	{
		return 1;
	}

	//verifica se vetor invertido eh compativel
	//equivale a primeira e a ultima dobra
	if(verificaResposta(vb, n, 1, w, m) == 1)
	{
		return 1;
	}

	//realiza todas as dobras restantes
	// a primeira e a ultima ja foi feita com o vetor invertido
	// por isso o looping vai de 1 ate n-1 apenas
	for(i = 1; i < n; i++)
	{
		//caso maxTest = 0, ja pode descartar esse 'retorno'
		maxTest = dobra(va, vb, n, i, retorno, &tam, maxElement, m);

		//verifica se 'retorno' eh compativel
		if(verificaResposta(retorno, tam, maxTest, w, m) == 1)
		{
			return 1;
		}
		else
		{
			resp = 0;
		}

		//caso maxTest == 0 podemos descartar o ramo
		//por isso so ira chamar a funcao recursiva caso maxTest == 1
		if(maxTest == 1) 
		{
			//exibeVetor(retorno, tam);
			resp = simpSenhaRec(retorno, w, tam, m, maxElement);
		}

		//caso encontre a resposta,
		//pode parar o looping e retornar
		//caso contrario, o looping continua procurando
		if(resp == 1)
		{
			return 1;
		}
	}
	return resp;
}

int main(int argc, char *argv)
{
	int n, m, i, resp, maxElement, temp = -1;

    scanf("%d", &n); //numero de elementos vet original
    int v[n];

	//ler elementos do vetor origem
    for(i = 0; i < n; i++)
    {
    	scanf("%d", &v[i]); 
    }

    scanf("%d", &m); //numero de elementos da suposta resposta
    int w[m];

	//ler elementos do vetor da possivel solucao
	//Tambem armazena o 'maxElement', que eh o maior valor do vetor
    for(i = 0; i < m; i++)
    {
    	scanf("%d", &temp); 
		if(i == 0)
			maxElement = temp;
		else if(maxElement < temp)
		{
			maxElement = temp;
		}
		w[i] = temp;
    }

	//Chama a funcao recursiva
    resp = simpSenhaRec(v, w, n, m, maxElement);
	//Se retornar 1, a entrada eh valida
	//Caso contrario, nao eh valida
	if(resp == 1)
		printf("S");
	else
		printf("N");
    return 0;
}
