#include <stdio.h>
#include <stdlib.h>

//link da arvore_b
#include "arv_b.c"

/*
* Atividade de EDII: 
* 
* Dada a implementação da Árvore Binária de Busca vista em aula, faça adaptações no seu código para 
* armazenar dados de alunos, de modo que a busca, inserção e remoção seja feita com base no número de 
* matrícula do aluno. No caso da busca, se o aluno existir, os dados do aluno deverão ser retornados 
* por referência. Em seguida, escreva um programa para ler um arquivo contendo os dados de 2287 alunos. 
* Cada linha do arquivo representa um aluno e é composta por 5 informações, separadas por espaço: 
* matricula (inteiro), nome e 3 notas (inteiro).
*
* Avalie o desempenho da Árvore Binária de Busca a medida que esses dados são inseridos:
*
*  - Número de níveis
*  - Altura da árvore
*  - Altura da árvore da sub-árvore esquerda e direita
*
*
* Autor: Anthony M. P. de Oliveira
* RGA: 202011722003
*/

int main() {
    int tam = 2287;
    //cria o vetor para armazenar os alunos em ordem
    Alunos v[2287];
    //cria variavel do tipo file
    FILE *file;
    //file recebe o arquivo alunos
    file = fopen("alunos.txt", "r");

    for(int i = 0; i < 2287; i++){
        //aloca espaço para receber o vetor de caracteres
        v[i].nomes = malloc(sizeof (char));
        //scaneia o arquivo e retira os valores que seram utilizados para construção da arv_b
        fscanf(file, "%d %s %d %d %d", &v[i].matricula, v[i].nomes, &v[i].n1, &v[i].n2, &v[i].n3 );
        printf("%d %s %d %d %d\n", v[i].matricula, v[i].nomes, v[i].n1, v[i].n2, v[i].n3);
    }
    fclose(file);

    printf("\n\n%d %s %d %d %d\n", v[0].matricula, v[0].nomes, v[0].n1, v[0].n2, v[0].n3);
    
    
    TNoA *raiz ;
    raiz = NULL;
    //cria a arvore balanceada
    raiz = criaArvoreBalanceada(raiz, v, 0, tam-1);

    //impressão da arvores balancerada
    printf("Arvore de Busca Balanceada:\n");
    imprime(raiz, 0);  
    printf("\nFim da impressão da arvore\n");

    //exclusão de no nº300
    TNoA *aux5;
    aux5 = exclui(raiz, 300);
    printf("\nNó excluido: %d\n\n",aux5->chave);
    free(aux5);

    //Busca na arv_b 
    TNoA *NO = busca(raiz, 32);
    printf("\nBUSCANDO ALUNO:(%d) \nAluno: %s \nNotas %d, %d, %d\n", NO->chave, NO->nome, NO->n1, NO->n2, NO->n3);  

    int *alt[3];

    alt[0] = altura(raiz, alt);
    printf("\n A arvore binaria possui altualmente: %d niveis\n sub-árvore esq-> %d niveis\n sub-árvore dir-> %d niveis\n", alt[0], alt[1], alt[2]);       
   
   return 0;
}