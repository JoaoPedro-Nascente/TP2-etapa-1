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

void desaloca_lesoes(void **lesoes, int nLesoes)
{
    tLesao **l = (tLesao **)lesoes;

    for (int i; i < nLesoes; i++)
    {
        desaloca_lesao(l[i]);
    }

    if (nLesoes > 0)
    {
        free(l);
    }
}

void **le_bd_lesao(char *caminho_bd, char *nome_arquivo, int *tam)
{
    char caminho[1000];
    strcpy(caminho, caminho_bd);
    strcat(caminho, nome_arquivo);

    FILE *fp;
    if (fp = fopen(caminho, "rb"))
    {
        tLesao **lesoes = (tLesao **)malloc(sizeof(tLesao *));
        int i = 0;

        while (fread(lesoes[i], sizeof(tLesao), 1, fp) == 1)
        {
            i++;
            lesoes = (tLesao **)realloc(lesoes, sizeof(tLesao *) * (i + 1));
        }
        *tam = i;
        lesoes = (tLesao **)realloc(lesoes, sizeof(tLesao *) * i);

        return (void **)lesoes;
    }

    *tam = 0;
    return NULL;
}