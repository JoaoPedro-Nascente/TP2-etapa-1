#include <stdio.h>

#include "tDocumento.h"

struct tDocumento
{
    /* data */
};

tDocumento *criaDocumento(void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                          func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                          func_ptr_desaloca desaloca);

void desalocaDocumento(tDocumento *doc);

void imprimeNaTelaDocumento(tDocumento *doc);

void imprimeEmArquivoDocumento(tDocumento *doc, char *path);