#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//inclusao do tipo Aluno
#include "aluno.c" 

typedef struct sNoA{
    int chave;
    char *nome;
    int n1;
    int n2;
    int n3;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

TNoA *criaNo(int ch, char *nomes, int nota1, int nota2, int nota3){
    TNoA *novo;
    novo = (TNoA *) malloc(sizeof(TNoA));
    novo-> chave = ch;
    novo-> nome = nomes;
    novo-> n1 = nota1;
    novo-> n2 = nota2;
    novo-> n3 = nota3;
    novo-> esq = NULL;
    novo-> dir = NULL;
    return novo;
}

TNoA *insere ( TNoA *no , int chave, char *nomes, int nota1, int nota2, int nota3) {
    if ( no == NULL ) {
        no = ( TNoA * ) malloc ( sizeof ( TNoA ) ) ;
        no-> chave = chave ;
        no-> nome = nomes;
        no-> n1 = nota1;
        no-> n2 = nota2;
        no-> n3 = nota3;
        no-> esq = NULL ;
        no-> dir = NULL ;
    } 
    else if(chave < ( no -> chave )){
        no -> esq = insere(no->esq, chave, nomes, nota1, nota2, nota3);
    }
    else if ( chave > ( no -> chave )){
        no -> dir = (insere(no->dir, chave, nomes, nota1, nota2, nota3));
    }
    else{
        printf("Inserção inválida! "); // chave já existe
        exit(1);
    }
    return no;
}

TNoA *criaArvoreBalanceada( TNoA *raiz , Alunos v [ ] , int inicio , int fim ) {
   if ( inicio <= fim ) {
        int meio = ( inicio + fim ) / 2 ;
        raiz = insere( raiz, v[meio].matricula, v[meio].nomes, v[meio].n1, v[meio].n2, v[meio].n3);
       // constroi subárvores esquerda e direita
        raiz->esq = criaArvoreBalanceada( raiz->esq , v , inicio, meio-1 ) ;                    
        raiz->dir = criaArvoreBalanceada( raiz->dir , v , meio + 1 , fim ) ;
        
        return raiz;
   }
    return NULL;
}

//Imprime em ordem simetrica
void simetrica ( TNoA *a ){
     if ( a != NULL ){
          simetrica ( a-> esq ) ;
          printf ( " %d \n " , a->chave ) ;
          simetrica ( a-> dir ) ;
     }
}

//imprime em produfundidade
void profundidade(TNoA* a){
    if (a!= NULL)
    {
        printf("%d\n",a->chave);
        profundidade(a->esq);
        profundidade(a->dir);
    }
}

//imprime em Pos ordem
void posOrdem(TNoA* a){
    
    if (a!= NULL)
    {
        posOrdem(a->esq);
        posOrdem(a->dir);
        printf("%d\n",a->chave);
    }
}

void troca(TNoA *no1, TNoA *no2){
    no1-> chave = no2->chave;
    no1-> nome= no2->nome;
    no1-> n1 = no2->n1;
    no1-> n2 = no2->n2;
    no1-> n3 = no2->n3;
}

TNoA *exclui(TNoA *raiz, int chave){
    TNoA *anterior = NULL;
    anterior = raiz;
    //percorre a arvore e para antes do nó ser nulo
    while ( raiz != NULL ){       
        //Se no contiver a chave procurada
        if (chave == raiz->chave){
            //cria um no auxiliar para armazenar o nó atual
            TNoA *aux; 
            aux = raiz;
            //se o no a ser removido contiver dois filhos
            if((raiz->esq != NULL) && (raiz->dir != NULL)){
                //encontra o maior no filho da sub arvore a esquerda que tenha um filho a direita
                raiz = raiz->esq;
                //armazena no anterior do maior filho da sub arvore a esquerda
                TNoA *anterior_sub; 
                anterior_sub = raiz;
                while(raiz->dir != NULL){
                    anterior_sub = raiz;
                    raiz = raiz->dir;
                }
                //apos encontrar o maior filho a direita da sub arvore a esquerda 
                //vamos agora verificar se ele possui algum filho a esquerda ou seja menor que ele
                if(raiz->esq != NULL){
                    //armazena o maior no da sub-arv esq
                    TNoA *aux3 = NULL, *aux2 = NULL;
                    aux2 = raiz->dir;
                    //coloca o FILHO a esquerda dele como maior nó atual da sub-arv 
                    raiz->dir = raiz->dir->esq;
                    //armazena os dados do no excluido
                    troca(aux3, aux);
                    aux3->chave = aux->chave;
                    //e coloca o maior dir no ligar do nó excluido
                    aux->chave = aux2->chave;
                    //libera o antigo nó antigo dele
                    free(aux2);
                    //retorna o nó excluido que posteriror mente sera liberado                   
                    return aux3;
                }else{
                    //se o nó for a raiz da arv
                    if(anterior == aux){
                        anterior = criaNo(anterior->chave, anterior->nome, anterior-> n1, anterior-> n2, anterior-> n3);

                        //passa o valor do no pai para o maior filho a direita da sub arvore a esquerda
                        aux->chave = raiz->chave; 
                        //libera atual nó trocado e define para NULL
                        free(anterior_sub->dir);
                        anterior_sub->dir=NULL;
                        
                        return anterior;


                    //no anterior ao excluido recebe o no
                    }else{
                        TNoA *aux2;
                        if(chave < aux->chave){
                            aux2 = criaNo(aux->chave, aux->nome, aux-> n1, aux-> n2, aux-> n3); 
                            aux2->esq = aux->esq;
                            aux2->dir = aux->dir;
                            anterior->esq->chave = raiz->chave;
                            free(anterior_sub->esq);
                            anterior_sub->esq = NULL;
                            return aux2;
                        }else{
                            aux2 = criaNo(aux->chave, aux->nome, aux-> n1, aux-> n2, aux-> n3); 
                            aux2->esq = aux->esq;
                            aux2->dir = aux->dir;
                            anterior->dir->chave = raiz->chave;
                            free(anterior_sub->dir);
                            anterior_sub->dir = NULL;
                            return aux2;
                        }
                     }
                }

            //Se no escolhido tiver filho esquerdo    
            }else if (raiz->esq != NULL){
                //ele vai para o lugar do excluido
                raiz->chave = raiz->esq->chave;
                //libera agora o no trocado
                free(raiz->esq);
                //define ele para NULL
                raiz->esq = NULL;              
                //retorna nó excluido
                return aux;
            }else if(raiz->dir != NULL){
                //ele vai para o lugar do excluido
                raiz->chave = raiz->dir->chave;
                //libera agora o no trocado
                free(raiz->esq);
                //define ele para NULL
                raiz->dir = NULL;              
                //retorna nó excluido
                return aux;
            }else{
                //só retorna o valor para exclusão
                if(chave < raiz->chave){
                    anterior->dir = NULL;
                    return aux;
                }else{
                    anterior->esq = NULL;
                    return aux;
                }
            }     
        
        //Se no atual for menor que o no procurado
        }else if(chave < raiz->chave){
            anterior = raiz;
            //caminha para filho a esquerda
            raiz = raiz->esq;
        //Se no for maior que a chave procurada
        }else {
            anterior = raiz;
            //caminha para o filho a direita
            raiz = raiz->dir;
        }
     }
     //caso chave não encontrada na arv-b
     printf("ERRO: chave não contida na arvore");
     return NULL;
}


void imprime(TNoA *no, int tab){
    if(no != NULL){
        tab +=10;
        imprime(no->dir, tab);
        printf("\n");
        for(int i =10; i<tab; i++)
            printf(" ");
        
        char *str = no->nome;
        printf("%d (%s)-(%d, %d, %d)\n", no->chave, str, no->n1, no->n2, no->n3);
        imprime(no->esq, tab +2);
    }
}


//Função para buscar um aluno pelo numero de matricula na arvore
TNoA *busca(TNoA *no, int matricula){
    if(no == NULL){
        TNoA *aux = criaNo(NULL,NULL,NULL,NULL,NULL);
        printf("ERRO INVALID KEY: No não existe na arvore de busca");
        return aux;
    }
    if(matricula == no->chave){
        return no;
    }else if( matricula < no->chave){
        busca(no->esq, matricula);
    }else if( matricula > no->chave){
        busca(no->dir, matricula);
    }else{
        printf("ERRO INVALID KEY");
        exit(1);
    }
}

/*
     Função para calcular a altura de uma árvore binária
*/
int altura(TNoA *raiz, int *vet[]){
    if(raiz == NULL){
        return -1;
    }
    else{
        //vetor que armazena - altura da arvore -> total/esq/dir
        int v[3] = {0,0,0};
        v[1] = altura(raiz->esq, vet);
        v[2] = altura(raiz->dir, vet);
        
        //se altura esq > altura direita
        if(v[1] > v[2]){
            //altura total = altura->esq + 1(raiz)
            v[0] = v[1] + 1;
            vet[1] = v[1];
            vet[2] = v[2];
            return v[0];
        }else{
            //altura total = altura->dir + 1(raiz)
            v[0] = v[2] + 1;
            vet[1] = v[1];
            vet[2] = v[2];
            return v[0];
        }
    }
}