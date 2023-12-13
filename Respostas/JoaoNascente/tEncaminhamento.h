#ifndef _TENCAMINHAMENTO_H_
#define _TENCAMINHAMENTO_H_

typedef struct tEncaminhamento tEncaminhamento;

tEncaminhamento *criaEncaminhamento(char *nomePaciente, char *cpfPaciente, char *especialidadeEncaminhada, char *motivoEncaminhamento, char *nomeMedico, char *crmMedico, char *data);
void desalocaEncaminhamento(void *dado);
void imprimeNaTelaEncaminhamento(void *dado);
void imprimeEmArquivoEncaminhamento(void *dado, char *path);

#endif