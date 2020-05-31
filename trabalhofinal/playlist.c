#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "iterador.h"
#include "sequencia.h"
#include "musica.h"
#include "playlist.h"


#define MAXNOME 100

struct _playlist{
    sequencia  musicas;
    char       nomePlaylist[MAXNOME];
    int        duracaoPlaylist;
    int        numeroVezesTocada;
    int        capacidade;
};

playlist criaPlaylist(int numeroMusicasLimite, char *nome){
    playlist p;
    p = (playlist)malloc(sizeof(struct _playlist));
    if(p == NULL)
        return NULL;
    strcpy(p -> nomePlaylist, nome); //add
    p -> musicas = criaSequencia(numeroMusicasLimite);
    //p -> numeroMusicas = 0;
    p -> duracaoPlaylist = 0;
    p -> numeroVezesTocada = 0;
    p -> capacidade = numeroMusicasLimite;
    return p;
}

char* retornaNomePlaylist(playlist p){
    return(p -> nomePlaylist);
}

int retornaNumeroMusicasPlaylist(playlist p){
    return(tamanhoSequencia(p -> musicas));
}

int retornaDuracaoPlaylist(playlist p){
    return(p -> duracaoPlaylist);
}

int retornaNumeroVezesTocada(playlist p){
    return(p -> numeroVezesTocada);
}

int existeMusicaPlaylist(playlist p, musica m){
    iterador myIt = criaIteradorMusicasPlaylist(p);
    musica musicaSequencia;
    while(temSeguinteIterador(myIt)){
        musicaSequencia = (musica)seguinteIterador(myIt);
        if(!strcmp(nomeMusica(musicaSequencia), nomeMusica(m)))
            return 1;
    }
    return 0;
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

int devolvePosMusicaPlaylist(playlist p, musica m){
    int pos = 1;
    musica mDevolve;
    iterador myIt = criaIteradorMusicasPlaylist(p);
    while(temSeguinteIterador(myIt)){
        mDevolve = seguinteIterador(myIt);
        if(!strcmp(nomeMusica(mDevolve), nomeMusica(m)))
            return pos;
        pos++;
    }
    destroiIterador(myIt);
    return (-1);
}

char* removerMusicaPlaylist(playlist p, int pos){
    musica m;
    if(pos > tamanhoSequencia(p -> musicas))
        return NULL;
    m = removePosSequencia(p -> musicas, pos);
    if(m == NULL)
        return NULL;
    if(!existeMusicaPlaylist(p, m))
        decrementaNumeroPlaylistsPresente(m);
    p -> duracaoPlaylist = p -> duracaoPlaylist - duracaoMusica(m);
    return(nomeMusica(m));
}

int adicionaMusicaPlaylist(playlist p, musica m, int pos, char* nomeMusica, int tempoMaximo){
    int tempoCorrentePlaylist;
    if(tamanhoSequencia(p -> musicas) + 1 > p -> capacidade)  //se a alteracao aqui altera
        return -1;
    tempoCorrentePlaylist = p -> duracaoPlaylist + duracaoMusica(m);
    if(tempoCorrentePlaylist > tempoMaximo){
        tempoCorrentePlaylist = p -> duracaoPlaylist - duracaoMusica(m);
        return 1; //nao consegue adicionar pois o tempo da playlist excede o tempo maximo permitido
    }
    if(!existeMusicaPlaylist(p, m))
        incrementaNumeroPlaylistsPresente(m);
    p -> duracaoPlaylist = tempoCorrentePlaylist;
    adicionaPosSequencia(p -> musicas, m, pos);
    return 2;//nao houve problema
}

int verificaCondicoesPlaylist(playlist p, int pos){
    if(pos > tamanhoSequencia(p -> musicas) + 2)
        return 0; //posicao nao existe
    return 1;
}

iterador criaIteradorMusicasPlaylist(playlist p){
    iterador myIt = iteradorSequencia(p -> musicas);
    return(myIt);
}

void destroiPlaylist(playlist p){
    free((playlist)p);
}

void destroiPlaylistEMusicas(playlist p){
    destroiSeqElems(p -> musicas, (void*) destroiGenMusica);
    free(p);
}

void destroiGenPlaylist(void *p){
    free((void *)p);
}
