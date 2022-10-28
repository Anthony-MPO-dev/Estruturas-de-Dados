/*
UFMT - Ciencia da Computacao
Autor: Anthony Muniz Prado de Oliveira / Vinicius Spanhol Ferrari
Funcao Principal
*/

//Inclusao de bibliotecas
#include <stdio.h>
#include <stdlib.h>

//inclusao da pasta do programa
#include "Arvore_Bin.c" 
#include "Arvore_AVL.c" 
#include "Arvore_rubro_negra.c" 

int main(){

    //arv_bin
    tipo_arv_bin *arvore_bin;
    tipo_arv_bin *arvore_bin2;
    tipo_arv_bin *arvore_bin3;
    tipo_arv_bin *arvore_bin4;
    tipo_arv_bin *arvore_bin5;
    tipo_arv_bin *arvore_bin6;
    arvore_bin = NULL;
    arvore_bin2 = NULL;
    arvore_bin3 = NULL;
    arvore_bin4 = NULL;
    arvore_bin5 = NULL;
    arvore_bin6 = NULL;

    //arv_AVL
    TNoA *arvore_AVL;
    TNoA *arvore_AVL2;
    TNoA *arvore_AVL3;
    TNoA *arvore_AVL4;
    TNoA *arvore_AVL5;
    TNoA *arvore_AVL6;
    arvore_AVL = NULL;
    arvore_AVL2 = NULL;
    arvore_AVL3 = NULL;
    arvore_AVL4 = NULL;
    arvore_AVL5 = NULL;
    arvore_AVL6 = NULL;
    int num, num2, num3, num4, num5, num6;
   
    //arv_rubro_negra
    tipoArvRB *raiz = NULL;
    tipoArvRB *raiz2 = NULL;
    tipoArvRB *raiz3 = NULL;
    tipoArvRB *raiz4 = NULL;
    tipoArvRB *raiz5 = NULL;
    tipoArvRB *raiz6 = NULL;
	int valor, contador = 0;
    int valor2, contador2 = 0;
    int valor3, contador3 = 0;
    int valor4, contador4 = 0;
    int valor5, contador5 = 0;
    int valor6, contador6 = 0;

    int chave;

    FILE *file, *file2, *file3, *file4, *file5, *file6;

    file = fopen("saida_5000_01.txt", "r");

    if(file != NULL){
        while (fscanf(file, "%d", &chave) != EOF){
            //printf("%d\n", chave);
            insereArvBin(&arvore_bin, chave);
            arvore_AVL = insere_AVL(arvore_AVL, chave);
            num = rotations();
            insereArvRB(&raiz, NULL, chave, &contador);

        }   
    }
    restart();
    fclose(file);

    file2 = fopen("saida_5000_02.txt", "r");

    if(file2 != NULL){
        while (fscanf(file2, "%d", &chave) != EOF){
            //printf("%d\n", chave);
            insereArvBin(&arvore_bin2, chave);
            arvore_AVL2 = insere_AVL(arvore_AVL2, chave);
            num2 = rotations();
            insereArvRB(&raiz2, NULL, chave, &contador2);

        }   
    }
    restart();
    fclose(file2);

    file3 = fopen("saida_5000_03.txt", "r");

    if(file3 != NULL){
        while (fscanf(file3, "%d", &chave) != EOF){
            //printf("%d\n", chave);
            insereArvBin(&arvore_bin3, chave);
            arvore_AVL3 = insere_AVL(arvore_AVL3, chave);
            num3 = rotations();
            insereArvRB(&raiz3, NULL, chave, &contador3);

        }   
    }
    restart();
    fclose(file3);

    file4 = fopen("saida_20000_01.txt", "r");

    if(file4 != NULL){
        while (fscanf(file4, "%d", &chave) != EOF){
            //printf("%d\n", chave);
            insereArvBin(&arvore_bin4, chave);
            arvore_AVL4 = insere_AVL(arvore_AVL4, chave);
            num4 = rotations();
            insereArvRB(&raiz4, NULL, chave, &contador4);

        }   
    }
    restart();
    fclose(file4);

    file5 = fopen("saida_20000_02.txt", "r");

    if(file5 != NULL){
        while (fscanf(file5, "%d", &chave) != EOF){
            //printf("%d\n", chave);
            insereArvBin(&arvore_bin5, chave);
            arvore_AVL5 = insere_AVL(arvore_AVL5, chave);
            num5 = rotations();
            insereArvRB(&raiz5, NULL, chave, &contador5);

        }   
    }
    restart();
    fclose(file5);

    file6 = fopen("saida_20000_03.txt", "r");

    if(file6 != NULL){
        while (fscanf(file6, "%d", &chave) != EOF){
            //printf("%d\n", chave);
            insereArvBin(&arvore_bin6, chave);
            arvore_AVL6 = insere_AVL(arvore_AVL6, chave);
            num6 = rotations();
            insereArvRB(&raiz6, NULL, chave, &contador6);

        }   
    }
    restart();
    fclose(file6);

	printf("\nArvore Rubro-Negra:");
	printf("\nNumero de rotacoes arquivo 1: %d", contador);
    printf("\nNumero de rotacoes arquivo 2: %d", contador2);
    printf("\nNumero de rotacoes arquivo 3: %d", contador3);
    printf("\nNumero de rotacoes arquivo 4: %d", contador4);
    printf("\nNumero de rotacoes arquivo 5: %d", contador5);
    printf("\nNumero de rotacoes arquivo 6: %d", contador6);

    printf("\n\nArvore AVL:");
	printf("\nNumero de rotacoes arquivo 1: %d", num);
    printf("\nNumero de rotacoes arquivo 2: %d", num2);
    printf("\nNumero de rotacoes arquivo 3: %d", num3);
    printf("\nNumero de rotacoes arquivo 4: %d", num4);
    printf("\nNumero de rotacoes arquivo 5: %d", num5);
    printf("\nNumero de rotacoes arquivo 6: %d", num6);

    double AVL_media_alturas_5000 = 0.0;
    double AVL_media_alturas_20000 = 0.0;
    double BIN_media_alturas_5000= 0.0;
    double BIN_media_alturas_20000 = 0.0;
    double RB_media_alturas_5000 = 0.0;
    double RB_media_alturas_20000 = 0.0;
    

    printf("\n\nAltura das arvores arq_01:\n");
    int niveis = Altura_arv(arvore_bin);
    printf("A arvore bin tem %d ", niveis);
    printf("\n");
    BIN_media_alturas_5000 += niveis;

    niveis = Altura_AVL(arvore_AVL);
    printf("A arvore AVL tem %d ", niveis);
    printf("\n");
    AVL_media_alturas_5000 += niveis;

    niveis = Altura_arv_RB(raiz);
    printf("A arvore_RB tem %d ", niveis);
    printf("\n");
    RB_media_alturas_5000 += niveis;

    printf("\nAltura das arvores arq_02:\n");
    niveis = Altura_arv(arvore_bin2);
    printf("A arvore bin tem %d ", niveis);
    printf("\n");
    BIN_media_alturas_5000 += niveis;

    niveis = Altura_AVL(arvore_AVL2);
    printf("A arvore AVL tem %d ", niveis);
    printf("\n");
    AVL_media_alturas_5000 += niveis;

    niveis = Altura_arv_RB(raiz2);
    printf("A arvore_RB tem %d ", niveis);
    printf("\n");
    RB_media_alturas_5000 += niveis;
    

    printf("\nAltura das arvores arq_03:\n");
    niveis = Altura_arv(arvore_bin3);
    printf("A arvore bin tem %d ", niveis);
    printf("\n");
    BIN_media_alturas_5000 += niveis;

    niveis = Altura_AVL(arvore_AVL3);
    printf("A arvore AVL tem %d ", niveis);
    printf("\n");
    AVL_media_alturas_5000 += niveis;

    niveis = Altura_arv_RB(raiz3);
    printf("A arvore_RB tem %d ", niveis);
    printf("\n");
    RB_media_alturas_5000 += niveis;

    printf("\nAltura das arvores arq_04:\n");
    niveis = Altura_arv(arvore_bin4);
    printf("A arvore bin tem %d ", niveis);
    printf("\n");
    BIN_media_alturas_20000 += niveis;
    
    niveis = Altura_AVL(arvore_AVL4);
    printf("A arvore AVL tem %d ", niveis);
    printf("\n");
    AVL_media_alturas_20000 += niveis;

    niveis = Altura_arv_RB(raiz4);
    printf("A arvore_RB tem %d ", niveis);
    printf("\n");
    RB_media_alturas_20000 += niveis;

    printf("\nAltura das arvores arq_05:\n");
    niveis = Altura_arv(arvore_bin5);
    printf("A arvore bin tem %d ", niveis);
    printf("\n");
    BIN_media_alturas_20000 += niveis;

    niveis = Altura_AVL(arvore_AVL5);
    printf("A arvore AVL tem %d ", niveis);
    printf("\n");
    AVL_media_alturas_20000 += niveis;

    niveis = Altura_arv_RB(raiz5);
    printf("A arvore_RB tem %d ", niveis);
    printf("\n");
    RB_media_alturas_20000 += niveis;

    printf("\nAltura das arvores arq_06:\n");
    niveis = Altura_arv(arvore_bin6);
    printf("A arvore bin tem %d ", niveis);
    printf("\n");
    BIN_media_alturas_20000 += niveis;

    niveis = Altura_AVL(arvore_AVL6); 
    printf("A arvore AVL tem %d ", niveis);
    printf("\n");
    AVL_media_alturas_20000 += niveis;

    niveis = Altura_arv_RB(raiz6);
    printf("A arvore_RB tem %d ", niveis);
    printf("\n");
    RB_media_alturas_20000 += niveis;

    AVL_media_alturas_5000 = AVL_media_alturas_5000/3;
    AVL_media_alturas_20000 = AVL_media_alturas_20000/3;
    BIN_media_alturas_5000 = BIN_media_alturas_5000/3;
    BIN_media_alturas_20000 = BIN_media_alturas_20000/3;
    RB_media_alturas_5000 = RB_media_alturas_5000/3;
    RB_media_alturas_20000 = RB_media_alturas_20000/3;

    double media = (num+num2+num3)/3;


    printf("\nMedia de rotacoes ARV AVL\n");
    printf( "5000 VALORES: %lf\n", media);
    media = (num4+num5+num6)/3;
    printf( "20000 VALORES: %lf\n", media);

    media = (contador+contador2+contador3)/3;
    printf("\nMedia de rotacoes ARV RB\n");
    printf( "5000 VALORES: %lf\n", media);
    media = (contador4+contador5+contador6)/3;
    printf( "20000 VALORES: %lf\n", media); 


    printf("\n\nMEDIAS DE ALTURA POR ARVORE:\n");

    printf("\nMedia de Altura ARV BIN\n");
    printf( "5000 VALORES: %lf\n", BIN_media_alturas_5000);
    printf( "20000 VALORES: %lf\n", BIN_media_alturas_20000);

    printf("\nMedia de Altura ARV AVL\n");
    printf( "5000 VALORES: %lf\n", AVL_media_alturas_5000);
    printf( "20000 VALORES: %lf\n", AVL_media_alturas_20000);

    printf("\nMedia de Altura ARV RB\n");
    printf( "5000 VALORES: %lf\n", RB_media_alturas_5000);
    printf( "20000 VALORES: %lf\n", RB_media_alturas_20000);

    //imprime(raiz6, 0);

    return 0;
}
