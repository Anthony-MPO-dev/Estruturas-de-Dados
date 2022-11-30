#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno{
    //chave da futura arvores
    int matricula;
    //vai armazenar o endereço para os vetor de caracteres
    char *nomes;
    //variaveis que armazenarão as notas
    int n1;
    int n2;
    int n3;
} Alunos;