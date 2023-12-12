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

enum nivelAcesso parseNivelAcesso(char *nivelAcesso);

void *cria_secretario(char *usuario, char *senha, char *nivelAcesso)
{
    tSecretario *secretario = (tSecretario *)malloc(sizeof(tSecretario));

    strcpy(secretario->usuario, usuario);
    strcpy(secretario->senha, senha);
    secretario->nivelAcesso = parseNivelAcesso(nivelAcesso);

    return secretario;
}

void desaloca_secretario(void *s)
{
    tSecretario *secretario = (tSecretario *)s;

    free(secretario);
}

char *retornaLoginSecretario(void *s)
{
    return ((tSecretario *)s)->usuario;
}

char *retornaSenhaSecretario(void *s)
{
    return ((tSecretario *)s)->senha;
}

enum nivelAcesso parseNivelAcesso(char *nivelAcesso)
{
    if (strcmp(nivelAcesso, "ADMIN"))
        return ADMIN;
    if (strcmp(nivelAcesso, "USER"))
        return USER;
}

enum nivelAcesso retornaNivelAcesso(void *s)
{
    return ((tSecretario *)s)->nivelAcesso;
}