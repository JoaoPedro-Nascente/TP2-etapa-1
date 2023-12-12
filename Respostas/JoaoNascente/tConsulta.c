#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tConsulta.h"

struct tConsulta
{
    char nomePaciente[TAM_MAX_NOME];
    char cpfPaciente[TAM_CPF];
    char nomeMedico[TAM_MAX_NOME];
    char crmMedico[TAM_CRM];
    char data[TAM_DATA];
};

void *cria_consulta(char *nomePaciente, char *cpfPaciente, char *nomeMedico, char *crm, char *data)
{
    tConsulta *c = (tConsulta *)malloc(sizeof(tConsulta));

    strcpy(c->nomeMedico, nomePaciente);
    strcpy(c->cpfPaciente, cpfPaciente);
    strcpy(c->nomeMedico, nomeMedico);
    strcpy(c->crmMedico, crm);
    strcpy(c->data, data);

    return c;
}

void desaloca_consulta(void *consulta)
{
    tConsulta *c = (tConsulta *)consulta;

    free(c);
}

void **le_bd_consulta(char *caminho_bd, char *nome_arquivo, int *tam)
{
    char caminho[1000];
    strcpy(caminho, caminho_bd);
    strcat(caminho, nome_arquivo);

    FILE *fp;
    if (fp = fopen(caminho, "rb"))
    {
        tConsulta **consultas = (tConsulta **)malloc(sizeof(tConsulta *));
        int i = 0;

        while (fread(consultas[i], sizeof(tConsulta), 1, fp) == 1)
        {
            i++;
            consultas = (tConsulta **)realloc(consultas, sizeof(tConsulta *) * (i + 1));
        }
        *tam = i;
        consultas = (tConsulta **)realloc(consultas, sizeof(tConsulta *) * i);

        return (void **)consultas;
    }

    *tam = 0;
    return NULL;
}