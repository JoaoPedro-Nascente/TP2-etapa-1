#ifndef _TATOR_H
#define _TATOR_H

#define TAM_MAX_NOME 100
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_TELEFONE 15

typedef struct tAtor tAtor;

typedef void destroi_ator_generico(void *);

enum tipoAtor
{
    Paciente,
    Secretario,
    Medico
};

enum generoAtor
{
    Masculino,
    Feminino,
    Outros
};

void *cria_ator(char *nome,
                char *cpf,
                char *data,
                char *telefone,
                enum tipoAtor tipoAtor,
                enum generoAtor generoAtor,
                void *atorEspecifico,
                destroi_ator_generico *funcao_desaloca);

void desaloca_ator(void *ator);

#endif