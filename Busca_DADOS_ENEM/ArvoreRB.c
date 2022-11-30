#ifndef ARVORERB //Verificacao se biblioteca foi carregada
#define ARVORERB

#include <stdio.h>
#include <stdlib.h>

#include "aluno.c"

#define RED 0
#define BLACK 1

typedef struct NoRB{
    int chave;
    int cor;
    Alunos *aluno;
    struct NoRB *esq;
    struct NoRB *dir;
    struct NoRB *pai;
} ArvRB;

int cor(ArvRB *no){
    if (no == NULL)
        return BLACK;
    else
        return no->cor;
}

ArvRB *rotacao_direitaRB(ArvRB *pt){
    ArvRB *ptu;
    ptu = pt->esq;

    //printf("RSD (%d)\n",pt->chave);

    pt->esq = ptu->dir;
    if (ptu->dir != NULL)
        ptu->dir->pai = pt;
    ptu->pai = pt->pai;

    if (pt->pai != NULL)
    {
        if (pt == ptu->pai->dir)
            pt->pai->dir = ptu;
        else
            pt->pai->esq = ptu;
    }
    ptu->dir = pt;
    pt->pai = ptu;
    pt = ptu;
    return pt;
}

ArvRB *rotacao_esquerdaRB(ArvRB *pt){
    
    ArvRB *ptu;
    ptu = pt->dir;
    //printf("RSE (%d)\n",pt->chave);

    pt->dir = ptu->esq;
    if (ptu->esq != NULL)
        ptu->esq->pai = pt;
    ptu->pai = pt->pai;

    if (pt->pai != NULL)
    {
        if (pt == ptu->pai->esq)
            pt->pai->esq = ptu;
        else
            pt->pai->dir = ptu;
    }
    ptu->esq = pt;
    pt->pai = ptu;
    pt = ptu;
    return pt;
}

ArvRB *insere_fixup(ArvRB *z, int *rt){
    ArvRB *y;
    while (cor(z->pai) == RED)
    {
        // Verifica se o pai de Z é filho a esquerda do avo de Z
        if (z->pai == z->pai->pai->esq)
        {
            // y recebe o tio de Z
            y = (z->pai)->pai->dir;

            // Se o tio de z for vermelho
            if (cor(y) == RED)
            {
                // caso 01
                //printf("CASO 1 (%d) \n",z->chave);
                z->pai->cor = BLACK;    // Pai de Z troca de vermelho para preto
                y->cor = BLACK;         // Tio de Z troca de vermelho para preto
                z->pai->pai->cor = RED; // Avo de Z troca de preto para vermeho
                z = z->pai->pai;        // Z passa a ser'' o AVO
            }
            else
            {
                // Verificando se Z é filho direita
                if (z == z->pai->dir)
                {
                    // caso 02
                    //printf("CASO 2 (%d) \n",z->chave);
                    z = z->pai;
                    z = rotacao_esquerdaRB(z);
                    *rt = *rt + 1;
                    z = z->esq;
                }
                else
                {
                    // caso 03
                    //printf("CASO 3 (%d) \n",z->chave);
                    z->pai->cor = BLACK;
                    z->pai->pai->cor = RED;
                    z = rotacao_direitaRB(z->pai->pai);
                    *rt = *rt + 1;
                    z = z->esq;
                }
            }
        }
        else
        {
            // se o pai é filho a direita
            // y recebe o tio de Z
            y = (z->pai)->pai->esq;

            // Se o tio de z for vermelho
            if (cor(y) == RED)
            {
                // caso 01
                //printf("CASO 1 (%d) \n",z->chave);
                z->pai->cor = BLACK;    // Pai de Z troca de vermelho para preto
                y->cor = BLACK;         // Tio de Z troca de vermelho para preto
                z->pai->pai->cor = RED; // Avo de Z troca de preto para vermeho
                z = z->pai->pai;        // Z passa a ser'' o AVO
            }
            else
            {
                // Verificando se Z é filho dir
                if (z == z->pai->dir)
                {
                    // caso 02
                    //printf("CASO 2 (%d) \n",z->chave);
                    z = z->pai;
                    z = rotacao_esquerdaRB(z);
                    *rt = *rt + 1;
                    z = z->esq;
                }
                else
                {
                    // caso 03
                    //printf("CASO 3 (%d) \n",z->chave);
                    z->pai->cor = BLACK;
                    z->pai->pai->cor = RED;
                    z = rotacao_esquerdaRB(z->pai->pai);
                    *rt = *rt + 1;
                    z = z->esq->dir;
                }
            }
        }
    }

    while (z->pai != NULL){
        z = z->pai;
    }
    z->cor = BLACK;
    return z;
}

ArvRB *insereArvRB(ArvRB *no, int chave, Alunos *aluno, int *rt){

    ArvRB *y = NULL;
    ArvRB *x = no;

    while (x != NULL)
    {
        y = x;
        if (chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }

    x = (ArvRB *)malloc(sizeof(ArvRB));
    x->chave = chave;
    x->aluno = aluno;
    x->esq = x->dir = NULL;
    x->cor = RED;
    x->pai = y;

    if (y == NULL)
        no = x;
    else{
        if (x->chave < y->chave)
            y->esq = x;
        else
            y->dir = x;
    }

    //printf("---------------FIXUP-BEGIN----------------");
    //no = imprime(no,0);
    x = insere_fixup(x, rt);
    //printf("---------------FIXUP-END----------------");
    return x;
}

int alturaRB(ArvRB *no){
    if (no == NULL){
        return -1;
    }
    else{
        int esq = alturaRB(no->esq);
        int dir = alturaRB(no->dir);
        if (esq > dir){
            return esq + 1;
        }
        else{
            return dir + 1;
        }
    } 
}

ArvRB* buscaArv_RB(ArvRB *no, int chave){
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

void imprimeRB(ArvRB *no){

    if(no != NULL){
        imprimeRB(no->esq);
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
        imprimeRB(no->dir);
    }
}

#endif