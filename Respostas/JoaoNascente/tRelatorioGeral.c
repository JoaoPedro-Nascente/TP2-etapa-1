#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tRelatorioGeral.h"

struct tRelatorioGeral
{
    int totalPacientes;
    int mediaIdadePacientes;
    int qtdPacientesF;
    int qtdPacientesM;
    int qtdPacientesO;
    int tamMedioLesoes;
    int totalLesoes;
    int totalCirurgias;
    int totalCrioterapias;
};

tRelatorioGeral *criaRelatorio(int totalPacientes, int mediaIdadePacientes, int qtdPacientesF, int qtdPacientesM, int qtdPacientesO, int tamMedioLesoes, int totalLesoes, int totalCirurgias, int totalCrioterapias)
{
    tRelatorioGeral *relatorio = (tRelatorioGeral *)malloc(sizeof(tRelatorioGeral));

    relatorio->totalPacientes = totalPacientes;
    relatorio->mediaIdadePacientes = mediaIdadePacientes;
    relatorio->qtdPacientesF = qtdPacientesF;
    relatorio->qtdPacientesM = qtdPacientesM;
    relatorio->qtdPacientesO = qtdPacientesO;
    relatorio->tamMedioLesoes = tamMedioLesoes;
    relatorio->totalLesoes = totalLesoes;
    relatorio->totalCirurgias = totalCirurgias;
    relatorio->totalCrioterapias = totalCrioterapias;

    return relatorio;
}

void desalocaRelatorio(void *dado)
{
    tRelatorioGeral *relatorio = (tRelatorioGeral *)dado;

    free(relatorio);
}

void imprimeNaTelaRelatorio(void *dado)
{
    tRelatorioGeral *relatorio = (tRelatorioGeral *)dado;

    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", relatorio->totalPacientes);
    printf("IDADE MEDIA: %d\n", relatorio->mediaIdadePacientes);
    printf("DISTRIBUICAO POR GENERO:\n");
    printf("- FEMININO: %d\n", relatorio->qtdPacientesF);
    printf("- MASCULINO: %d\n", relatorio->qtdPacientesM);
    printf("- OUTROS: %d\n", relatorio->qtdPacientesO);
    printf("TAMANHO MEDIO DAS LESOES: %d\n", relatorio->tamMedioLesoes);
    printf("NUMERO TOTAL DE LESOES: %d\n", relatorio->totalLesoes);
    printf("NUMERO TOTAL DE CIRURGIAS: %d\n", relatorio->totalCirurgias);
    printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n", relatorio->totalCrioterapias);
}

void imprimeEmArquivoRelatorio(void *dado, char *path)
{
    tRelatorioGeral *relatorio = (tRelatorioGeral *)dado;

    char caminho[1000];

    strcpy(caminho, path);
    strcat(caminho, "/relatorio_geral.txt");

    FILE *fp;
    fp = fopen(path, "a");

    fprintf(fp, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", relatorio->totalPacientes);
    fprintf(fp, "IDADE MEDIA: %d\n", relatorio->mediaIdadePacientes);
    fprintf(fp, "DISTRIBUICAO POR GENERO:\n");
    fprintf(fp, "- FEMININO: %d\n", relatorio->qtdPacientesF);
    fprintf(fp, "- MASCULINO: %d\n", relatorio->qtdPacientesM);
    fprintf(fp, "- OUTROS: %d\n", relatorio->qtdPacientesO);
    fprintf(fp, "TAMANHO MEDIO DAS LESOES: %d\n", relatorio->tamMedioLesoes);
    fprintf(fp, "NUMERO TOTAL DE LESOES: %d\n", relatorio->totalLesoes);
    fprintf(fp, "NUMERO TOTAL DE CIRURGIAS: %d\n", relatorio->totalCirurgias);
    fprintf(fp, "NUMERO TOTAL DE CRIOTERAPIA: %d\n", relatorio->totalCrioterapias);

    fclose(fp);
}