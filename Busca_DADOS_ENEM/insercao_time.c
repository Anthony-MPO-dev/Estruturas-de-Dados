#ifndef INSER_TIME//Verificacao se biblioteca foi carregada
#define INSER_TIME

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //necessário para usar tempo
#define BILLION  1000000000.0

#include "ArvoreBin.c"
#include "ArvoreAVL.c"
#include "ArvoreRB.c"

//cria variavel do tipo file
FILE *file;


struct timespec start, end;
struct timespec begin, endin;

double time_spent = 0.000000; //variavel para armazenar os microsegundos
double time_2 = 0.000000;

ArvBin *tempo_e_Insercao_ARVBinaria(ArvBin *Arvore_Binaria, Alunos *v[], int tam){

    //----------------------------ARVORE BINARIA----------------------------------//
                                    
    clock_gettime(CLOCK_REALTIME, &start);                            // cronometra o tempo de inicio
    //insere arvore Binaria de busca Balanceada                       //
    for(int i = 0; i < tam-1; i++){                                       //
        Arvore_Binaria = insereArvBin(Arvore_Binaria, v[i]->id, v[i]);//
    }                                                                 //com o tempo de final
    clock_gettime(CLOCK_REALTIME, &end);
 
    // time_spent = fim - início
    time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / BILLION;

    printf("Tempo de inserção Arvore Binaria %f segundos\n", time_spent);
 
    return Arvore_Binaria;
    

}


ArvAVL *tempo_e_Insercao_AVL(ArvAVL *Arvore_AVL, Alunos *v[], int tam, int *rt){

     //----------------------------ARVORE AVL----------------------------------//

    clock_gettime(CLOCK_REALTIME, &start);   
    //insere arvore AVL
    for(int i = 0; i < tam-1; i++){
        Arvore_AVL = insereArvAVL(Arvore_AVL, v[i]->id, v[i], rt);
    }
    clock_gettime(CLOCK_REALTIME, &end);
 
    // time_spent = fim - início
    time_spent = (end.tv_sec - start.tv_sec) +
                (end.tv_nsec - start.tv_nsec) / BILLION;
 
    printf("Tempo de inserção Arvore AVL %f segundos\n", time_spent);
    
    return Arvore_AVL;

}

ArvRB *tempo_e_Insercao_RB(ArvRB *Arvore_RB, Alunos *v[], int tam,int *rt){

    //----------------------------RUBRO NEGRA----------------------------------//

    clock_gettime(CLOCK_REALTIME, &start);  
    //insere arvore Rubro-Negra
    for(int i = 0; i < tam-1; i++){
        Arvore_RB = insereArvRB(Arvore_RB, v[i]->id, v[i], rt);
    }
    clock_gettime(CLOCK_REALTIME, &end);
 
    // time_spent = fim - início
    time_spent = (end.tv_sec - start.tv_sec) +
                (end.tv_nsec - start.tv_nsec) / BILLION;
 
    printf("Tempo de inserção RUBRO-NEGRA %f segundos\n", time_spent);

    return Arvore_RB;

}

//----------------------------FIM DAS INSERÇÕES----------------------------------//


//============================ALGORITIMOS DE CALCULO DE TEMPO EM BUSCA===================================//


//****************BUSCA EM ARVORE BINARIA*********************//
void *ARVBinaria_Busca(ArvBin *raiz, char *PATH){

    int chave;                                        
    //file recebe o arquivo e retira os valores
    file = fopen(PATH, "r");

    int i = 0;

    clock_gettime(CLOCK_REALTIME, &begin); 
    while(!feof(file)){
        //scaneia o arquivo e retira os valores para realização da busca
        fscanf(file, "%d", &chave);
        buscaArv_BI(raiz, chave);
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &endin);
     // time_spent = fim - início
    time_2 = (endin.tv_sec - begin.tv_sec) +
                (endin.tv_nsec - begin.tv_nsec) / BILLION;
 
    printf("|----[Tempo de busca com %d valores duracao: %f segundos]----|\n",i , time_2);
}

//********************DISTRIBUIÇÂO DOS CONJUTOS*********************//
void ARVBinaria_Conjutos_de_Busca(ArvBin *Arvore_Binaria){
    char *PATH = "arqs/100v.txt";
    printf("TEMPO DE BUSCA ARV BINARIA\n");

    clock_gettime(CLOCK_REALTIME, &start); 
        ARVBinaria_Busca(Arvore_Binaria, PATH);
        PATH = "arqs/mil.txt";
        ARVBinaria_Busca(Arvore_Binaria, PATH);
        PATH = "arqs/10mil.txt";
        ARVBinaria_Busca(Arvore_Binaria, PATH);
        PATH = "arqs/50mil.txt";
        ARVBinaria_Busca(Arvore_Binaria, PATH);
        PATH = "arqs/100mil.txt";
        ARVBinaria_Busca(Arvore_Binaria, PATH);
        PATH = "arqs/300mil.txt";
        ARVBinaria_Busca(Arvore_Binaria, PATH);
        PATH = "arqs/500mil.txt";
        ARVBinaria_Busca(Arvore_Binaria, PATH);
        PATH = "arqs/1mi.txt";
        ARVBinaria_Busca(Arvore_Binaria, PATH);
    clock_gettime(CLOCK_REALTIME, &end);

    // time_spent = fim - início
    time_spent = (end.tv_sec - start.tv_sec) +
                (end.tv_nsec - start.tv_nsec) / BILLION;
 
    printf("|----[TEMPO TOTAL: %f segundos]----|\n", time_spent);
}

//****************BUSCA EM ARVORE AVL*********************//
void *ARV_AVL_Busca(ArvAVL *raiz, char *PATH){

    int chave;                                        
    //file recebe o arquivo e retira os valores
    file = fopen(PATH, "r");
    int i=0;
    clock_gettime(CLOCK_REALTIME, &begin); 
    while(!feof(file)){
        //scaneia o arquivo e retira os valores para realização da busca
        fscanf(file, "%d", &chave);
        buscaArv_AVL(raiz, chave);
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &endin);
     // time_spent = fim - início
    time_2 = (endin.tv_sec - begin.tv_sec) +
                (endin.tv_nsec - begin.tv_nsec) / BILLION;
 
    printf("|----[Tempo de busca com %d valores duracao: %f segundos]----|\n", i, time_2);
}

//********************DISTRIBUIÇÂO DOS CONJUTOS*********************//
void ARV_AVL_Conjutos_de_Busca(ArvAVL *Arvore_AVL){
    char *PATH = "arqs/100v.txt";
    printf("TEMPO DE BUSCA AVL\n");

    clock_gettime(CLOCK_REALTIME, &start); 
        ARV_AVL_Busca(Arvore_AVL, PATH);
        PATH = "arqs/mil.txt";
        ARV_AVL_Busca(Arvore_AVL, PATH);
        PATH = "arqs/10mil.txt";
        ARV_AVL_Busca(Arvore_AVL, PATH);
        PATH = "arqs/50mil.txt";
        ARV_AVL_Busca(Arvore_AVL, PATH);
        PATH = "arqs/100mil.txt";
        ARV_AVL_Busca(Arvore_AVL, PATH);
        PATH = "arqs/300mil.txt";
        ARV_AVL_Busca(Arvore_AVL, PATH);
        PATH = "arqs/500mil.txt";
        ARV_AVL_Busca(Arvore_AVL, PATH);
        PATH = "arqs/1mi.txt";
        ARV_AVL_Busca(Arvore_AVL, PATH);
    clock_gettime(CLOCK_REALTIME, &end);

    // time_spent = fim - início
    time_spent = (end.tv_sec - start.tv_sec) +
                (end.tv_nsec - start.tv_nsec) / BILLION;
 
    printf("|----[TEMPO TOTAL: %f segundos]----|\n", time_spent);
}

//****************BUSCA EM ARVORE RUBRO NEGRA*********************//
void *ARV_RB_Busca(ArvRB *raiz, char *PATH){

    int chave;                                        
    //file recebe o arquivo e retira os valores
    file = fopen(PATH, "r");
    int i=0;
    clock_gettime(CLOCK_REALTIME, &begin); 
    while(!feof(file)){
        //scaneia o arquivo e retira os valores para realização da busca
        fscanf(file, "%d", &chave);
        buscaArv_RB(raiz, chave);
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &endin);
     // time_spent = fim - início
    time_2 = (endin.tv_sec - begin.tv_sec) +
                (endin.tv_nsec - begin.tv_nsec) / BILLION;
 
    printf("|----[Tempo de busca com %d valores duracao: %f segundos]----|\n", i, time_2);
}

//********************DISTRIBUIÇÂO DOS CONJUTOS*********************//
void ARV_RB_Conjutos_de_Busca(ArvRB *Arvore_RB){
    char *PATH = "arqs/100v.txt";
    printf("TEMPO DE BUSCA RUBRO NEGRA\n");

    clock_gettime(CLOCK_REALTIME, &start); 
        ARV_RB_Busca(Arvore_RB, PATH);
        PATH = "arqs/mil.txt";
        ARV_RB_Busca(Arvore_RB, PATH);
        PATH = "arqs/10mil.txt";
        ARV_RB_Busca(Arvore_RB, PATH);
        PATH = "arqs/50mil.txt";
        ARV_RB_Busca(Arvore_RB, PATH);
        PATH = "arqs/100mil.txt";
        ARV_RB_Busca(Arvore_RB, PATH);
        PATH = "arqs/300mil.txt";
        ARV_RB_Busca(Arvore_RB, PATH);
        PATH = "arqs/500mil.txt";
        ARV_RB_Busca(Arvore_RB, PATH);
        PATH = "arqs/1mi.txt";
        ARV_RB_Busca(Arvore_RB, PATH);
    clock_gettime(CLOCK_REALTIME, &end);

    // time_spent = fim - início
    time_spent = (end.tv_sec - start.tv_sec) +
                (end.tv_nsec - start.tv_nsec) / BILLION;
 
    printf("|----[TEMPO TOTAL: %f segundos]----|\n", time_spent);
}



//========================FIM DAS DOS CALCULOS DE TEMPO EM BUSCA==================================//

#endif