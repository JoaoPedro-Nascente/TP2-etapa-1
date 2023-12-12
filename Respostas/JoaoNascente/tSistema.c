#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tSistema.h"
#include "tAtor.h"
#include "tSecretario.h"
#include "tMedico.h"
#include "tPaciente.h"
#include "tConsulta.h"
#include "tLesao.h"

struct tSistema
{
    char caminho_saida[1000];
    char caminho_bd[1000];
    void **medicos_sistema;
    int nMedicosSistema;
    void **secretarios_sistema;
    int nSecretariosSistema;
    void **pacientes_sistema;
    int nPacientesSistema;
    void **consultas;
    int nConsultasSistema;
    int nLesoes;
    void **lesoes;
    tAtor *usuario;
    int encerra;
};

void *telaDeAcesso(tSistema *s);
void exibeMenu(tSistema *s);
void cadastroSecretario(tSistema *s);
void cadastroMedico(tSistema *s);
void cadastroPaciente(tSistema *s);

tSistema *cria_sistema(char *caminho_saida)
{
    char caminho_bd_completo[1000];
    char caminho_bd[1000];
    tSistema *s = (tSistema *)malloc(sizeof(tSistema));

    strcpy(s->caminho_saida, caminho_saida);

    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS:\n");
    printf("################################################\n");
    scanf("%s", caminho_bd);
    strcpy(caminho_bd_completo, caminho_saida);
    strcat(caminho_bd_completo, "/");
    strcat(caminho_bd_completo, caminho_bd);

    strcpy(s->caminho_bd, caminho_bd_completo);

    s->medicos_sistema = le_bd_ator(s->caminho_bd, "medicos.bin", &s->nMedicosSistema);

    s->secretarios_sistema = le_bd_ator(s->caminho_bd, "secretarios.bin", &s->nSecretariosSistema);

    s->pacientes_sistema = le_bd_ator(s->caminho_bd, "pacientes.bin", &s->nPacientesSistema);

    s->consultas = le_bd_consulta(s->caminho_bd, "consultas.bin", &s->nConsultasSistema);

    s->lesoes = le_bd_lesao(s->caminho_bd, "/lesoes.bin", &s->nLesoes);

    s->usuario = telaDeAcesso(s);

    s->encerra = 0;

    return s;
}

void desaloca_sistema(tSistema *s)
{
    desaloca_array_atores(s->medicos_sistema, s->nMedicosSistema);
    desaloca_array_atores(s->secretarios_sistema, s->nSecretariosSistema);
    desaloca_array_atores(s->pacientes_sistema, s->nPacientesSistema);
    desaloca_array_consultas(s->consultas, s->nConsultasSistema);
    desaloca_lesoes(s->lesoes, s->nLesoes);

    free(s);
}

void roda_sistema(tSistema *s)
{
    while (!s->encerra)
    {
        exibeMenu(s);
    }
}

void *telaDeAcesso(tSistema *s)
{
    tAtor *ator;
    if (s->medicos_sistema == NULL && s->secretarios_sistema == NULL)
    {
        cadastroSecretario(s);
        return (tAtor **)s->secretarios_sistema[0];
    }
    else
    {
        char login[20];
        char senha[20];

        printf("######################## ACESSO MINI-SADE ######################\n");
        printf("DIGITE SEU LOGIN:\n");
        printf("DIGITE SUA SENHA:\n");
        printf("###############################################################\n");

        scanf("%s", login);
        scanf("%s", senha);

        ator = verificaCredenciais(s->medicos_sistema, s->nMedicosSistema, s->secretarios_sistema, s->nSecretariosSistema, login, senha);
        if (ator != NULL)
        {
            return ator;
        }
        else
        {
            printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
            return telaDeAcesso(s);
        }
    }
}

void cadastroSecretario(tSistema *s)
{
    char nome[TAM_MAX_NOME];
    char cpf[TAM_CPF];
    char data[TAM_DATA];
    char telefone[TAM_TELEFONE];
    char genero[20];
    char nomeUsuario[20];
    char senha[20];
    char nivelAcesso[10];

    char confirmar;

    printf("#################### CADASTRO SECRETARIO #######################\n");
    printf("NOME COMPLETO:\n");
    printf("CPF:\n");
    printf("DATA DE NASCIMENTO:\n");
    printf("TELEFONE:\n");
    printf("GENERO:\n");
    printf("NOME DE USUARIO:\n");
    printf("SENHA:\n");
    printf("NIVEL DE ACESSO:\n");

    scanf("%s", nome);
    scanf("%s", cpf);
    scanf("%s", data);
    scanf("%s", telefone);
    scanf("%s", genero);
    scanf("%s", nomeUsuario);
    scanf("%s", senha);
    scanf("%s", nivelAcesso);

    s->nSecretariosSistema++;
    s->secretarios_sistema = (void **)realoca_array_atores(s->secretarios_sistema, s->nSecretariosSistema);
    ((tAtor **)s->secretarios_sistema)[s->nSecretariosSistema - 1] = cria_ator(nome, cpf, data, telefone, Secretario, genero, cria_secretario(nomeUsuario, senha, nivelAcesso), desaloca_secretario, retornaSenhaSecretario);

    atualizaBdAtor(((tAtor **)s->secretarios_sistema)[s->nSecretariosSistema - 1], s->caminho_bd, "secretarios.bin");

    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("###############################################################\n");

    scanf("%c", &confirmar);
}

void cadastroMedico(tSistema *s)
{
    char nome[TAM_MAX_NOME];
    char cpf[TAM_CPF];
    char data[TAM_DATA];
    char telefone[TAM_TELEFONE];
    char genero[20];
    char crm[TAM_CRM];
    char nomeUsuario[20];
    char senha[20];

    char confirmar;

    printf("#################### CADASTRO MEDICO #######################\n");
    printf("NOME COMPLETO:\n");
    printf("CPF:\n");
    printf("DATA DE NASCIMENTO:\n");
    printf("TELEFONE:\n");
    printf("GENERO:\n");
    printf("CRM:\n");
    printf("NOME DE USUARIO:\n");
    printf("SENHA:\n");

    scanf("%s", nome);
    scanf("%s", cpf);
    scanf("%s", data);
    scanf("%s", telefone);
    scanf("%s", genero);
    scanf("%s", nomeUsuario);
    scanf("%s", senha);
    scanf("%s", crm);

    s->nMedicosSistema++;
    s->medicos_sistema = (void **)realoca_array_atores(s->medicos_sistema, s->nMedicosSistema);
    ((tAtor **)s->medicos_sistema)[s->nMedicosSistema - 1] = cria_ator(nome, cpf, data, telefone, Medico, genero, cria_medico(crm, nomeUsuario, senha), desaloca_medico, retornaSenhaMedico);

    atualizaBdAtor(((tAtor **)s->medicos_sistema)[s->nMedicosSistema - 1], s->caminho_bd, "medicos.bin");

    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("###############################################################\n");

    scanf("%c", &confirmar);
}

void cadastroPaciente(tSistema *s)
{
    char nome[TAM_MAX_NOME];
    char cpf[TAM_CPF];
    char data[TAM_DATA];
    char telefone[TAM_TELEFONE];
    char genero[20];

    char confirmar;

    printf("#################### CADASTRO PACIENTE #######################\n");
    printf("NOME COMPLETO:\n");
    printf("CPF:\n");
    printf("DATA DE NASCIMENTO:\n");
    printf("TELEFONE:\n");
    printf("GENERO:\n");

    scanf("%s", nome);
    scanf("%s", cpf);
    scanf("%s", data);
    scanf("%s", telefone);
    scanf("%s", genero);

    s->nPacientesSistema++;
    s->pacientes_sistema = (void **)realoca_array_atores(s->medicos_sistema, s->nMedicosSistema);
    ((tAtor **)s->pacientes_sistema)[s->nPacientesSistema - 1] = cria_ator(nome, cpf, data, telefone, Paciente, genero, cria_paciente(), desaloca_paciente, NULL);

    atualizaBdAtor(((tAtor **)s->pacientes_sistema)[s->nPacientesSistema - 1], s->caminho_bd, "pacientes.bin");

    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("###############################################################\n");

    scanf("%c", &confirmar);
}

void exibeMenu(tSistema *s)
{
    int opcao;

    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");

    if (retornaTipoAtor(s->usuario) == Secretario)
    {
        if (retornaNivelAcesso(retornaAtorEspecifico(s->usuario)) == ADMIN)
        {
            printf("(1) CADASTRAR SECRETARIO\n");
            printf("(2) CADASTRAR MEDICO\n");
            printf("(3) CADASTRAR PACIENTE\n");
            printf("(4) REALIZAR CONSULTA\n");
            printf("(5) BUSCAR PACIENTES\n");
            printf("(6) RELATORIO GERAL\n");
            printf("(7) FILA DE IMPRESSAO\n");
            printf("(8) FINALIZAR O PROGRAMA\n");
            printf("###############################################################\n");
        }
        if (retornaNivelAcesso(retornaAtorEspecifico(s->usuario)) == USER)
        {
            printf("(2) CADASTRAR MEDICO\n");
            printf("(3) CADASTRAR PACIENTE\n");
            printf("(5) BUSCAR PACIENTES\n");
            printf("(6) RELATORIO GERAL\n");
            printf("(7) FILA DE IMPRESSAO\n");
            printf("(8) FINALIZAR O PROGRAMA\n");
            printf("###############################################################\n");
        }
    }

    if (retornaTipoAtor(s->usuario) == Medico)
    {
        printf("(4) REALIZAR CONSULTA\n");
        printf("(5) BUSCAR PACIENTES\n");
        printf("(6) RELATORIO GERAL\n");
        printf("(7) FILA DE IMPRESSAO\n");
        printf("(8) FINALIZAR O PROGRAMA\n");
        printf("###############################################################\n");
    }

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        cadastroSecretario(s);
        break;

    case 2:
        cadastroMedico(s);
        break;

    case 3:
        /* code */
        break;

    case 4:
        /* code */
        break;

    case 5:
        /* code */
        break;

    case 6:
        /* code */
        break;

    case 7:
        /* code */
        break;

    case 8:
        s->encerra = 1;
        break;

    default:
        break;
    }
}