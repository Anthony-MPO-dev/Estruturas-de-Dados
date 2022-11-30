#include <stdio.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include<time.h>//necessário p/ função time()
#include<string.h>

#define RANGE 1023 // define o range do valor maximo que pode ser atingido pelos valores gerados


void swap (int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int arr[], int n){

    srand (time(NULL));

    for (int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);

        swap(&arr[i], &arr[j]);
    }
}


int main(int argc, char *argv[]){

    int i, t; //t eh numero de valores a ser gerado 
    int select; // seleciona entre 2 = valores aleatorios 1 = valores aleatorios pares
    char *arq_name;
    FILE *file;

    t = atoi(argv[1]);
    select = atoi(argv[2]);
    arq_name = argv[3];

    printf("Valor: %d\n", t);

    

    /* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
    com o valor da função time(NULL). Este por sua vez, é calculado
    como sendo o total de segundos passados desde 1 de janeiro de 1970
    até a data atual.
    Desta forma, a cada execução o valor da "semente" será diferente.
    */

    // gerando valores aleatórios na faixa de 0 a t                
    int *numeros;
    numeros = malloc(RANGE * sizeof *numeros);

    if (!numeros) 
        exit(EXIT_FAILURE);

    for (int k = 0; k < RANGE; k++){ // preenche o vetor atṕe 1023
        numeros[k] = k + 1;
    }

    shuffle(numeros, RANGE); /* é usual usar método de Knuth  para embaralhar o vetor*/

    if (select == 1){
       
        file = fopen(arq_name, "a");

            
        
        int cont_a = 0;
        int cont_b = 0;
        while (cont_a < t){
            while ( numeros[cont_b] % 2 != 0 ){
                    cont_b++;
            }

            if (cont_a >= t-1)
                fprintf(file, "%d", numeros[cont_b]); 
            else  
                fprintf(file, "%d\n", numeros[cont_b]);

            cont_a++;
            cont_b++;
        }

        fclose(file);

    }
    
    else if (select == 2){

        file = fopen(arq_name, "a");

        for (i = 0; i < t; i++) {
            if (i >= t-1)
                fprintf(file, "%d", numeros[i]); 
            else  
                fprintf(file, "%d\n", numeros[i]);
        } 
    

        
        fclose(file);
    }

    else
        printf("Valor invalido escolha entre 1 e 2\n\n");
    
    return 0;
    
}