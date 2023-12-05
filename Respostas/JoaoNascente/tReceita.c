#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tReceita.h"

struct tReceita
{
    char nomePaciente[100];
    eTipoUso tpUso;
    char nomeMedicamento[50];
    char tpMedicamento[50];
    int qtdMedicamento;
    char instrucoesUso[300];
    char nomeMedico[100];
    char crm[12];
    char data[11];
};

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr)
{
    tReceita *r = (tReceita *)malloc(sizeof(tReceita));

    strcpy(r->nomePaciente, nomePaciente);

    return r;
}

void desalocaReceita(void *dado)
{
    tReceita *r = (tReceita *)dado;

    free(r);
}

void imprimeNaTelaReceita(void *dado)
{
}

void imprimeEmArquivoReceita(void *dado, char *path);