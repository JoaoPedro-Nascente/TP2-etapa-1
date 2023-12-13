#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tBusca.h"

struct tBusca
{
    tAtor **pacientes;
    int nPacientes;
};

tBusca *criaBusca(tAtor **pacientes, int nPacientes)
{
    tBusca *busca = (tBusca *)malloc(sizeof(tBusca));

    busca->pacientes = pacientes;
    busca->nPacientes = nPacientes;

    return busca;
}

void desalocaBusca(void *dado)
{
    tBusca *busca = (tBusca *)dado;

    free(busca->pacientes);
    free(busca);
}

void imprimeNaTelaBusca(void *dado)
{
    tBusca *busca = (tBusca *)dado;
    for (int i = 0; i < busca->nPacientes; i++)
    {
        printf("%d - %s (%s)\n", i + 1, retornaNomeAtor(busca->pacientes[i]), retornaCpfAtor(busca->pacientes[i]));
    }
}

void imprimeEmArquivoBusca(void *dado, char *path)
{
    tBusca *busca = (tBusca *)dado;

    char caminho[1000];

    strcpy(caminho, path);
    strcat(caminho, "/lista_busca.txt");

    FILE *fp;
    fp = fopen(path, "a");

    for (int i = 0; i < busca->nPacientes; i++)
    {
        fprintf(fp, "%d - %s (%s)\n", i + 1, retornaNomeAtor(busca->pacientes[i]), retornaCpfAtor(busca->pacientes[i]));
    }

    fclose(fp);
}