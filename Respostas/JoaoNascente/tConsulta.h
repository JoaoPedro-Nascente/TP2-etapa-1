#ifndef _TCONSULTA_H
#define _TCONSULTA_H

#define TAM_MAX_NOME 100
#define TAM_CPF 15
#define TAM_CRM 12
#define TAM_DATA 11

typedef struct tConsulta tConsulta;

void *cria_consulta(char *nomePaciente, char *cpfPaciente, char *nomeMedico, char *crm, char *data);
void desaloca_consulta(void *consulta);
void desaloca_array_consultas(void **arr, int tam);
void *realiza_consulta();
void **le_bd_consulta(char *caminho_bd, char *nome_arquivo, int *tam);
void atualizaBdConsultas(tConsulta *consulta, char *caminhoBd, char *nomeBd);
tConsulta **realoca_array_consultas(void **consultas, int novoTam);

#endif