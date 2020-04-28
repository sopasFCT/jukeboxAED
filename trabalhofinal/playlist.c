#include <stdlib.h>
#include <string.h>

#include "dicionario.h"
#include "musica.h"
#include "playlist.h"

#define MAXNOME 100

struct _playlist{
    dicionario musicas;
    char       nomePlaylist[MAXNOME];
    int        duracaoPlaylist;
}
