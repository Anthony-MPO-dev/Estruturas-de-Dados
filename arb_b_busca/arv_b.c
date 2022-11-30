#include <stdio.h>
#include <stdlib.h>

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

int main() {
    int tam = 15 ;
    //83,100,120,130,150,200,230}   80,100,150,200,220,250,260,270,275,280,290,300,350,400,500
    int v[] =  {80,100,150,200,220,250,260,270,275,280,290,300,350,400,500};
    TNoA *raiz ;
    raiz = NULL;
    raiz = criaArvoreBalanceada(raiz, v , 0, tam-1) ;

    printf("Impressão arb_b (Profundidade\n");
    profundidade(raiz);   

    //imprime(raiz);  
    TNoA *aux5;
    aux5 = exclui(raiz, 300);
    printf("\nnó excluido: %d\n\n",aux5->chave);
    free(aux5);

    printf("Impressão arb_b (Profundidade)\n");
    profundidade(raiz);              
   
   return 0;
}