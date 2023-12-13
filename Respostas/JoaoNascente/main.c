#include <stdio.h>

#include "tSistema.h"

int main(int argc, char *argv[])
{
    tSistema *s = cria_sistema(argv[1]);
    roda_sistema(s);
    desaloca_sistema(s);

    return 0;
}