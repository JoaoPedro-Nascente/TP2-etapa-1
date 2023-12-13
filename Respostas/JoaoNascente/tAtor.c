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
    destroi_ator_generico funcao_desaloca;
    retornaSenhaAtor retornaSenha;
};

enum generoAtor parseGenero(char *genero);

void *cria_ator(char *nome,
                char *cpf,
                char *data,
                char *telefone,
                enum tipoAtor tipoAtor,
                char *generoAtor,
                void *atorEspecifico,
                destroi_ator_generico funcao_desaloca,
                retornaSenhaAtor retornaSenha)
{
    tAtor *ator = (tAtor *)malloc(sizeof(tAtor));

    strcpy(ator->nome, nome);
    strcpy(ator->cpf, cpf);
    strcpy(ator->data, data);
    strcpy(ator->telefone, telefone);
    ator->tipoAtor = tipoAtor;
    ator->generoAtor = parseGenero(generoAtor);
    ator->atorEspecifico = atorEspecifico;
    ator->funcao_desaloca = funcao_desaloca;
    ator->retornaSenha = retornaSenha;

    return ator;
}

void desaloca_ator(tAtor *ator)
{
    tAtor *a = (tAtor *)ator;

    a->funcao_desaloca(a->atorEspecifico);

    free(a);
}

tAtor **realoca_array_atores(void **atores, int novoTam)
{
    tAtor **arr = (tAtor **)atores;
    return (tAtor **)realloc(arr, novoTam);
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

tAtor *verificaCredenciais(void **arr1, int tam_arr1, void **arr2, int tam_arr2, char *login, char *senha)
{
    if (existeLogin(arr1, tam_arr1, arr2, tam_arr2, login))
    {
        tAtor *ator = retorna_ator_login(arr1, tam_arr1, arr2, tam_arr2, login);
        if (strcmp(ator->retornaSenha(ator->atorEspecifico), senha) == 0)
        {
            return ator;
        }
    }

    return NULL;
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

enum generoAtor parseGenero(char *genero)
{
    if (strcmp(genero, "MASCULINO") == 0)
        return Masculino;
    if (strcmp(genero, "FEMININO") == 0)
        return Feminino;
    if (strcmp(genero, "OUTROS") == 0)
        return Outros;
}

enum tipoAtor retornaTipoAtor(tAtor *ator)
{
    return ator->tipoAtor;
}

void *retornaAtorEspecifico(tAtor *ator)
{
    return ator->atorEspecifico;
}

void atualizaBdAtor(tAtor *ator, char *caminhoBd, char *nomeBd)
{
    char caminho[1000];
    strcpy(caminho, caminhoBd);
    strcat(caminho, nomeBd);
    FILE *fp;

    fp = fopen(caminho, "ab");

    fwrite(ator, 1, sizeof(tAtor), fp);

    fclose(fp);
}

char *retornaNomeAtor(void *ator)
{
    return ((tAtor *)ator)->nome;
}

char *retornaCpfAtor(void *ator)
{
    return ((tAtor *)ator)->cpf;
}

char *retornaDataNascimentoAtor(void *ator)
{
    return ((tAtor *)ator)->data;
}

enum generoAtor retornaGeneroAtor(void *ator)
{
    return ((tAtor *)ator)->generoAtor;
}

int retornaIdadeAtor(void *ator)
{
    char *pt;
    int dataInt[3];
    int cont = 0;
    int idade;

    pt = strtok(((tAtor *)ator)->data, "/");
    while (pt)
    {
        dataInt[cont] = atoi(pt);
        cont++;
        pt = strtok(NULL, "/");
    }

    idade = 2023 - dataInt[2];
    if (11 < dataInt[1])
    {
        idade--;
    }
    else if (dataInt[1] == 11)
    {
        if (dataInt[0] < 9)
            idade--;
    }

    return idade;
}