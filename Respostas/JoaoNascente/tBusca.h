#ifndef _TBUSCA_H_
#define _TBUSCA_H_

#include "tAtor.h"

typedef struct tBusca tBusca;

tBusca *criaBusca(tAtor **pacientes, int nPacientes);
void desalocaBusca(void *dado);
void imprimeNaTelaBusca(void *dado);
void imprimeEmArquivoBusca(void *dado, char *path);

#endif