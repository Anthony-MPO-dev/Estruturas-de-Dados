#include <stdio.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include<time.h>//necessário p/ função time()
#include<string.h>

#include "aluno.c"

#define RANGE 30228 // define o range do valor maximo que pode ser atingido pelos valores gerados



/*void swap (int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
*/
void ramdom(int arr[], int n, int t){
   
    srand (time(NULL));
 
    for (int i = t-1; i > 0; i--){
        arr[i] = rand() % (n);
 
        //swap(&arr[i], &arr[j]);
    }
}


int main(){
    srand (time(NULL));    
    int t; //t eh numero de valores a ser gerado
    int tam =  30228; 
    char arq_name[50];
    FILE *file;
    FILE *file2;
   

    printf("N valores\n");
    scanf("%d", &t);

    Alunos *v[tam]; //cria o vetor de alunos com base no numero de caracteres que vai ser inserido os valores
    
    printf("Nome arq\n");
    scanf("%s", &arq_name);

    

    // gerando valores aleatórios na faixa de 0 a t                
    int *numeros;
    numeros = malloc(t * sizeof *numeros);

    if (!numeros) 
        exit(EXIT_FAILURE);

   /* for (int k = 0; k < RANGE; k++){
        numeros[k] = k + 1;
    }
    */

    ramdom(numeros, RANGE, t); /* é usual usar método de Knuth */

   
    file2 = fopen("DadosEnem.txt", "r");//dados do enem
    int i = 0;

    while(!feof(file2)){

        //cria um ponterio tipo aluno e aloca a memoria 
        v[i] = (Alunos *)malloc(sizeof(Alunos));

        //scaneia o arquivo e retira os valores que seram utilizados para construção das arvores
        fscanf(file2, "%d %s %s %s %lf %lf %lf %lf %lf", 
        &v[i]->id, 
         v[i]->estado, 
         v[i]->municipio, 
         v[i]->rede,
        &v[i]->media_ciencias_natureza,
        &v[i]->media_ciencias_humanas,
        &v[i]->media_linguagem,
        &v[i]->media_matematica,
        &v[i]->media_redacao
        );

        i++;
    }

    int n2 = sizeof(v)/sizeof(int);
    printf("Tamanho do vetor: %d\n", n2);

    file = fopen(arq_name, "a");
    
    for (int k = 0; k < t; k++){  

        printf("%d\n", numeros[k]); //escreve os dados no arquivo   

    } 
    
    for (int k = 0; k < t; k++){      

        
        //escreve os dados no arquivo
        
            fprintf(file, "%d", 
            v[numeros[k]]->id); 
        if(k != t-1){
            fprintf(file, "\n");  
        }

    } 
    
    fclose(file);
    fclose(file2);
    return 0;
}