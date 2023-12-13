#ifndef _TATOR_H
#define _TATOR_H

#define TAM_MAX_NOME 100
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_TELEFONE 15

typedef struct tAtor tAtor;

typedef void (*destroi_ator_generico)(void *);
typedef char *(*retornaSenhaAtor)(void *);

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
                char *generoAtor,
                void *atorEspecifico,
                destroi_ator_generico funcao_desaloca,
                retornaSenhaAtor retornaSenha);

void desaloca_ator(tAtor *ator);
tAtor **realoca_array_atores(void **atores, int novoTam);
void desaloca_array_atores(void **arr, int tam);
int atorEstaNoArray(void **arr, int tam_arr, char *cpf);
tAtor *retorna_ator_cpf(void **arr, int tam_arr, char *cpf);
int existeLogin(void **arr1, int tam_arr1, void **arr2, int tam_arr2, char *login);
tAtor *verificaCredenciais(void **arr1, int tam_arr1, void **arr2, int tam_arr2, char *login, char *senha);
tAtor *retorna_ator_login(void **arr1, int tam_arr1, void **arr2, int tam_arr2, char *login);
void **le_bd_ator(char *caminho_bd, char *nome_arquivo, int *tam);
enum tipoAtor retornaTipoAtor(tAtor *ator);
void *retornaAtorEspecifico(tAtor *ator);
void atualizaBdAtor(tAtor *ator, char *caminhoBd, char *nomeBd);
char *retornaNomeAtor(void *ator);
char *retornaCpfAtor(void *ator);
char *retornaDataNascimentoAtor(void *ator);
enum generoAtor retornaGeneroAtor(void *ator);
int retornaIdadeAtor(void *ator);

#endif