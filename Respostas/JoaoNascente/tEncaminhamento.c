#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tEncaminhamento.h"

struct tEncaminhamento
{
    char nomePaciente[100];
    char cpfPaciente[15];
    char especialidadeEncaminhada[50];
    char motivoEncaminhamento[300];
    char nomeMedico[100];
    char crmMedico[12];
    char data[11];
};

tEncaminhamento *criaEncaminhamento(char *nomePaciente, char *cpfPaciente, char *especialidadeEncaminhada, char *motivoEncaminhamento, char *nomeMedico, char *crmMedico, char *data)
{
    tEncaminhamento *encaminhamento = (tEncaminhamento *)malloc(sizeof(tEncaminhamento));

    strcpy(encaminhamento->nomePaciente, nomePaciente);
    strcpy(encaminhamento->cpfPaciente, cpfPaciente);
    strcpy(encaminhamento->especialidadeEncaminhada, especialidadeEncaminhada);
    strcpy(encaminhamento->motivoEncaminhamento, motivoEncaminhamento);
    strcpy(encaminhamento->nomeMedico, nomeMedico);
    strcpy(encaminhamento->crmMedico, crmMedico);
    strcpy(encaminhamento->data, data);

    return encaminhamento;
}

void desalocaEncaminhamento(void *dado)
{
    tEncaminhamento *encaminhamento = (tEncaminhamento *)dado;

    free(encaminhamento);
}

void imprimeNaTelaEncaminhamento(void *dado)
{
    tEncaminhamento *encaminhamento = (tEncaminhamento *)dado;

    printf("PACIENTE: %s\n", encaminhamento->nomePaciente);
    printf("CPF: %s\n", encaminhamento->cpfPaciente);
    printf("\n");
    printf("ESPECIALIDADE ENCAMINHADA: %s\n", encaminhamento->especialidadeEncaminhada);
    printf("MOTIVO: %s\n", encaminhamento->motivoEncaminhamento);
    printf("\n");
    printf("DR. %s (%s)\n", encaminhamento->nomeMedico, encaminhamento->crmMedico);
    printf("%s\n", encaminhamento->data);
}

void imprimeEmArquivoEncaminhamento(void *dado, char *path)
{
    tEncaminhamento *encaminhamento = (tEncaminhamento *)dado;

    char caminho[1000];

    strcpy(caminho, path);
    strcat(caminho, "/encaminhamento.txt");

    FILE *fp;
    fp = fopen(path, "a");

    fprintf(fp, "PACIENTE: %s\n", encaminhamento->nomePaciente);
    fprintf(fp, "CPF: %s\n", encaminhamento->cpfPaciente);
    fprintf(fp, "\n");
    fprintf(fp, "ESPECIALIDADE ENCAMINHADA: %s\n", encaminhamento->especialidadeEncaminhada);
    fprintf(fp, "MOTIVO: %s\n", encaminhamento->motivoEncaminhamento);
    fprintf(fp, "\n");
    fprintf(fp, "DR. %s (%s)\n", encaminhamento->nomeMedico, encaminhamento->crmMedico);
    fprintf(fp, "%s\n", encaminhamento->data);

    fclose(fp);
}