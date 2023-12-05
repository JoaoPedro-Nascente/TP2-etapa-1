#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tPaciente.h"
#include "tLesao.h"

struct tPaciente
{
    int possui_diabetes;
    int fuma;
    int possui_alergia;
    int possui_historico_cancer;
    enum tipoPele tipoPele;
    int n_lesoes_cadastradas;
    void **lesoes;
};

void *cria_paciente()
{
    tPaciente *p = (tPaciente *)malloc(sizeof(tPaciente));

    p->possui_diabetes = 0;
    p->fuma = 0;
    p->possui_alergia = 0;
    p->possui_historico_cancer = 0;
    p->n_lesoes_cadastradas = 0;
    p->lesoes = NULL;

    return p;
}

void realiza_consulta(void *paciente,
                      int possui_diabetes,
                      int fuma,
                      int possui_alergia,
                      int possui_historico_cancer,
                      enum tipoPele tipoPele)
{
    tPaciente *p = (tPaciente *)paciente;

    p->possui_diabetes = possui_diabetes;
    p->fuma = fuma;
    p->possui_alergia = possui_alergia;
    p->possui_historico_cancer = possui_historico_cancer;
    p->tipoPele = tipoPele;
}

void adiciona_lesao(void *paciente, void *l)
{
    tPaciente *p = (tPaciente *)paciente;

    p->n_lesoes_cadastradas++;
    p->lesoes = (void *)realloc(p->lesoes, p->n_lesoes_cadastradas);
    p->lesoes[p->n_lesoes_cadastradas - 1] = l;
}

void desaloca_paciente(void *paciente)
{
    tPaciente *p = (tPaciente *)paciente;
    if (p->lesoes != NULL)
    {
        for (int i = 0; i < p->n_lesoes_cadastradas; i++)
        {
            desaloca_lesao(p->lesoes[i]);
        }
        free(p->lesoes);
    }

    free(p);
}