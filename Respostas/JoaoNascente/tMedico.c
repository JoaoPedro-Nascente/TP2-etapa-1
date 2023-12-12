#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tMedico.h"

struct tMedico
{
    char crm[TAM_CRM];
    char usuario[TAM_MAX_USUARIO];
    char senha[TAM_MAX_SENHA];
};

void *cria_medico(char *crm, char *usuario, char *senha)
{
    tMedico *medico = (tMedico *)malloc(sizeof(tMedico));

    strcpy(medico->crm, crm);
    strcpy(medico->usuario, usuario);
    strcpy(medico->senha, senha);

    return medico;
}

void desaloca_medico(void *m)
{
    tMedico *medico = (tMedico *)m;

    free(medico);
}

char *retornaLoginMedico(void *m)
{
    return ((tMedico *)m)->usuario;
}

char *retornaSenhaMedico(void *m)
{
    return ((tMedico *)m)->senha;
}