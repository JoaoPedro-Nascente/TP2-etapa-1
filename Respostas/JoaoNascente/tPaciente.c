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
};

enum tipoPele parseTipoPele(char *tpPele)
{
    if (strcmp(tpPele, "I"))
        return I;
    if (strcmp(tpPele, "II"))
        return II;
    if (strcmp(tpPele, "III"))
        return III;
    if (strcmp(tpPele, "IV"))
        return IV;
    if (strcmp(tpPele, "V"))
        return V;
    if (strcmp(tpPele, "VI"))
        return VI;
}

void *cria_paciente()
{
    tPaciente *p = (tPaciente *)malloc(sizeof(tPaciente));

    p->possui_diabetes = 0;
    p->fuma = 0;
    p->possui_alergia = 0;
    p->possui_historico_cancer = 0;

    return p;
}

void consultaPaciente(void *paciente,
                      int possui_diabetes,
                      int fuma,
                      int possui_alergia,
                      int possui_historico_cancer,
                      char *tipoPele)
{
    tPaciente *p = (tPaciente *)paciente;

    p->possui_diabetes = possui_diabetes;
    p->fuma = fuma;
    p->possui_alergia = possui_alergia;
    p->possui_historico_cancer = possui_historico_cancer;
    p->tipoPele = parseTipoPele(tipoPele);
}

void desaloca_paciente(void *paciente)
{
    tPaciente *p = (tPaciente *)paciente;

    free(p);
}