#ifndef ARVOREBIN //Verificacao se biblioteca foi carregada
#define ARVOREBIN

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aluno.c"

typedef struct No{
    int chave;
    Alunos *aluno;
    struct No *esq;
    struct No *dir;
} ArvBin;

ArvBin* buscaArv_BI(ArvBin *no, int chave){
    while (no != NULL){
        if (no->chave == chave)
            return no;
        else if (no->chave > chave)
            no = no->esq;
        else
            no = no->dir;
    }
    return NULL;
}

ArvBin* criaNo(ArvBin *no, int chave, Alunos *al){
    no = (ArvBin *)malloc(sizeof(ArvBin));
    no->chave = chave;
    no->aluno = al;
    no->esq = NULL;
    no->dir = NULL;

    return no;
}

ArvBin* insereArvBin(ArvBin *no, int chave, Alunos *a){

    if (no == NULL)
        no = criaNo(no, chave, a);
    else if (chave < (no->chave))
        no->esq = insereArvBin(no->esq, chave, a);
    else if (chave > (no->chave))
        no->dir = insereArvBin(no->dir, chave, a);
    else
    {
        printf("inserçao invalida! ");
        exit(1);
    }
    return no;
}

int alturaBin(ArvBin *no){
    if (no == NULL){
        return -1;
    }
    else{
        int esq = alturaBin(no->esq);
        int dir = alturaBin(no->dir);
        if (esq > dir){
            return esq + 1;
        }
        else{
            return dir + 1;
        }
    } 
}

void imprimeBin(ArvBin *no){
    if(no != NULL){
        imprimeBin(no->esq);
        printf("%d %s %s %s %lf %lf %lf %lf %lf\n", 
        no->chave, 
        no->aluno->estado, 
        no->aluno->municipio, 
        no->aluno->rede,
        no->aluno->media_ciencias_natureza,
        no->aluno->media_ciencias_humanas,
        no->aluno->media_linguagem,
        no->aluno->media_matematica,
        no->aluno->media_redacao);
        imprimeBin(no->dir);
    }
}

#endif
