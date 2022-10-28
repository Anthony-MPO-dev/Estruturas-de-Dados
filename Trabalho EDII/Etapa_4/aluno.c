#ifndef ALUNO //Verificacao se biblioteca foi carregada
#define ALUNO

#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno{
    //chave da futura arvores
    int id;
    //dados do estudante
    char estado[3];
    char municipio[40];
    char rede[20];
    //notas do estudante
    double media_ciencias_natureza;
    double media_ciencias_humanas;  
    double media_linguagem;
    double media_matematica;
    double media_redacao;
} Alunos;

#endif