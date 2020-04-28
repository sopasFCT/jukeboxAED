//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//TADs usados
#include "jukebox.h"
#include "playlist.h"
#include "musica.h"

//constantes
#define MAXLINHA 30

//prototipos
void interpretador(jukebox j);
void definirLimites(char *linha, int *numeroMusicas, int *tempoDuracao);
void uploadMusica(char *linha, );
void deleteMusica(char *linha, );
void viewMusica(char *linha, );
void listaMusica(char *linha, );
void criaPlaylist(char *linha, int numeroMusicas);
void tocaPlaylist(char *linha, );
void listaPlaylist(char *linha, );
void modificarPlaylist(char *linha, );
void destroiPlaylist(char *linha, );

int main(){
    jukebox jukeboxAED = criaJukebox();
    interpretador(jukeboxAED);
    destroiJukeboxPlaylistsMusicas(jukeboxAED);
    return 0;
}

void interpretador(jukebox j){
    //declaracao de variaveis
    int numeroMusicas, tempoDuracao;
    char linha[MAXLINHA], linhaInicio[MAXLINHA], cmd;
    //
    definirLimites(linhaInicio, &numeroMusicas, &tempoDuracao);
    fgets(linha,MAX_LINHA,stdin);
    sscanf(linha, "%s", cmd);
    while(strcmp(cmd, "fim")){
        switch(cmd){
            case "upload"   : uploadMusica(linha, );
            case "delete"   : deleteMusica(linha, );
            case "view"     : viewMusica(linha, );
            case "music"    : listaMusica(linha, );
            case "create"   : criaPlaylist(linha, numeroMusicas);
            case "play"     : tocaPlaylist(linha, );
            case "playlist" : listaPlaylist(linha, );
            case "modify"   : modificarPlaylist(linha, );
            case "destroy"  : destroiPlaylist(linha, );
        }
    }
    printf("Jukebox encerrada.\n");
}

void definirLimites(char *linhaInicio, int *numeroMusicas, int *tempoDuracao){
    if(sscanf(linhaInicio, "%d %d", numeroMusicas, tempoDuracao) == 2) //falta ver situacoes
        printf("Jukebox aberta.\n");
}

void uploadMusica(char *linha, ){

}

void deleteMusica(char *linha, ){

}

void viewMusica(char *linha, ){

}

void listaMusica(char *linha, ){

}

void criaPlaylist(char *linha, int numeroMusicas){

}

void tocaPlaylist(char *linha, ){

}

void listaPlaylist(char *linha, ){

}

void modificarPlaylist(char *linha, ){

}

void destroiPlaylist(char *linha, ){

}
