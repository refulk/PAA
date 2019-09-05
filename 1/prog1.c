    #include <stdio.h>
    /*
    Renan
        
    Problema de calcular o custo de organizar contratos, onde só é possível realizar trocas entre contratos localizados em posições consecutivas, resolvido utilizando-se mergesort.
    */  
    long long int merge(int *vetor, int *aux, int esq, int m, int dir) 
    { 
        int i, j, k; 
        long long int cont = 0;   
        i = esq; // Esq
        j = m;  // Dir
        k = esq; //Aux
     
        while ((i <= m - 1) && (j <= dir)) 
        { 
            if (vetor[i] <= vetor[j]) 
            { 
                aux[k] = vetor[i];  // não inverteu, manteve a ordem
                k++;
                i++;
            } 
            else 
            { 
                aux[k] = vetor[j]; // inverte a ordem
                k++;
                j++; 
                cont += (m - i); //realiza a soma
                // soma a quantidade de trocas de pares que seriam necessárias
                // para realizar a troca
            } 
        } 
      
        while (i <= m - 1) // copia o restante do vetor para aux
        {
            aux[k] = vetor[i]; 
            k++;
            i++;
        }
      
        while (j <= dir) // copia o restante do vetor para aux
        {
            aux[k] = vetor[j]; 
            k++;
            j++;
        }
      
        for (i = esq; i <= dir; i++) // copia de volta o vetor ordenado
        {
            vetor[i] = aux[i]; 
        }
      
        return cont; 
    } 
     
    long long int mergeSort2(int *vetor, int *aux, int esq, int dir) 
    { 
        int m; 
        long long int cont = 0;
        if (dir > esq) //enquanto tem 2 elementos ou mais no vetor recebido
        { 
            m = (dir + esq) / 2;   // define o meio do vetor
            cont += mergeSort2(vetor, aux, esq, m); //metade esquerda
            cont += mergeSort2(vetor, aux, m + 1, dir);  // metade direita
            cont += merge(vetor, aux, esq, m + 1, dir); //Apos dividir, comeca a juntar as partes de maneira ordenada
        } 
        return cont; 
    } 
     
    long long int mergeSort(int *vetor, int qtd) 
    { 
        int aux[qtd];
        return mergeSort2(vetor, aux, 0, qtd - 1); 
    } 
      
    int main(int argc, char *argv)
    {
        long long int qtd;
        int i;
        int verifica = 0;
     
        scanf("%lli", &qtd); //ler quantidade de entradas
        int vetor[qtd];
     
        scanf("%d", &vetor[0]); //ler cada elemento do vetor
        for(i = 1; i < qtd; i++)
        {
          scanf("%d", &vetor[i]); //ler cada elemento do vetor
          if(vetor[i] > vetor [i-1]) //Caso o vetor esteja completamente na ordem decrescente
            verifica = 1;
        }
        
        if(verifica == 1)
          printf("%lli", mergeSort(vetor, qtd)); // chama a funcao e exibe retorno
        else
          printf("%lli", ((qtd)*(qtd-1))/2);
        return 0;
    }