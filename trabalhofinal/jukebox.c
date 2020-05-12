#include <stdlib.h>
#include <string.h>

#define MAXDICIONARIO 200

#include "dicOrdenado.h"
#include "musica.h"
#include "playlist.h"
#include "jukebox.h"

struct _jukebox{
    dicionario playlists;
    dicOrdenado musicas;
};

jukebox criaJukebox(int numeroMusicas){
    jukebox j = (jukebox)malloc(sizeof(struct _jukebox));
    if(j == NULL)
        return NULL;
    j -> playlists = (dicionario)criaDicionario(numeroMusicas, 1);
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

//esta funcao tambem adiciona a playlist p a sequencia criada de playlists
playlist criaPlaylistJukebox(jukebox j, char* nomePlaylist, int numeroMusicasLimite){
    playlist p;
    iterador myIt = iteradorSequencia(j -> playlist);
    p = criaPlaylist(numeroMusicasLimite, nomePlaylist);
    if(adicionaElemDicionario(j -> playlist, nomePlaylist, p))
        return p;// se conseguiu adicionar da return da p
    else
        return NULL; //caso o return do adiciona seja 0 da return de null para a main

}

int existePlaylistJukebox(jukebox j, char* nomePlaylist){
    playlist p;
    iterador myIt = criaIteradorNomesPlaylists(j);
    while(temSeguinteIterador(myIt)){
        p = (playlist)seguinteIterador(myIt);
        if(!strcmp(retornaNomePlaylist(p), nomePlaylist))
                return 1; //da return de 1 caso ja exista esta playlist
    }
    return 0;
}

int existeMusicaJukebox(jukebox j, char* nomeMusica){
    if(existeElemDicOrdenado(j -> musicas, nomeMusica))
        return 1; //se existir safa 1
    return 0; //se existir nao safa
}

int numeroMusicasJukebox(jukebox j){
    return (tamanhoDicOrdenado(j -> musicas));
}

int numeroPlaylistsJukebox(jukebox j){
    return (tamanhoDicionario(j -> playlists));
}

musica retornaMusicaJukebox(jukebox j, char *nomeMusica){
    return(elementoDicOrdenado(j -> musicas, nomeMusica));
}

iterador criaIteradorNomesMusicas(jukebox j){
    iterador myIt = iteradorChaveDicOrdenado(j -> musicas);
    return(myIt);
}

iterador criaIteradorMusicas(jukebox j){
    iterador myIt = iteradorDicOrdenado(j -> musicas);
    return(myIt);
}

iterador criaIteradorNomesPlaylists(jukebox j){
    iterador myIt = iteradorChaveDicionario(j -> playlists);
    return(myIt);
}

iterador criaIteradorPlaylists(jukebox j){
    iterador myIt = iteradorDicionario(j -> playlists);
    return(myIt);
}

void apagarMusicaJukebox(jukebox j, char *nomeMusica){
    musica m = elementoDicOrdenado(j -> musicas, nomeMusica);
    if(existeElemDicOrdenado(j -> musicas, nomeMusica)){
        removeElemDicOrdenado(j -> musicas, nomeMusica);
        return 1;
    }
    else
        return 0;
    destroiMusica(m);
}

musica devolveMusicaJukebox(jukebox j, char *nomeMusica){
    musica m = elementoDicOrdenado(j -> musicas, nomeMusica);
    if (m == NULL)
        return NULL;
    return m;
}

playlist devolvePlaylistJukebox(jukebox j, char *nomePlaylist){
    playlist p = elementoDicionario(j -> playlists, nomePlaylist);
    if (p == NULL)
        return NULL;
    return p;
}
