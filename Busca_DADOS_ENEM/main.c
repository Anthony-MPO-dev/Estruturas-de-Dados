#include <stdio.h>
#include <stdlib.h>


//link das arvore
#include "ArvoreBin.c"
#include "ArvoreAVL.c"
#include "ArvoreRB.c"

//link para função de inserção e calculo do tempo 
#include "insercao_time.c"






int main(){
    int tam = 30228;
    Alunos *v[tam];
    int rtRB;
    int rtAVL; 
    rtAVL=0;
    rtRB=0; 

    /*
        Conjuntos Aleatorios de Alunos
        
        1   100
        2	1000
        3	10.000
        5	50.000
        6	100.000
        7	300.000
        8	500.000
        9	1.000.000

    */

    
    //cria variavel do tipo file
    FILE *file;


    //file recebe o arquivo e retira os valores
    file = fopen("DadosEnem.txt", "r");
    
    int i = 0;
    while(!feof(file)){

        //cria um ponterio tipo aluno e aloca a memoria 
        v[i] = (Alunos *)malloc(sizeof(Alunos));

        //scaneia o arquivo e retira os valores que seram utilizados para construção das arvores
        fscanf(file, "%d %s %s %s %lf %lf %lf %lf %lf", 
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


    //inicializa as arvores
    ArvBin *Arvore_Binaria = NULL;
    ArvAVL *Arvore_AVL = NULL;
    ArvRB *Arvore_RB = NULL;
 
    //Insere os valores nas Arvores e retorna o tempo
    double tempo_decorrido;                

    Arvore_Binaria = tempo_e_Insercao_ARVBinaria(Arvore_Binaria, v, tam);
    printf("\n\n");
    Arvore_AVL = tempo_e_Insercao_AVL(Arvore_AVL, v, tam, &rtAVL);
    printf("Nº de Rotações %d\n\n", rtAVL);
    Arvore_RB= tempo_e_Insercao_RB(Arvore_RB, v, tam, &rtRB);
    printf("Nº de Rotações %d\n\n", rtRB);

    
    

    ARVBinaria_Conjutos_de_Busca(Arvore_Binaria);
    ARV_AVL_Conjutos_de_Busca(Arvore_AVL);
    ARV_RB_Conjutos_de_Busca(Arvore_RB);

    fclose(file);//fecha o arquivo de leitura dos dados



    //imprimeBin(Arvore_Binaria);
    //imprimeAVL(Arvore_AVL);
    //imprimeRB(Arvore_RB);

    return 0;
}
