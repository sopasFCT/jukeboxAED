#include <stdio.h>
#include <string.h>
void trataComando(char *linha, char* comando);
int trataSaida(char *linha, char *comando);
void uploadMusica(char *linha);
void deleteMusica(char *linha);
int main(){
    char linha[30], cmd;
    printf(">");
    fgets(linha,30,stdin);
    cmd = linha[0];
    while(trataSaida(linha, "quit")){
        switch(cmd){
            case 'u'   : trataComando(linha, "upload"); break;
            case 'd'   : trataComando(linha, "delete"); break;
            //case "view"     : viewMusica(linha);
            //case "music"    : listaMusica(linha);
            //case "create"   : criaPlaylist(linha);
            //case "play"     : tocaPlaylist(linha);
            //case "playlist" : listaPlaylist(linha);
            //case "modify"   : modificarPlaylist(linha);
            //case "destroy"  : destroiPlaylist(linha);
            default    : printf("Comando invalido\n"); 
        }
        printf(">");
		fgets(linha,30,stdin);
		cmd = linha[0];
    }
    printf("Jukebox encerrada.\n");
}

void trataComando(char *linha, char* comando){
    char* newcmd;
    int i;
    for(i = 0; i < 30; i++){
        if(linha[i] != ' ')
            newcmd[i] = linha[i];
        else
            break;
    }
    if(!strcmp(newcmd, comando))
        printf("É igual filho, deu certo.\n");
    else
        printf("Comando invalido.\n");
}

int trataSaida(char *linha, char *comando){
    int i;
    char *newcmd;
    for(i = 0; i < 30; i++){
        if(linha[i] != ' ')
            newcmd[i] = linha[i];
        else
            break;
    }
    if(!strcmp(newcmd, "quit"))
        return 0;
    else
        return 1;
}

void uploadMusica(char *linha){
    printf("upload %s", linha);
}

void deleteMusica(char *linha){
    printf("delete %s", linha);
}

