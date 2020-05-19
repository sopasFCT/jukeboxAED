#include <stdlib.h>
#include <string.h>

#include "iterador.h"
#include "sequencia.h"
#include "musica.h"
#include "playlist.h"


#define MAXNOME 100

struct _playlist{
    sequencia  musicas; //dicionario mudar
    char       nomePlaylist[MAXNOME];
    //int        numeroMusicas; //numero de musicas que estao na playlist
    int        duracaoPlaylist; //numero de segundos das musicas da playlist
    int        numeroVezesTocada; //numero de vezes que a playlist foi tocada
    int        capacidade;//numeroMusicasLimite declarado no inicio do programado
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

char* removerMusicaPlaylist(playlist p, int pos){
    musica m;
    m = removePosSequencia(p -> musicas, pos);
    if(m == NULL)
        return NULL;
    p -> duracaoPlaylist = p -> duracaoPlaylist - duracaoMusica(m);
    return(nomeMusica(m));
}

int adicionaMusicaPlaylist(playlist p, musica m, int pos, char* nomeMusica, int tempoMaximo){
    int tempoCorrentePlaylist;
    if(tamanhoSequencia(p -> musicas) + 1 > p -> capacidade) //se a alteracao aqui altera
        return 0; //nao consegue adicionar outra musica pois excede o numero musicas permitido
    tempoCorrentePlaylist = p -> duracaoPlaylist + duracaoMusica(m);
    if(tempoCorrentePlaylist > tempoMaximo)
        return 1; //nao consegue adicionar pois o tempo da playlist excede o tempo maximo permitido
    else{
        p -> duracaoPlaylist = tempoCorrentePlaylist;
        adicionaPosSequencia(p -> musicas, m, pos);
        return 2; //deu certo equipa
    }
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
