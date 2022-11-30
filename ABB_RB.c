#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct sNoA
{
    int chave;
    int cor;
    struct sNoA* esq;
    struct sNoA* dir;
    struct sNoa* pai;
   
};
typedef struct sNoA TNoA;

int cor(TNoA *no){
    if(no=NULL){
        return BLACK;
    }else{
        return no->cor; 
    }
}

TNoA* rotacao_esquerda(TNoA* pt){
    TNoA *ptu;
    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt = ptu;
    return pt;
}

TNoA* rotacao_direita(TNoA* pt){
    TNoA *ptu;
    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt = ptu;
    return pt;
}

TNoA* insere_fixup(TNoA *no){
    TNoA *tio;
    while (cor(no->pai) == RED)
    {   
        //verifica se o pai do nó é filho a esquerda de seu avo
        if( no->pai == ((no-> pai)-> pai)->esq){

            //se o pai é filho a direita
            //recebe o tio do no
            tio = ((no-> pai)-> pai)->dir;
            
            //se o tio do no for vermelho
            if(cor(tio) == RED){
                //caso 01 
                    no->pai->cor = BLACK;         //PAI do No troca de vermelho para preto
                    tio->cor = BLACK;           // Tio do No troca de vermelho para preto
                    no->pai->pai->cor = RED;  // Avo do No troca de preto para vermelho
                    no = no->pai->pai;      // No passa a ser o AVO 
            
            }else{// tio não for vermelho

                //Verificando se No é filho direito
                if(no == no->pai->dir){
                    //caso 2
                    no = no->pai;//recebe o no pai
                    no = rotacao_esquerda(no);// rotação a esquerda no pai que retorna o no
                    no = no->esq; // retorna para o pai
                }else{ // eh filho esquerdo
                    //caso 03
                    no-> pai-> cor = BLACK;
                    no-> pai-> pai-> cor = RED;
                    no = rotacao_direita(no->pai->pai);

                    no = no->esq;

                }
            }
        }else{
            //se o pai é filho a esq
            //recebe o tio do no
            tio = ((no-> pai)-> pai)->esq;
            
            //se o tio do no for vermelho
            if(cor(tio) == RED){
                //caso 01 
                    no->pai->cor = BLACK;         //PAI do No troca de vermelho para preto
                    tio->cor = BLACK;           // Tio do No troca de vermelho para preto
                    no->pai->pai->cor = RED;  // Avo do No troca de preto para vermelho
                    no = no->pai->pai;      // No passa a ser o AVO 
            
            }else{// tio não for vermelho
            
                //Verificando se No é filho direito
                if(no == no->pai->dir){
                    //caso 2
                    no = no->pai;//recebe o no pai
                    no = rotacao_esquerda(no);// rotação a esquerda no pai que retorna o no
                    no = no->esq; // retorna para o pai
                }else{ // eh filho esquerdo
                    //caso 03
                    no-> pai-> cor = BLACK;
                    no-> pai-> pai-> cor = RED;
                    no = rotacao_esquerda(no->pai->pai);

                    no = no->esq;

                }
            }
        }
    }
    return no;
    
}

TNoA *insere(TNoA *no, int chave, TNoA *pai){
    if(no == NULL){
        no = (TNoA *)malloc(sizeof(TNoA));
        no->chave = chave;
        no->esq = no->dir = NULL;
        no->cor = RED;
        no->pai = pai;

    }
    if(chave > no->chave){
        no = insere(no-> esq, chave, no);
    }
    else if(chave > no->chave){
        no = insere(no-> dir, chave, no);
    }
    else{
        printf("Inserção invalida");
        exit(1);
    }
    no = insere_fixup(no);
    return no;
}