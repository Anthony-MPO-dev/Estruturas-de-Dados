#include <stdio.h>
#include <conio.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include<time.h>//necessário p/ função time()
#include<string.h>

#define RANGE 100000 // define o range do valor maximo que pode ser atingido pelos valores gerados

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

int main(){

    int t; //t eh numero de valores a ser gerado 
    char arq_name[50];
    FILE *file;

    printf("N valores\n");
    scanf("%d", &t);

    printf("Nome arq\n");
    scanf("%s", &arq_name);

    file = fopen(arq_name, "a");

    // gerando valores aleatórios na faixa de 0 a t                
    int *numeros;
    numeros = malloc(RANGE * sizeof *numeros);

    if (!numeros) 
        exit(EXIT_FAILURE);

    for (int k = 0; k < RANGE; k++){
        numeros[k] = k + 1;
    }
    shuffle(numeros, RANGE); /* é usual usar método de Knuth */

    for(int y=0; y<100; y++){
        printf("%d\n",numeros[y]);
    }

    for (int k = 0; k < t; k++) 
        fprintf(file, "%d\n", numeros[k]);    
    
    fclose(file);
    return 0;
}