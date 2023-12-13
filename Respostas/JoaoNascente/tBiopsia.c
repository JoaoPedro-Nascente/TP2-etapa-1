#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tBiopsia.h"

struct tBiopsia
{
    char nomePaciente[100];
    char cpfPaciente[15];
    tLesao **lesoes;
    char nomeMedico[100];
    char crmMedico[12];
    char data[11];
    int nLesoes;
};

tBiopsia *criaBiopsia(char *nomePaciente, char *cpfPaciente, tLesao **lesoes, char *nomeMedico, char *crmMedico, char *data, int nLesoes)
{
    tBiopsia *biopsia = (tBiopsia *)malloc(sizeof(tBiopsia));

    strcpy(biopsia->nomePaciente, nomePaciente);
    strcpy(biopsia->cpfPaciente, cpfPaciente);
    biopsia->lesoes = lesoes;
    strcpy(biopsia->nomeMedico, nomeMedico);
    strcpy(biopsia->crmMedico, crmMedico);
    strcpy(biopsia->data, data);
    biopsia->nLesoes = nLesoes;

    return biopsia;
}

void desalocaBiopsia(void *dado)
{
    tBiopsia *biopsia = (tBiopsia *)dado;

    free(biopsia->lesoes);
    free(biopsia);
}

void imprimeNaTelaBiopsia(void *dado)
{
    tBiopsia *biopsia = (tBiopsia *)dado;

    printf("PACIENTE: %s\n", biopsia->nomePaciente);
    printf("CPF: %s\n", biopsia->cpfPaciente);
    printf("\n");
    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");

    for (int i = 0; i < biopsia->nLesoes; i++)
    {
        printf("%s - %s - %s - %dMM\n", retornaRotuloLesao(biopsia->lesoes[i]), retornaDiagnosticoLesao(biopsia->lesoes[i]), retornaRegiaoLesao(biopsia->lesoes[i]), retornaTamanhoLesao(biopsia->lesoes[i]));
    }

    printf("\n");
    printf("DR. %s (%s)\n", biopsia->nomeMedico, biopsia->crmMedico);
    printf("%s\n", biopsia->data);
}

void imprimeEmArquivoBiopsia(void *dado, char *path)
{
    tBiopsia *biopsia = (tBiopsia *)dado;

    char caminho[1000];

    strcpy(caminho, path);
    strcat(caminho, "/biopsia.txt");

    FILE *fp;
    fp = fopen(path, "a");

    fprintf(fp, "PACIENTE: %s\n", biopsia->nomePaciente);
    fprintf(fp, "CPF: %s\n", biopsia->cpfPaciente);
    fprintf(fp, "\n");
    fprintf(fp, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");

    for (int i = 0; i < biopsia->nLesoes; i++)
    {
        fprintf(fp, "%s - %s - %s - %dMM\n", retornaRotuloLesao(biopsia->lesoes[i]), retornaDiagnosticoLesao(biopsia->lesoes[i]), retornaRegiaoLesao(biopsia->lesoes[i]), retornaTamanhoLesao(biopsia->lesoes[i]));
    }

    fprintf(fp, "\n");
    fprintf(fp, "DR. %s (%s)\n", biopsia->nomeMedico, biopsia->crmMedico);
    fprintf(fp, "%s\n", biopsia->data);

    fclose(fp);
}