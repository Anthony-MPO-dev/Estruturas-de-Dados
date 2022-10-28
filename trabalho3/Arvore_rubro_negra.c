#ifndef ARVBIN_RUBRO_NEGRA //Verificacao se biblioteca foi carregada
#define ARVBIN_RUBRO_NEGRA

#include <stdio.h>
#include <stdlib.h>

typedef struct ArvoreRB{
	struct ArvoreRB *esq, *dir;
	int cor, valor;
	// cor 1 vermelho
	// cor -1 preto
}tipoArvRB;

void insereArvRB(tipoArvRB **node, tipoArvRB **pai, int valor, int *contador);
int corArvRB(tipoArvRB *node);
void rotacionaDirRB(tipoArvRB **pai);
void rotacionaEsqRB(tipoArvRB **pai);
void rotacionaEsqDirRB(tipoArvRB **vo);
void rotacionaDirEsqRB(tipoArvRB **vo);
void imprime(tipoArvRB* no, int tab);
int alturaRaizRB(tipoArvRB* node);
int alturaRB(tipoArvRB* node);
/*
int main(int argc, char **argv){
	tipoArvRB *raiz = NULL;
	int valor, contador = 0;

    insereArvRB(&raiz, NULL, 50, &contador);
    insereArvRB(&raiz, NULL, 60, &contador);
	insereArvRB(&raiz, NULL, 55, &contador);

    imprime(raiz, 0);
	
	printf("contador: %d", contador);
}
*/

void insereArvRB(tipoArvRB **node, tipoArvRB **pai, int valor, int *contador){
	if (*node == NULL){
		*node = malloc(sizeof(tipoArvRB));
		(*node)->valor = valor;
		(*node)->esq = NULL;
		(*node)->dir = NULL;
		(*node)->cor = 1;
	} 
	else{
		if (valor < (*node)->valor){
			insereArvRB(&((*node)->esq), node, valor, contador);
			if (((*node)->esq->cor == 1) && ((*node)->cor) == 1){ //se as cores estao em conflito
				if (valor < (*pai)->valor){
					if(corArvRB((*pai)->dir) == 1){ // verifico se o tio tem a mesma cor
						(*pai)->cor *= -1;
						(*pai)->dir->cor *= -1;
						(*node)->cor *= -1;
					}
					else{  // rotaciona
						rotacionaDirRB(pai);
						*contador = *contador + 1;
					}
				}
				else{
					if (corArvRB((*pai)->esq) == 1){ //verifico se o tio tem a mesma cor
						(*pai)->cor *= -1;
						(*pai)->esq->cor *= -1;
						(*node)->cor *= -1;
					}
					else{ // rotaciona
						rotacionaDirEsqRB(pai);
						*contador = *contador + 1;
					}
				}	
			}
		} 
		else{
			insereArvRB(&((*node)->dir), node, valor, contador);
			if (((*node)->dir->cor == 1) && ((*node)->cor) == 1){
				if (valor < (*pai)->valor){
					if (corArvRB((*pai)->dir) == 1){
						(*pai)->cor *= -1;
						(*pai)->dir->cor *= -1;
						(*node)->cor *= -1;
					} 
					else{
						rotacionaEsqDirRB(pai);
						*contador = *contador + 1;
					}
				}
				else{
					if (corArvRB((*pai)->esq) == 1){
					(*pai)->cor *= -1;
					(*pai)->esq->cor *= -1;
					(*node)->cor *= -1;
					} 
					else{//rotaciona
						rotacionaEsqRB(pai);
						*contador = *contador + 1;
					}
				}
			}
		}
	}
	if (pai == NULL){
		(*node)->cor = -1;
	}
}

int corArvRB(tipoArvRB *node){
	if (node == NULL)
		return -1;
	else
		return node->cor; 
}

void rotacionaDirRB(tipoArvRB** pai){
	tipoArvRB *filho;
	(*pai)->cor = 1;
	filho = (*pai)->esq;
	(*pai)->esq = filho->dir;
	filho->dir = (*pai);
	(*pai) = filho;
	(*pai)->cor = -1;
    //printf("[RSD]");
}

void rotacionaEsqRB(tipoArvRB** pai){
	tipoArvRB *filho;
	(*pai)->cor = 1;
	filho = (*pai)->dir;
	(*pai)->dir = filho->esq;
	filho->esq = (*pai);
	(*pai) = filho;
	(*pai)->cor = -1;
    //printf("[RSE]");
}

void rotacionaEsqDirRB(tipoArvRB **vo){
	tipoArvRB *filho, *neto;

	filho = (*vo)->esq;
	neto = filho->dir;

	(*vo)->esq = neto->dir;
	filho->dir = neto->esq;
	neto->dir = (*vo);
	neto->esq = filho;
	(*vo)->cor = 1;
	neto->cor = -1;

	(*vo) = neto;
    //printf("[R-ED]");
}

void rotacionaDirEsqRB(tipoArvRB **vo){
	tipoArvRB *filho, *neto;

	filho = (*vo)->dir;
	neto = filho->esq;

	(*vo)->dir = neto->esq;
	filho->esq = neto->dir;
	neto->esq = (*vo);
	neto->dir = filho;
	neto->cor = -1;
	(*vo)->cor = 1;

	*vo = neto;
    //printf("[R-DE]");
}

void imprime(tipoArvRB* no, int tab){
    if(no != NULL){
        tab += 10;
        imprime(no->dir, tab);
        printf("\n");
        for (int i = 5; i < tab; i++)
            printf(" ");
        if (no-> cor == -1)
            printf("preto (%d)\n", no->valor);
        else
            printf("red (%d)\n", no->valor);

        imprime(no->esq, tab);
    }
}

int alturaRaizRB(tipoArvRB* node){
	if (node == NULL)
		return 0;
	else{
		int esq, dir;
		esq = alturaRB(node->esq);
		dir = alturaRB(node->dir);
		if (esq > dir)
			return esq;
		else
			return dir;
	}
}

int alturaRB(tipoArvRB* node){
	if (node == NULL)
		return 0;
	else{
		int esq, dir;
		esq = alturaRB(node->esq);
		dir = alturaRB(node->dir);
		if (esq > dir)
			return 1 + esq;
		else
			return 1 + dir;
	}
}

int Altura_arv_RB(tipoArvRB *arv){
    int esq, dir;
    if (arv != NULL){
        esq = Altura_arv(arv->esq);
        dir = Altura_arv(arv->dir);
        if (esq > dir){
            return 1 + esq;
        }else{
          return 1 + dir;  
        } 

    }else{
        return 0;
    }
    
}

#endif