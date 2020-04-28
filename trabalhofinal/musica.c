#include <stdlib.h>
#include <string.h>

#include "musica.h"

#define MAXNOME   100
#define MAXGENERO 30

struct _musica{
    char nome[MAXNOME];
    char interprete[MAXNOME];
    char genero[MAXGENERO];
    int  anoLancamento;
    int duracao;
}
