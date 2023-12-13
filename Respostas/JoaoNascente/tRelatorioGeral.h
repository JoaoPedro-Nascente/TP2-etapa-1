#ifndef _TRELATORIOGERAL_H_
#define _TRELATORIOGERAL_H_

typedef struct tRelatorioGeral tRelatorioGeral;

tRelatorioGeral *criaRelatorio(int totalPacientes, int mediaIdadePacientes, int qtdPacientesF, int qtdPacientesM, int qtdPacientesO, int tamMedioLesoes, int totalLesoes, int totalCirurgias, int totalCrioterapias);
void desalocaRelatorio(void *dado);
void imprimeNaTelaRelatorio(void *dado);
void imprimeEmArquivoRelatorio(void *dado, char *path);

#endif