#ifndef _TSECRETARIO_H
#define _TSECRETARIO_H

#define TAM_MAX_USUARIO 20
#define TAM_MAX_SENHA 20

typedef struct tSecretario tSecretario;

enum nivelAcesso
{
    USER,
    ADMIN
};

void *cria_secretario(char *usuario, char *senha, enum nivelAcesso nivelAcesso);
void desaloca_secretario(void *s);
char *retornaLoginSecretario(void *s);

#endif