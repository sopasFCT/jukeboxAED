#include <stdio.h>
#include <string.h>
void trataU(char *linha);
void trataD(char *linha);
int trataQuit(char *linha);
void uploadMusica(char *linha);
void deleteMusica(char *linha);
int main(){
    char linha[30], cmd;
    printf(">");
    fgets(linha,30,stdin);
    cmd = linha[0];
    while(cmd != 'q'){
        switch(cmd){
            case 'u'   : trataU(linha); break;
            case 'd'   : trataD(linha); break;
            //case "view"     : viewMusica(linha);
            //case "music"    : listaMusica(linha);
            //case "create"   : criaPlaylist(linha);
            //case "play"     : tocaPlaylist(linha);
            //case "playlist" : listaPlaylist(linha);
            //case "modify"   : modificarPlaylist(linha);
            //case "destroy"  : destroiPlaylist(linha);
            default    : "Comando invalido\n"; 
        }
        printf(">");
		fgets(linha,30,stdin);
		cmd = linha[0];
    }
    if(trataQuit(linha))
        printf("Jukebox encerrada.\n");
    else
        printf("Comando invalido.\n");
}

void trataU(char *linha){
    char* newcmd;
    int i;
    for(i = 0; i < 30; i++){
        if(linha[i] != ' ')
            newcmd[i] = linha[i];
        else
            break;
    }
    if(!strcmp(newcmd, "upload"))
        uploadMusica(linha);
    else{
        printf("Comando invalido.\n");
    }
}

void trataD(char *linha){
    char* newcmd;
    int i;
    for(i = 0; i < 30; i++){
        if(linha[i] != ' ')
            newcmd[i] = linha[i];
        else
            break;
    }
    if(!strcmp(newcmd, "delete"))
        deleteMusica(linha);
    else
        printf("Comando invalido.\n");
}

int trataQuit(char *linha)
{
    char* newcmd;
    int i;
    for(i = 0; i < 30; i++){
        if(linha[i] != ' ')
            newcmd[i] = linha[i];
        else
            break;
    }
    if(!strcmp(newcmd, "quit"))
        return 1;
    else
        return 0;
}

void uploadMusica(char *linha){
    printf("upload %s", linha);
}

void deleteMusica(char *linha){
    printf("delete %s", linha);
}

