/*
UFMT - Ciencia da Computacao

Autor: Anthony Muniz Prado de Oliveira

Implementacao Estrutura de Dados em Arvore Binaria

*/

#ifndef ARVBIN_C //Verificacao se biblioteca foi carregada
#define ARVBIN_C

#include <stdio.h>
#include <stdlib.h>

struct est_arv_bin{
    struct est_arv_bin *esq;
    struct est_arv_bin *dir;
    int valor;
};
typedef struct est_arv_bin tipo_arv_bin;

//Prototipos
tipo_arv_bin *alocaNovoNo(int vl);
void insereArvBin(tipo_arv_bin **arv, int valor);
void buscaArvBin(tipo_arv_bin *arv, int vl);
int conta_NosArvBin(tipo_arv_bin *arv);
int contaNiveis(tipo_arv_bin *arv);
void imprimeNivel(tipo_arv_bin *arv, int nv_desejado, int nv_atual);
void imprimeNosFolha(tipo_arv_bin *arv);
void percursoPreOrdem(tipo_arv_bin *arv);
void percursoPosOrdem(tipo_arv_bin *arv);
void percursoOrdem(tipo_arv_bin *arv);


//Funcao que aloca novo no na estrutura arvore
tipo_arv_bin *alocaNovoNo(int vl){
    tipo_arv_bin *novo_no;
    novo_no = (tipo_arv_bin*) malloc(sizeof(tipo_arv_bin));
    novo_no-> valor = vl;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return novo_no;
}
//Funcao que insere um valor na arvore binaria
void insereArvBin(tipo_arv_bin **arv, int valor){
    if((*arv) == NULL){

        (*arv) = alocaNovoNo(valor);

    }else{

        if (valor < (*arv)->valor){
            insereArvBin( &((*arv)->esq), valor);
        }else{
            insereArvBin( &((*arv)->dir), valor);
        }

    }
}

// Funcao que conta o numero de nos arvore binaria
int conta_NosArvBin(tipo_arv_bin *arv){
    int esq, dir;
    if (arv != NULL){
        esq = conta_NosArvBin(arv->esq);
        dir = conta_NosArvBin(arv->dir);
        return 1 + esq + dir;
        

    }else{
        return 0;
    }
    
}

// Funcao que conta o numero de niveis na arvore binaria
int Altura_arv(tipo_arv_bin *arv){
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

int contaNiveis(tipo_arv_bin *arv){
    int esq, dir;
    if (arv != NULL){
        esq = Altura_arv(arv->esq);
        dir = Altura_arv(arv->dir);
        if (esq > dir){
            return esq;
        }else{
          return dir;  
        } 

    }else{
        return 0;
    }
    
}

//Funcao auxiliares do remore valor
//encontra o menor no filho
int menorNo(tipo_arv_bin *no){
    if(no != NULL){
        if(no->esq !=NULL){
            return menorNo(no->esq);
        }
        return no->valor;
    }
    return -1;
}

//verifica se é um no folha
int se_folha(tipo_arv_bin *arv){
    return arv->esq == NULL && arv->dir == NULL;
}

//Funcao que remove um valor dado como parametro
int remove_valorArvBin(tipo_arv_bin **arv, int vl){
    int aux;
    tipo_arv_bin *filho;
    if (*arv != NULL){
        if (vl < (*arv)->valor){
            return remove_valorArvBin(&(*arv)->esq, vl);
        }else if (vl > (*arv)->valor){
            return remove_valorArvBin(&(*arv)->dir, vl);
        }else{
            //encontrou valor
            if(se_folha(*arv)){
                aux = (*arv)->valor;
                free(*arv);
                *arv = NULL;
                return aux;
            }else if ((*arv)->esq != NULL && (*arv)->dir != NULL){
                // o valor esta em um no que tem 2 filhos
                int menor_valor = menorNo((*arv)->dir);
                aux = (*arv)->valor;
                // valor do no é sobrescrito por seu menor filho
                (*arv)->valor = menor_valor;

                remove_valorArvBin(&(*arv)->dir,menor_valor);

            }else{
                //o valor está em um no com apenas 1 filho
                if((*arv)->esq != NULL){
                    filho = (*arv)->esq;
                }else{
                    filho = (*arv)->dir;
                }
                aux = (*arv)->valor;
                free(*arv);
                (*arv) = filho;
                return aux;
            }
        }
    }else{
        printf("\nValor não encontrado na arvore binaria\n");
        return -1;    
    }
}




//Funcao que identifica e imprime os Nos folha
void imprimeNosFolha(tipo_arv_bin *arv){
    if (arv != NULL){
        if (arv->esq == NULL && arv->dir == NULL){
             printf("%d ", arv->valor);
             
        }else{
            imprimeNosFolha(arv->esq);
            imprimeNosFolha(arv->dir);   
        }   
    }
}

//Funcao que imprime todos os valores de determinado nivel da arvore
void imprimeNivel(tipo_arv_bin *arv, int nv_desejado, int nv_atual){
    if (arv != NULL){
        if (nv_desejado <= nv_atual){
            printf("%d ", arv->valor);
        }else{
            nv_atual++;
            imprimeNivel(arv->esq, nv_desejado, nv_atual);
            imprimeNivel(arv->dir, nv_desejado, nv_atual);
        }
    }
}

//Funcao que Busca um valor na arvore
void buscaArvBin(tipo_arv_bin *arv, int vl){
    if(arv != NULL){
        if (arv-> valor == vl){
            printf("Valor %d encontrado na Arvore binaria", arv->valor);
        }else if (vl > arv->valor ){
            buscaArvBin(arv->dir, vl);
        }else if (vl < arv->valor){
            buscaArvBin(arv->esq, vl);
        }
    }
}

//Funcao que percore em Pre-Ordem
void percursoPreOrdem(tipo_arv_bin *arv){
    if(arv != NULL){
        printf("%d ", arv->valor);
        percursoPreOrdem(arv->esq);
        percursoPreOrdem(arv->dir);
    }
}

//Funcao que percore em Pos-Ordem
void percursoPosOrdem(tipo_arv_bin *arv){
    if(arv != NULL){
        percursoPosOrdem(arv->esq);
        percursoPosOrdem(arv->dir);
        printf("%d ", arv->valor);    
    }
}

//Funcao que percore em Ordem
void percursoOrdem(tipo_arv_bin *arv){
    if(arv != NULL){
        percursoOrdem(arv->esq);
        printf("%d ", arv->valor);   
        percursoOrdem(arv->dir);
    }
}


#endif