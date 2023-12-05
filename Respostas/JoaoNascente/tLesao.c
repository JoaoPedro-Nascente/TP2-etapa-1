#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tLesao.h"

struct tLesao
{
    char rotulo[TAM_MAX_ROTULO];
    char diagnostico[TAM_MAX_DIAGNOSTICO];
    char regiao_corpo[TAM_MAX_REGIAO_CORPO];
    int tamanho;
    int cirurgia;
    int crioterapia;
};

void *cria_lesao(char *rotulo,
                 char *diagnostico,
                 char *regiao_corpo,
                 int tamanho,
                 int cirurgia,
                 int crioterapia)
{
    tLesao *l = (tLesao *)malloc(sizeof(tLesao));

    strcpy(l->rotulo, rotulo);
    strcpy(l->diagnostico, diagnostico);
    strcpy(l->regiao_corpo, regiao_corpo);
    l->tamanho = tamanho;
    l->cirurgia = cirurgia;
    l->crioterapia = crioterapia;

    return l;
}

void desaloca_lesao(void *l)
{
    tLesao *lesao = (tLesao *)l;

    free(lesao);
}