#ifndef _TLESAO_H
#define _TLESAO_H

#define TAM_MAX_ROTULO 5
#define TAM_MAX_DIAGNOSTICO 30
#define TAM_MAX_REGIAO_CORPO 30

typedef struct tLesao tLesao;

void *cria_lesao(char *rotulo, char *diagnostico, char *regiao_corpo, int tamanho, int cirurgia, int crioterapia);
void desaloca_lesao(void *l);
void desaloca_lesoes(void **lesoes, int nLesoes);
void **le_bd_lesao(char *caminho_bd, char *nome_arquivo, int *tam);

#endif