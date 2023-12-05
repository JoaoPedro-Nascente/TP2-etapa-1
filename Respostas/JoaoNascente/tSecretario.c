#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tSecretario.h"

struct tSecretario
{
    char usuario[TAM_MAX_USUARIO];
    char senha[TAM_MAX_SENHA];
    enum nivelAcesso nivelAcesso;
};

void *cria_secretario(char *usuario, char *senha, enum nivelAcesso nivelAcesso)
{
    tSecretario *secretario = (tSecretario *)malloc(sizeof(tSecretario));

    strcpy(secretario->usuario, usuario);
    strcpy(secretario->senha, senha);
    secretario->nivelAcesso = nivelAcesso;

    return secretario;
}

void desaloca_secretario(void *s)
{
    tSecretario *secretario = (tSecretario *)s;

    free(secretario);
}