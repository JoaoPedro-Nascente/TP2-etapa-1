#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tAtor.h"

struct tAtor
{
    char nome[TAM_MAX_NOME];
    char cpf[TAM_CPF];
    char data[TAM_DATA];
    char telefone[TAM_TELEFONE];
    enum tipoAtor tipoAtor;
    enum generoAtor generoAtor;
    void *atorEspecifico;
    destroi_ator_generico *funcao_desaloca;
};

void *cria_ator(char *nome,
                char *cpf,
                char *data,
                char *telefone,
                enum tipoAtor tipoAtor,
                enum generoAtor generoAtor,
                void *atorEspecifico,
                destroi_ator_generico *funcao_desaloca)
{
    tAtor *ator = (tAtor *)malloc(sizeof(tAtor));

    strcpy(ator->nome, nome);
    strcpy(ator->cpf, cpf);
    strcpy(ator->data, data);
    strcpy(ator->telefone, telefone);
    ator->tipoAtor = tipoAtor;
    ator->generoAtor = generoAtor;
    ator->atorEspecifico = atorEspecifico;
    ator->funcao_desaloca = funcao_desaloca;

    return ator;
}

void desaloca_ator(void *ator)
{
    tAtor *a = (tAtor *)ator;

    a->funcao_desaloca(a->atorEspecifico);

    free(a);
}