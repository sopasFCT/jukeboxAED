#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPLAYLISTS 1000
#define MAXMUSICAS   3000

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
    if(adicionaElemDicOrdenado(j -> musicas, nomeMusica, m))//tag
        return 1;
    else //seria engracado eu destruir aqui m
        return 0;
}

//esta funcao tambem adiciona a playlist p a sequencia criada de playlists
playlist criaPlaylistJukebox(jukebox j, char* nomePlaylist, int numeroMusicasLimite){
    playlist p;
    p = criaPlaylist(numeroMusicasLimite, nomePlaylist);
    if(p == NULL)
        return NULL;
    if(adicionaElemDicionario(j -> playlists, nomePlaylist, p))
        return p;
    else
        return NULL;
}

int existePlaylistJukebox(jukebox j, char* nomePlaylist){
    playlist p;
    iterador myIt = criaIteradorNomesPlaylists(j);
    while(temSeguinteIterador(myIt)){
        p = (playlist)seguinteIterador(myIt);
        if(!strcmp(retornaNomePlaylist(p), nomePlaylist))
                return 1;
    }
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

int destruirPlaylistJukebox(jukebox j, char* nomePlaylist){ //ver se precisa receber playlist parametro
    playlist p = removeElemDicionario(j -> playlists, nomePlaylist);
    if(p == NULL)
        return 0;
    destroiPlaylist(p);
    return 1;
}

void destroiJukebox(jukebox j){
    free(j);
}

void destroiPlaylistsEMusicas(jukebox j){
    destroiDicEElems(j -> playlists, (void*)destroiGenPlaylist);
    destroiDicOrdEElems(j -> musicas, (void*)destroiGenMusica);
}

