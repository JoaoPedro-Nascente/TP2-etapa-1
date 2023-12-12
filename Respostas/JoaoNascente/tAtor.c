#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tAtor.h"
#include "tMedico.h"
#include "tSecretario.h"

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

void desaloca_ator(tAtor *ator)
{
    tAtor *a = (tAtor *)ator;

    a->funcao_desaloca(a->atorEspecifico);

    free(a);
}

tAtor **realoca_array_atores(tAtor **atores, int novoTam)
{
    return (tAtor **)realloc(atores, novoTam);
}

void desaloca_array_atores(void **arr, int tam)
{
    tAtor **atores = (tAtor **)arr;
    for (int i = 0; i < tam; i++)
    {
        desaloca_ator(atores[i]);
    }
    free(atores);
}

int atorEstaNoArrayCPF(void **arr, int tam_arr, char *cpf)
{
    tAtor **atores = (tAtor **)arr;

    for (int i = 0; i < tam_arr; i++)
    {
        if (strcmp(atores[i]->cpf, cpf) == 0)
        {
            return 1;
        }
    }

    return 0;
}

tAtor *retorna_ator_cpf(void **arr, int tam_arr, char *cpf)
{
    tAtor **atores = (tAtor **)arr;

    for (int i = 0; i < tam_arr; i++)
    {
        if (strcmp(atores[i]->cpf, cpf) == 0)
        {
            return atores[i];
        }
    }

    return NULL;
}

int existeLogin(void **arr1, int tam_arr1, void **arr2, int tam_arr2, char *login)
{
    tAtor **atores1 = (tAtor **)arr1;
    tAtor **atores2 = (tAtor **)arr1;

    for (int i = 0; i < tam_arr1; i++)
    {
        if (strcmp(retornaLoginMedico(atores1[i]->atorEspecifico), login) == 0)
        {
            return 1;
        }
    }

    for (int i = 0; i < tam_arr1; i++)
    {
        if (strcmp(retornaLoginSecretario(atores2[i]->atorEspecifico), login) == 0)
        {
            return 1;
        }
    }

    return 0;
}

tAtor *retorna_ator_login(void **arr1, int tam_arr1, void **arr2, int tam_arr2, char *login)
{
    tAtor **atores1 = (tAtor **)arr1;
    tAtor **atores2 = (tAtor **)arr1;

    for (int i = 0; i < tam_arr1; i++)
    {
        if (strcmp(retornaLoginMedico(atores1[i]->atorEspecifico), login) == 0)
        {
            return atores1[i]->atorEspecifico;
        }
    }

    for (int i = 0; i < tam_arr1; i++)
    {
        if (strcmp(retornaLoginSecretario(atores2[i]->atorEspecifico), login) == 0)
        {
            return atores2[i]->atorEspecifico;
        }
    }

    return NULL;
}

void **le_bd_ator(char *caminho_bd, char *nome_arquivo, int *tam)
{
    char caminho[1000];
    strcpy(caminho, caminho_bd);
    strcat(caminho, nome_arquivo);

    FILE *fp;
    if (fp = fopen(caminho, "rb"))
    {
        tAtor **atores = (tAtor **)malloc(sizeof(tAtor *));
        int i = 0;

        while (fread(atores[i], sizeof(tAtor), 1, fp) == 1)
        {
            i++;
            atores = (tAtor **)realloc(atores, sizeof(tAtor *) * (i + 1));
        }
        *tam = i;
        atores = (tAtor **)realloc(atores, sizeof(tAtor *) * i);

        return (void **)atores;
    }

    *tam = 0;
    return NULL;
}