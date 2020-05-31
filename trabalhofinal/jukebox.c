#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPLAYLISTS 1000
#define MAXMUSICAS   3000
#define MAXNOME      100
#define MAXGENERO    30

#include "iterador.h"
#include "chaves.h"
#include "tuplo.h"
#include "dicOrdenado.h"
#include "dicionario.h"
#include "musica.h"
#include "playlist.h"
#include "jukebox.h"

struct _jukebox{
    dicionario playlists;
    dicOrdenado musicas;
};

jukebox criaJukebox(){
    jukebox j = (jukebox)malloc(sizeof(struct _jukebox));
    if(j == NULL)
        return NULL;
    j -> playlists = (dicionario)criaDicionario(MAXPLAYLISTS, 1);
    if(j -> playlists == NULL){
        free(j);
        return NULL;
    }
    j -> musicas = (dicOrdenado)criaDicOrdenado(MAXMUSICAS, 1);
    if(j -> musicas == NULL){
        free(j);
        return NULL;
    }
    return j;
}

int novaMusicaJukebox(jukebox j, char *nomeMusica, char *interprete, char *genero, int anoLancamento, int duracao){
    musica m;
    m = criaMusica(nomeMusica, interprete, genero, anoLancamento, duracao);
    if(m == NULL){
        free(m);
        return 0;
    }
    if(adicionaElemDicOrdenado(j -> musicas, nomeMusica, m))
        return 1;
    else{
        free(m);
        return 0;
    }
}

playlist criaPlaylistJukebox(jukebox j, char* nomePlaylist, int numeroMusicasLimite){
    playlist p;
    p = criaPlaylist(numeroMusicasLimite, nomePlaylist);
    if(p == NULL){
        free(p);
        return NULL;
    }
    if(adicionaElemDicionario(j -> playlists, nomePlaylist, p))
        return p;
    else{
        free(p);
        return NULL;
    }
}

int existePlaylistJukebox(jukebox j, char* nomePlaylist){
    playlist p;
    /*iterador myIt = criaIteradorNomesPlaylists(j);
    while(temSeguinteIterador(myIt)){
        p = (playlist)seguinteIterador(myIt);
        if(!strcmp(retornaNomePlaylist(p), nomePlaylist))
                return 1;
    }*/
    if(existeElemDicionario(j -> playlists, nomePlaylist))
        return 1;
    return 0;
}

int existeMusicaJukebox(jukebox j, char* nomeMusica){
    if(existeElemDicOrdenado(j -> musicas, nomeMusica))
        return 1;
    return 0;
}

int numeroMusicasJukebox(jukebox j){
    return (tamanhoDicOrdenado(j -> musicas));
}

int numeroPlaylistsJukebox(jukebox j){
    return (tamanhoDicionario(j -> playlists));
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

int apagarMusicaJukebox(jukebox j, char *nomeMusica){
    iterador myIt = criaIteradorPlaylists(j);
    playlist p;
    int pos;
    if(existeElemDicOrdenado(j -> musicas, nomeMusica)){
        musica m = removeElemDicOrdenado(j -> musicas, nomeMusica);
        if(m == NULL)
            return 0;
        while(temSeguinteIterador(myIt)){
            p = (playlist)seguinteIterador(myIt);
            while(existeMusicaPlaylist(p, m)){
                pos = devolvePosMusicaPlaylist(p, m);
                removerMusicaPlaylist(p, pos);
            }
        }
        destroiMusica(m);
        return 1;
    }
    else
        return 0;
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

int destruirPlaylistJukebox(jukebox j, char* nomePlaylist){
    playlist p = removeElemDicionario(j -> playlists, nomePlaylist);
    int i = 1;
    char *nome = removerMusicaPlaylist(p, i);
    if(p == NULL)
        return 0;
    while(nome != NULL)
        nome = removerMusicaPlaylist(p, i);
    destroiPlaylistEMusicas(p);
    return 1;
}

void destroiJukebox(jukebox j){
    free(j);
}

void destroiPlaylistsEMusicasJukebox(jukebox j){
    destroiDicEElems(j -> playlists, (void*)destroiGenPlaylist);
    destroiDicOrdEElems(j -> musicas, (void*)destroiGenMusica);
}

