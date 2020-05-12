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

char* retornaNomePlaylist(playlist p){
    return(p -> nomePlaylist);
}

int retornaNumeroMusicasPlaylist(playlist p){
    return(p -> numeroMusicas);
}

int retornaDuracaoPlaylist(playlist p){
    return(p -> duracaoPlaylist);
}

int retornaNumeroVezesTocada(playlist p){
    return(p -> numeroVezesTocada);
}
//se exceder tempo da return de 0
int adicionaMusicaPlaylist(playlist p, musica m, char *nomeMusica, int tempoDuracaoMaximoPlaylist){
    if(p -> duracaoPlaylist <= tempoDuracaoMaximoPlaylist){
        adicionaPosSequencia(p -> musicas, m, tamanhoSequencia(p -> musicas));
        p -> numeroMusicas = p -> numeroMusicas + 1; //ver futuramente se pode incrementar p++
    }
    else
        return 0;
    p -> duracaoPlaylist = p -> duracaoPlaylist + duracaoMusica(m);
    return 1;
}

void incrementarNumeroVezesTocada(playlist p){
    musica m;
    p -> numeroVezesTocada = p -> numeroVezesTocada + 1;
    iterador myIt = iteradorSequencia(p -> musicas);
    while(temSeguinteIterador(myIt))
    {
        m = (musica)seguinteIterador(myIt);
        incrementaNumeroVezesTocada(m);
    }
}

iterador criaIteradorMusicasPlaylist(playlist){
    iterador myIt = iteradorSequencia(p -> musicas);
    return(myIt);
}
