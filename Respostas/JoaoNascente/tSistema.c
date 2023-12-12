#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tSistema.h"
#include "tAtor.h"
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
};

tSistema *cria_sistema(char *caminho_saida)
{
    tSistema *s = (tSistema *)malloc(sizeof(tSistema));

    strcpy(s->caminho_saida, caminho_saida);

    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS:\n");
    printf("################################################\n");
    scanf("%s", s->caminho_bd);

    s->medicos_sistema = le_bd_ator(s->caminho_bd, "/medicos.bin", &s->nMedicosSistema);

    s->secretarios_sistema = le_bd_ator(s->caminho_bd, "/secretarios.bin", &s->nSecretariosSistema);

    s->pacientes_sistema = le_bd_ator(s->caminho_bd, "/pacientes.bin", &s->nPacientesSistema);

    s->consultas = le_bd_consulta(s->caminho_bd, "/consultas.bin", &s->nConsultasSistema);

    s->lesoes = le_bd_lesao(s->caminho_bd, "/lesoes.bin", &s->nLesoes);

    return s;
}

void desaloca_sistema(tSistema *s)
{
    desaloca_array_atores(s->medicos_sistema, s->nMedicosSistema);
    desaloca_array_atores(s->secretarios_sistema, s->nSecretariosSistema);
    desaloca_array_atores(s->pacientes_sistema, s->nPacientesSistema);

    free(s);
}

void *telaDeAcesso(tSistema *s)
{
    printf("");
    printf("");
    printf("");
}

int verificaLogin(char *login, char *senha)
{
}