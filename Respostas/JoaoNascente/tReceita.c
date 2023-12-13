#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tReceita.h"

struct tReceita
{
    char nomePaciente[100];
    eTipoUso tpUso;
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tpMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    int qtdMedicamento;
    char instrucoesUso[MAX_TAM_INSTRUCOES];
    char nomeMedico[100];
    char crm[12];
    char data[11];
};

char *retornaTpUso(eTipoUso tipoUso);

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr)
{
    tReceita *r = (tReceita *)malloc(sizeof(tReceita));

    strcpy(r->nomePaciente, nomePaciente);
    strcpy(r->nomeMedicamento, nomeMedicamento);
    strcpy(r->tpMedicamento, tipoMedicamento);
    strcpy(r->instrucoesUso, instrucoes);
    strcpy(r->nomeMedico, nomeMedico);
    strcpy(r->crm, CRM);
    strcpy(r->data, dataStr);
    r->tpUso = tipoUso;
    r->qtdMedicamento = qntd;

    return r;
}

void desalocaReceita(void *dado)
{
    tReceita *r = (tReceita *)dado;

    free(r);
}

void imprimeNaTelaReceita(void *dado)
{
    tReceita *r = (tReceita *)dado;

    printf("RECEITUÁRIO\n");
    printf("NOME: %s\n", r->nomePaciente);
    printf("\n");
    printf("USO %s\n", retornaTpUso(r->tpUso));
    printf("\n");
    printf("%s\n", r->nomeMedicamento);
    printf("%d %s\n", r->qtdMedicamento, r->tpMedicamento);
    printf("\n");
    printf("%s\n", r->instrucoesUso);
    printf("\n");
    printf("%s (%s)\n", r->nomeMedico, r->crm);
    printf("%s\n", r->data);
}

void imprimeEmArquivoReceita(void *dado, char *path)
{
    char caminho[1000];
    tReceita *r = (tReceita *)dado;

    strcpy(caminho, path);
    strcat(caminho, "/receita.txt");

    FILE *fp;
    fp = fopen(path, "a");

    fprintf(fp, "RECEITUÁRIO\n");
    fprintf(fp, "NOME: %s\n", r->nomePaciente);
    fprintf(fp, "\n");
    fprintf(fp, "USO %s\n", retornaTpUso(r->tpUso));
    fprintf(fp, "\n");
    fprintf(fp, "%s\n", r->nomeMedicamento);
    fprintf(fp, "%d %s\n", r->qtdMedicamento, r->tpMedicamento);
    fprintf(fp, "\n");
    fprintf(fp, "%s\n", r->instrucoesUso);
    fprintf(fp, "\n");
    fprintf(fp, "%s (%s)\n", r->nomeMedico, r->crm);
    fprintf(fp, "%s\n", r->data);
    fprintf(fp, "\n");
    fprintf(fp, "\n");

    fclose(fp);
}

char *retornaTpUso(eTipoUso tipoUso)
{
    if (tipoUso == ORAL)
    {
        return "ORAL";
    }

    return "TOPICO";
}