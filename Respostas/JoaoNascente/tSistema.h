#ifndef _TSISTEMA_H
#define _TSISTEMA_H

#include "tAtor.h"

typedef struct tSistema tSistema;

tSistema *cria_sistema(char *caminho_saida);
void desaloca_sistema(tSistema *s);
void roda_sistema(tSistema *s);
void *realiza_consulta();

#endif