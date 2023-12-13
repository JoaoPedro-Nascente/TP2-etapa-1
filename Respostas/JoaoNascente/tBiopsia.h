#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include "tLesao.h"

typedef struct tBiopsia tBiopsia;

tBiopsia *criaBiopsia(char *nomePaciente, char *cpfPaciente, tLesao **lesoes, char *nomeMedico, char *crmMedico, char *data, int nLesoes);
void desalocaBiopsia(void *dado);
void imprimeNaTelaBiopsia(void *dado);
void imprimeEmArquivoBiopsia(void *dado, char *path);

#endif