#include <stdio.h>
#include <stdlib.h>

const int d =2; // fator de ramificação

typedef struct No{
    int m; //quantidade de chaves armazenadas no nó
    struct No *pont_pai;
    int *s; //array de chaves
    struct No **p; // ponteiro para array de ponteiros para os filhos
} TNo;

TNo *insere(TNo *raiz, int folha, int ch, TNo *pt);

//Função que inicializa a arvore de Busca B
TNo* inicializa(){
    return NULL;
}

//Função para alocar/criar novos nós para a arvore
TNo *criaNO(){
    TNo * novo = (TNo *) malloc(sizeof(TNo));
    novo->m = 0; // quantidade de valores armazenados no vetor
    novo->pont_pai = NULL; 
    novo->s = (int *) malloc(sizeof(int *) * (d * 2)); // vetor vai ter o tamanho maximo de 2d
    novo->p = (TNo **) malloc(sizeof(TNo *) * (d * 2) + 1); // numero maximo de filhos por nó é 2d + 1 
    //EX: d=2 então numero maximo de filhos de um no_vetor pai é 5
    for (int i = 0; i< (d*2 + 1); i++){// define todos os filhos para NULL
        novo->p[i] = NULL;
    } 
    return novo;//retorna o no alocado
}

//Função realiza a busca de um nó especifico pela arvore de Busca B
TNo *busca(TNo *no, int ch) {
    if (no != NULL){
        int i =0;
        while (i < no->m && ch > no->s[i]){
            i++;  
        }
        if (i < no->m && ch == no->s[i]){
            return no; // encontrou o nó desejado
        } else if (no->p[i] != NULL){
            return busca(no->p[i], ch);
        }else return no; // nó era folha -- não existem mais nós a buscar, então retorna o nó onde a chave deveria estar
        
    }else return NULL; // nó é NULL, não há como buscar
}

//Função que vai particionar o vetor do nó caso ele 
//esteja cheio e não possa mais suportar valores
TNo *particiona(TNo *raiz, TNo *P, int ch, TNo *pt){
    TNo *Q = criaNO();// cria o novo no/vetor que recebera os valores particionados a direita
    Q->m = d;
    Q->pont_pai = P->pont_pai;

    int pos = -1;
    for (int i = 0; i < P->m; i++){//encontra o valor onde a chave deve ser colocada
        if (ch > P->s[i]){
            pos = i + 1;
        }
    }
    if (pos == -1){
        //chave a ser inserida é menor de todas as presentes no nó e deve ser inserida na primeira posição
        pos = 0;
    }

    int chave_d;
    TNo *pt_chave_d = Q;

    if (pos != d && pos < d) //pos for diferente do meio e for menor que d
        chave_d = P->s[d - 1];//ela vai ser inserida a esquerda
    else if (pos != d) // se a posição eh diferente de meio e maior que d
        chave_d = P->s[d]; // vai ser inserido no meio
    else
        chave_d = ch;

    int i = d * 2 - 1;
    int j = d - 1;

    while(j>=0){
        if(j != pos - d - 1){
            Q->s[j] = P->s[i];
            Q->p[j + 1] = P->p[i + 1];
            i--;
        }else{
            //insere ch em Q na posição correta
            Q->s[j] = ch;
            Q->p[j + 1] = pt;
        }
        j--;
    }

    Q->p[0] = P->p[d]; // faz a metade da direita do vetor de ponteiros ser particionada para a nova pagina de vetores

    j = d;
    while(i > pos){
        P->s[i] = P->s[i - 1];
        P->p[i + 1] = P->p[i];
        i--;
    }

    if (pos <= d){
        P->s[pos] = ch; // insere chave na posição pos
        P->p[pos + 1] = pt; // insere o ponteiro dele na posição pos+1
    } 

    P->m = d;

    TNo *pai = insere(P->pont_pai, 0, chave_d, pt_chave_d);

    //se apos o particionamento o ponteiro pai for nulo
    //significa que era o primeiro no da arvores, então
    //deve ser definido o pai de P e Q
    if (P->pont_pai == NULL){
        P->pont_pai = pai;
        Q->pont_pai = pai;
        pai->p[0] = P;
        pai->p[1] = Q;
    }
    printf("No de chave: %d foi particionado\n", chave_d);
    raiz = pai;
    return raiz;
}


//Função que insere valores na arvore de Busca B
TNo *insere(TNo *raiz, int folha, int ch, TNo *pt){
    TNo *no_aux;
    if (folha) {
        no_aux = busca(raiz, ch); // busca o nó folha da arvore
        if (no_aux != NULL){
            for (int i=0; i< no_aux->m; i++){
                // nó ja existe  não pode ser inserido 
                if (no_aux->s[i] == ch){
                    return raiz; //apenas retorna a raiz
                }
            }
        }
    }
    else{
        no_aux = raiz;
    }

    if (raiz == NULL){//primeiro nó da arvore
        raiz = criaNO();
        raiz->s[0] = ch; // armazena a chave na posição zero do primeiro vetor da arvore
        raiz->m = 1;
        //atualizada raiz da arvore
        return raiz;
    }else{ //se o nó não for o nó raiz ou seja o primeiro no da arvore
        if(no_aux->m == (2*d)){//se o no estiver cheio
            //particiona o vetor e sobe o valor do meio
            raiz = particiona(raiz, no_aux, ch, pt);
        }else{//se o no não estiver cheio
            //apenas insere dentro do vetor do no atual
            int i = no_aux->m;
            while (i >= 0 && ch < no_aux->s[i-1]){
                no_aux->s[i] = no_aux->s[i - 1];
                no_aux->p[i + 1] = no_aux->p[i];
                i--;
            }
            if (i == -1){
                i = 0;
            }
            no_aux->s[i] = ch;
            no_aux->p[i + 1] = pt;
            no_aux->m++;

        }
    }
}

void imprime(TNo *a, int nivel){
    if (a != NULL){
        if (nivel >=0)
            printf("Nivel %d:\n", nivel);
        for (int i =0; i<a->m; i++){
            printf("%5d", a->s[i]);
        }
        printf("\n");
        //Imprime filhos recursivamente, se não for folha
        if (a->p[0] != NULL){
            for (int i =0; i<= a->m; i++){
                imprime(a->p[i], nivel+1);
            }
        }
    }
}

int main(){
    TNo *raiz = inicializa();

    raiz = insere(raiz, 1, 10, NULL);
    raiz = insere(raiz, 1, 20, NULL);
    raiz = insere(raiz, 1, 30, NULL);
    raiz = insere(raiz, 1, 40, NULL);
    raiz = insere(raiz, 1, 50, NULL);
    raiz = insere(raiz, 1, 15, NULL);
    raiz = insere(raiz, 1, 45, NULL);
    raiz = insere(raiz, 1, 25, NULL);
    raiz = insere(raiz, 1, 22, NULL);
    raiz = insere(raiz, 1, 42, NULL);
    raiz = insere(raiz, 1, 43, NULL);
    raiz = insere(raiz, 1, 5, NULL);
    raiz = insere(raiz, 1, 8, NULL);
    raiz = insere(raiz, 1, 7, NULL);
    raiz = insere(raiz, 1, 12, NULL);
    raiz = insere(raiz, 1, 18, NULL);
    raiz = insere(raiz, 1, 11, NULL);

    printf("Resultado final da inserção: \n");
    imprime(raiz, 0);

    printf("Busca valor 22:\n");
    TNo *find = inicializa();
    find = busca(raiz, 22);
    int i = 0;
    while(find->s[i] != NULL){
        if(find->s[i] == 22)
            printf("%5d",find->s[i]);

        i++;
    }
    printf("\n");
}