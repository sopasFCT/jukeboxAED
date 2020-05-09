#include <stdlib.h>
#include <string.h>

#define MAXDICIONARIO 200

#include "dicOrdenado.h"
#include "musica.h"
#include "playlist.h"
#include "jukebox.h"

struct _jukebox{
    sequencia playlists;
    dicOrdenado musicas;
};

jukebox criaJukebox(int numeroMusicas){
    jukebox j = (jukebox)malloc(sizeof(struct _jukebox));
    if(j == NULL)
        return NULL;
    j -> playlists = (sequencia)criaSequencia(numeroMusicas);
    if(j -> playlists == NULL){
        free(j);
        return NULL;
    }
    j -> musicas = (dicOrdenado)criaDicOrdenado(MAXDICIONARIO, 1)
    if(j -> musicas == NULL){
        free(j);
        return NULL;
    }
    return j;
}

int novaMusicaJukebox(jukebox j, char *nomeMusica, char *interprete, char *genero, int anoLancamento, int duracao){
    musica m;
    m = criaMusica(nomeMusica, interprete, genero, anoLancamento, duracao);
    if(adicionaElemDicOrdenado(j -> musicas, nomeMusica, m))//tag
        return 1;
    else
        return 0;
}

void apagarMusicaJukebox(jukebox j, char *nomeMusica){
    musica m = elementoDicOrdenado(p -> musicas, nomeMusica);
    if(existeElemDicOrdenado(p -> musicas, nomeMusica)){
        removeElemDicOrdenado(p -> musicas, nomeMusica);
        return 1;
    }
    else
        return 0;
    destroiMusica(m);
}

musica devolveMusicaJukebox(jukebox j, char *nomeMusica){
    musica m = elementoDicOrdenado(p -> musicas, nomeMusica);
    if (m == NULL)
        return NULL;
}
