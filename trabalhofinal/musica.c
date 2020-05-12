#include <stdlib.h>
#include <string.h>

#include "musica.h"

#define MAXNOME   100
#define MAXGENERO 30

struct _musica{
    char nomeMusica[MAXNOME]; //vai se procurar pelo nome
    char interpreteMusica[MAXNOME];
    char generoMusica[MAXGENERO];
    int  anoLancamentoMusica;
    int  duracaoMusica;
    int  numeroVezesTocada;
    int  numeroPlaylists; //numero de playlist que tem esta musica
};

musica criaMusica(char *nome, char *interprete, char *genero, int anoLancamento, int duracao){
    musica m;
    m = (musica)malloc(sizeof(struct _musica));
    if (m == NULL)
        return NULL;
    strcpy(m -> nomeMusica, nome);
    strcpy(m -> interpreteMusica, interprete);
    strcpy(m -> generoMusica, genero);
    m -> anoLancamentoMusica = anoLancamento;
    m -> duracaoMusica = duracao;
    m -> numeroVezesTocada = 0;
    m -> numeroPlaylists = 0;
    return m; //dar return para usar nas outras tads
}

char *nomeMusica(musica m){
    return(m -> nomeMusica);
}

char *interpreteMusica(musica m){
    return(m -> interpreteMusica);
}

char *generoMusica(musica m){
    return(m -> generoMusica);
}

int anoLancamentoMusica(musica m){
    return(m -> anoLancamentoMusica);
}

int duracaoMusica(musica m){
    return(m -> duracaoMusica);
}

int numeroVezesTocada(musica m){
    return(m -> numeroVezesTocada);
}

int numeroPlaylistsMusica(musica m){
    return(m -> numeroPlaylists);
}

void incrementaNumeroVezesTocada(musica m){
    m -> numeroVezesTocada = m -> numeroVezesTocada + 1;
}

void destroiMusica(musica m){
    free((musica)m);
}

void destroiGenMusica(void *m){
    free((void *)m);
}
