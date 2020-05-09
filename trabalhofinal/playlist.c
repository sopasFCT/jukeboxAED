#include <stdlib.h>
#include <string.h>

#include "dicionario.h"
#include "musica.h"
#include "playlist.h"

#define MAXNOME 100

struct _playlist{
    sequencia  musicas;
    char       nomePlaylist[MAXNOME];
    int        numeroMusicas; //numero de musicas que estao na playlist
    int        duracaoPlaylist; //numero de segundos das musicas da playlist
    int        numeroVezesTocada; //numero de vezes que a playlist foi tocada
};

playlist criaPlaylist(int numeroMusicasLimite, char *nome){
    playlist p;
    p = (playlist)malloc(sizeof(struct _playlist))
    if(p == NULL)
        return NULL;
    p -> musicas = criaSequencia(numeroMusicasLimite);
    p -> numeroMusicas = 0;
    p -> duracaoPlaylist = 0;
    p -> numeroVezesTocada = 0;
    return p;
}
