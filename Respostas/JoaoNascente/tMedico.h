#ifndef _TMEDICO_H
#define _TMEDICO_H

#define TAM_CRM 12
#define TAM_MAX_USUARIO 20
#define TAM_MAX_SENHA 20

typedef struct tMedico tMedico;

void *cria_medico(char *crm, char *usuario, char *senha);
void desaloca_medico(void *m);

#endif