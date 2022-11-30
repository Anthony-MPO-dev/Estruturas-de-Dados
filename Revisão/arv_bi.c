#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1

typedef struct sNoA{
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

TNoA *criaNo(int ch){
    TNoA *novo;
    novo = (TNoA *) malloc(sizeof(TNoA));
    novo-> chave = ch;
    novo-> esq = NULL;
    novo-> dir = NULL;
    return novo;
}

TNoA * insere ( TNoA *no , int chave ) {
    if ( no == NULL ) {
        no = ( TNoA * ) malloc ( sizeof ( TNoA ) ) ;
        no-> chave = chave ;
        no-> esq = NULL ;
        no-> dir = NULL ;
    } 
    else if(chave < ( no -> chave )){
        no -> esq = insere(no->esq, chave);
    }
    else if ( chave > ( no -> chave )){
        no -> dir = (insere(no->dir, chave));
    }
    else{
        printf("Inserção inválida! "); // chave já existe
        exit(1);
    }
    return no;
}

TNoA *criaArvoreBalanceada( TNoA *raiz , int v [ ] , int inicio , int fim ) {
   if ( inicio <= fim ) {
        int meio = ( inicio + fim ) / 2 ;
        raiz = insere( raiz , v [meio]) ;
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

void imprime(TNoA *no, int tab){
    if(no != NULL){
        tab +=10;
        imprime(no->dir, tab);
        printf("\n");
        for(int i =10; i<tab; i++)
            printf(" ");
        
        printf("(%d)\n", no->chave);
        imprime(no->esq, tab +2);
    }
}

TNoA *MaiorDireita(TNoA **no){
    if((*no)->dir != NULL) 
       return MaiorDireita(&(*no)->dir);
    else{
       TNoA *aux = *no;
       if((*no)->esq != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da esquerda!
          *no = (*no)->esq;
       else
          *no = NULL;
       return aux;
       }
}

TNoA *maior(TNoA *no){
    if(no->dir != NULL) 
       return maior(no->dir);
    else{       
       return no;
    }
}

TNoA *menor(TNoA *no){
    if(no->esq != NULL) 
       return menor(no->esq);
    else{       
       return no;
    }
}

int Cheia(TNoA *raiz, int *one, int *two){//NÂO FUNCIONA
    if(raiz->dir == NULL && raiz->esq == NULL){
        if(one == two){
            printf("Cheia");
            return 0;
        }else{
            printf("Não é cheia");
            return 0;
        }
        return 0;
    }else if(raiz->dir != NULL){
        Cheia(raiz->dir, one, two);
        one = one+1;
    }else if(raiz->esq != NULL){
        Cheia(raiz->esq, one, two);
        two = two+1;
    }
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
                    //armazena a chave do no excluido
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
                        anterior = criaNo(anterior->chave);
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
                            aux2 = criaNo(aux->chave); 
                            aux2->esq = aux->esq;
                            aux2->dir = aux->dir;
                            anterior->esq->chave = raiz->chave;
                            free(anterior_sub->esq);
                            anterior_sub->esq = NULL;
                            return aux2;
                        }else{
                            aux2 = criaNo(aux->chave); 
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

TNoA *espelho(TNoA *raiz, TNoA *espelhado){
    TNoA *aux;
    if(raiz != NULL){
        if (espelhado == NULL){
            espelhado = criaNo(raiz->chave);
            espelhado->dir = criaNo(raiz->esq->chave);
            espelhado->esq = criaNo(raiz->dir->chave);
        }
        aux = espelhado; 
        espelho2(raiz, espelhado);
    }
    return aux; 
}

void espelho2(TNoA *raiz, TNoA *espelhado){
     if(raiz != NULL){
        if (espelhado == NULL){
                espelhado = criaNo(raiz->chave);
        }
        if(raiz->esq != NULL)
                espelhado->dir = criaNo(raiz->esq->chave);
        if(raiz->dir != NULL)
                espelhado->esq = criaNo(raiz->dir->chave);
        
        espelho2(raiz->dir, espelhado->esq);
        espelho2(raiz->esq, espelhado->dir);
    }
    
}

int main() {
    
    //83,100,120,130,150,200,230}   80,100,150,200,220,250,260,270,275,280,290,300,350,400,500
    //int v[] =  {80,100,150,200,220,250,260,270,275,280,290,300,350,400,500,600,800,900,1000};
    int v[] = {0,1,2,3,4};
    int v2[] = {0,1,2,3,4,5,6};
    int tam = 5;
    int tam2 = 7;

    TNoA *raiz;
    raiz = NULL;
    raiz = criaArvoreBalanceada(raiz, v , 0, tam-1) ;

    TNoA *raiz2;
    raiz2 = NULL;
    raiz2 = criaArvoreBalanceada(raiz2, v2 , 0, tam2-1) ;


    printf("Impressão arb_b (pos-ordem)\n");
    posOrdem(raiz);  
    printf("Impressão arb_b (Profundidade)\n");
    profundidade(raiz2);
    raiz2 = NULL;

    raiz2 = espelho(raiz, raiz2);
    imprime(raiz,0);
    imprime(raiz2,0); 


    /*
    printf("Impressão arb_b Maior valor: %d\n", maior(raiz)->chave);
    printf("Impressão arb_b Menor valor: %d\n", menor(raiz)->chave);

    
    int *one = 0, *two = 0;
    Cheia(raiz, one, two);
    imprime(raiz,0);
    TNoA *raiz2 = NULL;
    raiz2 = espelho(raiz, raiz2);
    imprime(raiz2,0);
    */

    
   return 0;
}
