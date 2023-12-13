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
#include "tFila.h"
#include "tBusca.h"
#include "tReceita.h"
#include "tBiopsia.h"
#include "tBusca.h"
#include "tRelatorioGeral.h"
#include "tEncaminhamento.h"

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
    tFila *fila;
};

void *telaDeAcesso(tSistema *s);
void exibeMenu(tSistema *s);
void cadastroSecretario(tSistema *s);
void cadastroMedico(tSistema *s);
void cadastroPaciente(tSistema *s);
void consulta(tSistema *s);
int exibeMenuPosConsulta(tSistema *s, tAtor *paciente, char *data);
void buscaPaciente(tSistema *s);
void cadastraLesao(tSistema *s);
void executaFila(tSistema *s);
void geraRelatorioGeral(tSistema *s);
void geraReceitaMedica(tSistema *s, tAtor *paciente, char *data);
void geraBiopsia(tSistema *s, tAtor *paciente, char *data, tLesao **lesoes, int nLesoes);
void geraEncaminhamento(tSistema *s, tAtor *paciente, char *data);

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

    s->fila = criaFila();

    return s;
}

void desaloca_sistema(tSistema *s)
{
    desaloca_array_atores(s->medicos_sistema, s->nMedicosSistema);
    desaloca_array_atores(s->secretarios_sistema, s->nSecretariosSistema);
    desaloca_array_atores(s->pacientes_sistema, s->nPacientesSistema);
    desaloca_array_consultas(s->consultas, s->nConsultasSistema);
    desaloca_lesoes(s->lesoes, s->nLesoes);
    desalocaFila(s->fila);

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

void consulta(tSistema *s)
{
    char cpf[TAM_CPF];
    tAtor *paciente;
    char data[TAM_DATA];
    int possui_diabetes;
    int fuma;
    int possui_alergia;
    int possui_historico_cancer;
    char tipoPele[3];
    int encerra = 0;

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE:\n");
    printf("############################################################\n");

    scanf("%s", cpf);

    paciente = retorna_ator_cpf(s->pacientes_sistema, s->nPacientesSistema, cpf);
    if (paciente != NULL)
    {
        printf("#################### CONSULTA MEDICA #######################\n");
        printf("CPF DO PACIENTE: %s\n", retornaCpfAtor(paciente));
        printf("- - -\n");
        printf("- NOME: %s\n", retornaNomeAtor(paciente));
        printf("- DATA DE NASCIMENTO: %s\n", retornaDataNascimentoAtor(paciente));
        printf("- - -\n");
        printf("\n");
        printf("DATA DA CONSULTA :\n");
        printf("POSSUI DIABETES :\n");
        printf("FUMANTE :\n");
        printf("ALEGIA A MEDICAMENTO :\n");
        printf("HISTORICO DE CANCER :\n");
        printf("TIPO DE PELE :\n");
        printf("############################################################\n");

        scanf("%s", data);
        scanf("%d", &possui_diabetes);
        scanf("%d", &fuma);
        scanf("%d", &possui_alergia);
        scanf("%d", &possui_historico_cancer);
        scanf("%s", tipoPele);

        consultaPaciente(retornaAtorEspecifico(paciente), possui_diabetes, fuma, possui_alergia, possui_historico_cancer, tipoPele);

        s->nConsultasSistema++;
        s->consultas = (void **)realoca_array_consultas(s->consultas, s->nConsultasSistema);
        if (retornaTipoAtor(s->usuario) == Medico)
            ((tConsulta **)s->consultas)[s->nConsultasSistema - 1] = cria_consulta(retornaNomeAtor(paciente), retornaCpfAtor(paciente), retornaNomeAtor((void *)s->usuario), retornaCrmMedico(retornaAtorEspecifico(s->usuario)), data);
        if (retornaTipoAtor(s->usuario) == Secretario)
            ((tConsulta **)s->consultas)[s->nConsultasSistema - 1] = cria_consulta(retornaNomeAtor(paciente), retornaCpfAtor(paciente), "", "", data);
        atualizaBdConsultas(((tConsulta **)s->consultas)[s->nConsultasSistema - 1], s->caminho_bd, "consultas.bin");

        while (!encerra)
        {
            exibeMenuPosConsulta(s, paciente, data);
        }
    }
    else
    {
        printf("#################### CONSULTA MEDICA #######################\n");
        printf("CPF DO PACIENTE: %s\n", cpf);
        printf("PACIENTE SEM CADASTRO\n");
        printf("\n");
    }

    printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("############################################################\n");
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
        cadastroPaciente(s);
        break;

    case 4:
        consulta(s);
        break;

    case 5:
        buscaPaciente(s);
        break;

    case 6:
        geraRelatorioGeral(s);
        break;

    case 7:
        executaFila(s);
        break;

    case 8:
        s->encerra = 1;
        break;

    default:
        break;
    }
}

int exibeMenuPosConsulta(tSistema *s, tAtor *paciente, char *data)
{
    int opcao;
    int nLesoesCadastradas;
    void **lesoesCirurgia = NULL;
    int nLesoesCirurgia = 0;

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("(1) CADASTRAR LESAO\n");
    printf("(2) GERAR RECEITA MEDICA\n");
    printf("(3) SOLICITACAO DE BIOPSIA\n");
    printf("(4) ENCAMINHAMENTO\n");
    printf("(5) ENCERRAR CONSULTA\n");
    printf("############################################################\n");

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        cadastraLesao(s);
        nLesoesCadastradas++;
        break;

    case 2:
        geraReceitaMedica(s, paciente, data);
        break;

    case 3:
        for (int i = s->nLesoes - nLesoesCadastradas; i < s->nLesoes; i++)
        {
            if (foiCirurgia(((tLesao **)s->lesoes)[i]))
            {
                nLesoesCirurgia++;
                lesoesCirurgia = (void **)realloc(lesoesCirurgia, nLesoesCirurgia);
                ((tLesao **)lesoesCirurgia)[nLesoesCirurgia - 1] = ((tLesao **)s->lesoes)[i];
            }
        }
        geraBiopsia(s, paciente, data, (tLesao **)lesoesCirurgia, nLesoesCirurgia);
        break;

    case 4:
        geraEncaminhamento(s, paciente, data);
        break;

    case 5:
        return 1;
        break;

    default:
        break;
    }
}

void buscaPaciente(tSistema *s)
{
    char nome[100];
    int nPacientesNome = 0;
    tAtor **pacientes = NULL;
    tBusca *busca;
    char confirmar;
    int opcao;
    char nomeAtor[100];

    printf("#################### BUSCAR PACIENTES #######################\n");
    printf("NOME DO PACIENTE:\n");
    printf("############################################################");
    scanf("%s", nome);

    for (int i = 0; i < s->nPacientesSistema; i++)
    {
        strcpy(nomeAtor, retornaNomeAtor((void *)(((tAtor **)s->pacientes_sistema)[i])));
        if (strcmp(nome, nomeAtor) == 0)
        {
            nPacientesNome++;

            pacientes = realoca_array_atores((void **)pacientes, nPacientesNome);
            pacientes[nPacientesNome - 1] = ((tAtor **)s->pacientes_sistema)[i];
        }
    }

    busca = criaBusca(pacientes, nPacientesNome);

    if (nPacientesNome == 0)
    {
        printf("#################### BUSCAR PACIENTES #######################\n");
        printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");

        scanf("%c", &confirmar);
        desalocaBusca(busca);
        free(pacientes);
    }
    else
    {
        printf("#################### BUSCAR PACIENTES #######################\n");
        printf("PACIENTES ENCONTRADOS:\n");
        imprimeNaTelaBusca(busca);
        printf("\n");

        printf("SELECIONE UMA OPÇÃO:\n");
        printf("(1) ENVIAR LISTA PARA IMPRESSAO\n");
        printf("(2) RETORNAR AO MENU PRINCIPAL\n");
        printf("############################################################\n");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            printf("#################### BUSCAR PACIENTES #######################\n");
            printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
            printf("############################################################\n");
            insereDocumentoFila(s->fila, busca, imprimeNaTelaBusca, imprimeEmArquivoBusca, desalocaBusca);
        }
        if (opcao == 2)
        {
            desalocaBusca(busca);
        }
    }
}

void executaFila(tSistema *s)
{
    int opcao;

    printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("(1) EXECUTAR FILA DE IMPRESSAO\n");
    printf("(2) RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        imprimeFila(s->fila, s->caminho_saida);
    }
}

void geraRelatorioGeral(tSistema *s)
{
    tRelatorioGeral *relatorio;
    int totalPacientes = 0;
    int mediaIdadePacientes = 0;
    int qtdPacientesF = 0;
    int qtdPacientesM = 0;
    int qtdPacientesO = 0;
    int tamMedioLesoes = 0;
    int totalLesoes = 0;
    int totalCirurgias = 0;
    int totalCrioterapias = 0;
    int opcao;

    totalPacientes = s->nPacientesSistema;
    totalLesoes = s->nLesoes;

    for (int i = 0; i < totalPacientes; i++)
    {
        if (retornaGeneroAtor(((tAtor **)s->pacientes_sistema)[i]) == Masculino)
        {
            qtdPacientesM++;
        }
        if (retornaGeneroAtor(((tAtor **)s->pacientes_sistema)[i]) == Feminino)
        {
            qtdPacientesF++;
        }
        if (retornaGeneroAtor(((tAtor **)s->pacientes_sistema)[i]) == Outros)
        {
            qtdPacientesO++;
        }

        mediaIdadePacientes += retornaIdadeAtor(((tAtor **)s->pacientes_sistema)[i]);
    }
    mediaIdadePacientes /= totalPacientes;

    for (int i = 0; i < totalLesoes; i++)
    {
        tamMedioLesoes += retornaTamanhoLesao(((tLesao **)s->lesoes)[i]);

        if (foiCirurgia(((tLesao **)s->lesoes)[i]))
            totalCirurgias++;
        if (foiCrioterapia(((tLesao **)s->lesoes)[i]))
            totalCrioterapias++;
    }

    relatorio = criaRelatorio(totalPacientes, mediaIdadePacientes, qtdPacientesF, qtdPacientesM, qtdPacientesO, tamMedioLesoes, totalLesoes, totalCirurgias, totalCrioterapias);
    printf("#################### RELATORIO GERAL #######################\n");
    imprimeNaTelaRelatorio(relatorio);

    printf("\n");
    printf("SELECIONE UMA OPÇÃO:\n");
    printf("(1) ENVIAR PARA IMPRESSAO\n");
    printf("(2) RETORNAR AO MENU PRINCIPAL\n");
    printf("############################################################\n");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        printf("#################### RELATORIO GERAL #######################\n");
        printf("RELATÓRIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");
        insereDocumentoFila(s->fila, relatorio, imprimeNaTelaRelatorio, imprimeEmArquivoRelatorio, desalocaRelatorio);
    }
    if (opcao == 2)
    {
        desalocaRelatorio(relatorio);
    }
}

void cadastraLesao(tSistema *s)
{
    char rotulo[TAM_MAX_ROTULO];
    char nRotulo[4];
    char diagnostico[TAM_MAX_DIAGNOSTICO];
    char regiao_corpo[TAM_MAX_REGIAO_CORPO];
    int tamanho;
    int cirurgia;
    int crioterapia;
    char confirmar;

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CADASTRO DE LESAO:\n");
    printf("DIAGNOSTICO CLINICO:\n");
    printf("REGIAO DO CORPO:\n");
    printf("TAMANHO:\n");
    printf("ENVIAR PARA CIRURGIA:\n");
    printf("ENVIAR PARA CRIOTERAPIA:\n");
    scanf("%s", diagnostico);
    scanf("%s", regiao_corpo);
    scanf("%d", &tamanho);
    scanf("%d", &cirurgia);
    scanf("%s", &crioterapia);

    s->nLesoes++;
    s->lesoes = (void **)realloc(s->lesoes, s->nLesoes);
    strcpy(rotulo, "L");
    itoa(s->nLesoes, nRotulo, 10);
    strcat(rotulo, nRotulo);

    ((tLesao **)s->lesoes)[s->nLesoes - 1] = cria_lesao(rotulo, diagnostico, regiao_corpo, tamanho, cirurgia, crioterapia);

    printf("\n");
    printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%c", &confirmar);
}

void geraReceitaMedica(tSistema *s, tAtor *paciente, char *data)
{
    char tipoUso[7];
    eTipoUso tpUso;
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    int quantidade;
    char instrucoesUso[MAX_TAM_INSTRUCOES];
    char confirma;

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("RECEITA MEDICA:\n");
    printf("TIPO DE USO:\n");
    printf("NOME DO MEDICAMENTO:\n");
    printf("TIPO DE MEDICAMENTO:\n");
    printf("QUANTIDADE:\n");
    printf("INSTRUÇÕES DE USO:\n");

    scanf("%s", tipoUso);
    scanf("%s", nomeMedicamento);
    scanf("%s", tipoMedicamento);
    scanf("%d", &quantidade);
    scanf("%s", instrucoesUso);

    if (strcmp(tipoUso, "TOPICO") == 0)
        tpUso = TOPICO;
    if (strcmp(tipoUso, "ORAL") == 0)
        tpUso = ORAL;

    if (retornaTipoAtor(s->usuario) == Medico)
        insereDocumentoFila(s->fila, criaReceita(retornaNomeAtor(paciente), tpUso, nomeMedicamento, tipoMedicamento, instrucoesUso, quantidade, retornaNomeAtor(s->usuario), retornaCrmMedico(retornaAtorEspecifico(s->usuario)), data), imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
    if (retornaTipoAtor(s->usuario) == Secretario)
        insereDocumentoFila(s->fila, criaReceita(retornaNomeAtor(paciente), tpUso, nomeMedicamento, tipoMedicamento, instrucoesUso, quantidade, "", "", data), imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);

    printf("\n");
    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%c", confirma);
}

void geraBiopsia(tSistema *s, tAtor *paciente, char *data, tLesao **lesoes, int nLesoes)
{
    char confirma;

    if (nLesoes > 0)
    {
        if (retornaTipoAtor(s->usuario) == Medico)
            insereDocumentoFila(s->fila, criaBiopsia(retornaNomeAtor(paciente), retornaCpfAtor(paciente), lesoes, retornaNomeAtor(s->usuario), retornaCrmMedico(retornaAtorEspecifico(s->usuario)), data, nLesoes), imprimeNaTelaBiopsia, imprimeEmArquivoBiopsia, desalocaBiopsia);
        if (retornaTipoAtor(s->usuario) == Secretario)
            insereDocumentoFila(s->fila, criaBiopsia(retornaNomeAtor(paciente), retornaCpfAtor(paciente), lesoes, "", "", data, nLesoes), imprimeNaTelaBiopsia, imprimeEmArquivoBiopsia, desalocaBiopsia);

        printf("#################### CONSULTA MEDICA #######################\n");
        printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");

        scanf("%c", &confirma);
    }
    else
    {
        printf("#################### CONSULTA MEDICA #######################\n");
        printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");
        free(lesoes);

        scanf("%c", &confirma);
    }
}

void geraEncaminhamento(tSistema *s, tAtor *paciente, char *data)
{
    char especialidadeEncaminhada[50];
    char motivo[300];
    char confirma;

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ENCAMINHAMENTO:\n");
    printf("ESPECIALIDADE ENCAMINHADA:\n");
    printf("MOTIVO:\n");

    scanf("%s", especialidadeEncaminhada);
    scanf("%s", motivo);

    if (retornaTipoAtor(s->usuario) == Medico)
        insereDocumentoFila(s->fila, criaEncaminhamento(retornaNomeAtor(paciente), retornaCpfAtor(paciente), especialidadeEncaminhada, motivo, retornaNomeAtor(s->usuario), retornaCrmMedico(retornaAtorEspecifico(s->usuario)), data), imprimeNaTelaEncaminhamento, imprimeEmArquivoBiopsia, desalocaEncaminhamento);
    if (retornaTipoAtor(s->usuario) == Secretario)
        insereDocumentoFila(s->fila, criaEncaminhamento(retornaNomeAtor(paciente), retornaCpfAtor(paciente), especialidadeEncaminhada, motivo, "", "", data), imprimeNaTelaEncaminhamento, imprimeEmArquivoBiopsia, desalocaEncaminhamento);

    printf("\n");
    printf("ENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%c", confirma);
}