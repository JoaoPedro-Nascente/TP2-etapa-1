#include <stdio.h>
#include <stdlib.h>

#include "tFila.h"

struct tFila
{
    tDocumento **documentos;
    int qtdDocumentos;
};

tFila *criaFila()
{
    tFila *fila = (tFila *)malloc(sizeof(tFila));

    fila->qtdDocumentos = 0;
    fila->documentos = NULL;

    return fila;
}

void desalocaFila(tFila *f)
{
    for (int i = 0; i < f->qtdDocumentos; i++)
    {
        desalocaDocumento(f->documentos[i]);
    }

    free(f->documentos);
    free(f);
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                         func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                         func_ptr_desaloca desaloca)
{
    f->qtdDocumentos++;
    f->documentos = (tDocumento **)realloc(f->documentos, sizeof(tDocumento *) * f->qtdDocumentos);

    f->documentos[f->qtdDocumentos - 1] = criaDocumento(dado, imprimeNaTela, ImprimeEmArquivo, desaloca);
}

int quantidadeDocumentosNaFila(tFila *f)
{
    return f->qtdDocumentos;
}

void imprimeFila(tFila *f, char *path)
{
    printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
    printf("EXECUTANDO FILA DE IMPRESSÃO:\n");
    for (int i = 0; i < f->qtdDocumentos; i++)
    {
        imprimeNaTelaDocumento(f->documentos[i]);
        printf("\n");
        imprimeEmArquivoDocumento(f->documentos[i], path);
    }
}