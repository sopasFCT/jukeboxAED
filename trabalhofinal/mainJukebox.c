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
#define MAXNOME   100
#define MAXGENERO 30

//prototipos
//funcoes menu
void interpretador(jukebox j);
void definirLimites(char *linha, int *numeroMusicas, int *tempoDuracao);
void trataComando(char *linha, char *comando);
int  trataSaida(char *linha, char *comando);
char *scanAteEnter(char *string);
char *apagarComandoLinha(char *linha);
//funcoes listagem
void totalEListagemMusicas(jukebox j);
void listaMusicasInterprete(jukebox j)
void listaMusicasGenero(jukebox j);
void listaMusicasEmMaisPlaylists(jukebox j);
void listaMusicasMaisTocadas(jukebox j);
void criaIteradorTop(jukebox j, int top);
//funcoes tadss
void uploadMusica(jukebox j, char *linha);
void deleteMusica(jukebox j, char *linha);
void viewMusica(jukebox j, char *linha);
void listaMusica(jukebox j, char *linha);
void criaPlaylist(jukebox j, char *linha, int numeroMusicas, int tempoDuracao);
void tocaPlaylist(char *linha);
void listaPlaylist(char *linha);
void modificarPlaylist(char *linha);
void destroiPlaylist(char *linha);

int main(){
    int numeroMusicas, tempoDuracao;
    definirLimites(linhaInicio, &numeroMusicas, &tempoDuracao);
    jukebox jukeboxAED = criaJukebox(numeroMusica);
    interpretador(jukeboxAED);
    destroiJukeboxPlaylistsMusicas(jukeboxAED);
    return 0;
}

void interpretador(jukebox j){
    //declaracao de variaveis
    char linha[MAXLINHA], linhaInicio[MAXLINHA], cmd;
    int decide;
    printf(">");
    fgets(linha,MAXLINHA,stdin);
    cmd = linha[0];
    while(trataSaida(linha)){
        switch(cmd){
            case 'u' : trataComando(linha, "upload"); break;
            case 'd' : decide = trataComandoIgual(linha, "delete", "destroy"); break;
            case 'v' : trataComando(linha, "view"); break;
            case 'm' : decide = trataComandoIgual(linha, "music", "modify"); break;
            case 'c' : trataComando(linha, "create"); break;
            case 'p' : decide = trataComandoIgual(linha, "play", "playlist"); break;
        }
        printf(">");
		fgets(linha,MAXLINHA,stdin);
		cmd = linha[0];
    }
    printf("Jukebox encerrada.\n");
}

void definirLimites(char *linhaInicio, int *numeroMusicas, int *tempoDuracao){
    if(sscanf(linhaInicio, "%d %d", numeroMusicas, tempoDuracao) == 2) //falta ver situacoes
        printf("Jukebox aberta.\n");
}

void trataComando(char *linha, char* comando){
    char* newcmd;
    int i;
    for(i = 0; i < MAXLINHA; i++){
        if(linha[i] != ' ')
            newcmd[i] = linha[i];
        else
            break;
    }
    if(!strcmp(newcmd, comando))
        printf("Olá comando %s.\n", comando);
        //fazer um switch. as iniciais ja foram verificadas. mudar a inicial do comando caso seja playlist para o seguinte codigo da tabela ascii
        //chamar a funcao conforme a inicial
        //ou fazer uma funcao so para os p
    else
        printf("Comando invalido.\n");
}

int trataComandoIgual(char *linha, char *comando1, char *comando2){
    int i;
    char *newcmd;
    for(i = 0; i < MAXLINHA; i++){
        if(linha[i] != ' ')
            newcmd[i] = linha[i];
        else
            break;
    }
    if(!strcmp(newcmd, comando1)){
        printf("Comando 1 - %s \n", comando1);
        return 1;
    }
    else if(!strcmp(newcmd, comando2)){
        printf("Comando 2 - %s \n", comando2);
        return 2;
    }
    else{
        printf("comando invalido\n");
        return 0;
    }
}

int trataSaida(char *linha){
    int i;
    char *newcmd;
    for(i = 0; i < MAXLINHA; i++){
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

char* scanAteEnter(char *string){
    int i=0;
    char *ch = malloc(sizeof(char) * strlen(string));
    while(1)
    {
         scanf("%c",&ch[i]);
         if(ch[i]=='\n')
             break;
         i++;
    }
    ch[strlen(ch) - 1] = '\0';
    return ch;
}

//da return do nome da musica
char *apagarComandoLinha(char *linha){
    int i;
    int j = 0;
    char *ch = malloc(sizeof(char) * strlen(linha));
    for(i = 0; linha[i] != ' ' || linha[i] != '\0'; i++){
    }
    i++;
    if(linha[i] == '\0')
    {
        return NULL;
    }
    else
    {
        i++;
        while(linha[i]!='\0')
        {
            ch[j] = linha[i];
            j++;
            i++;
        }
        return ch;
    }
}

void uploadMusica(jukebox j, char *linha){
    char nomeMusica[MAXNOME], interpreteMusica[MAXNOME], generoMusica[MAXGENERO];
    int anoLancamentoMusica, duracaoMusica;
    strcpy(nomeMusica, scanAteEnter(nomeMusica));
    strcpy(interpreteMusica, scanAteEnter(interpreteMusica);
    strcpy(generoMusica, scanAteEnter(generoMusica));
    scanf("%d",&anoLancamentoMusica);
    scanf("%d",&duracaoMusica);
    if(novaMusicaJukebox(j, nomeMusica, interpreteMusica, generoMusica, anoLancamentoMusica, duracaoMusica))
        printf("Musica %s adicionada.\n", nomeMusica);
    else
        printf("Musica ja existente.\n");
}

void deleteMusica(jukebox j, char *linha){
    //comando : delete musica 1
    //tirar comando deleteespaco
    char nomeMusica[MAXNOME];
    if(apagarComandoLinha(linha) == NULL)
        printf("Dados invalidos.\n");
    else{
        strcpy(nomeMusica, apagarComandoLinha(linha));
        if(apagarMusicaJukebox(j, nomeMusica))
            printf("Musica %s removida.\n", nomeMusica);
        printf("Musica inexistente.\n");
    }
}

void viewMusica(jukebox j, char *linha){
    char nomeMusica[MAXNOME];
    if(apagarComandoLinha(linha) == NULL)
        printf("Dados invalidos.\n");
    else{
        strcpy(nomeMusica, apagarComandoLinha(linha));
        m = devolveMusicaJukebox(j, nomeMusica);
        if(m == NULL)
            printf("Musica inexistente.\n");
        //listar
        printf("%s\n", interpreteMusica(m));
        printf("%s\n", generoMusica(m));
        printf("%d\n", anoLancamentoMusica(m));
        printf("%d\n", duracaoMusica(m));
        printf("Tocada %d vezes.\n", numeroVezesTocada(m));
    }
}

void listaMusica(jukebox j, char *linha){
    char *comando;
    strcpy(comando, apagarComandoLinha(linha));
    if(strlen(comando) != 1))
        printf("Dados invalidos.\n");
    switch(comando[0]){
        case 'a' : totalEListagemMusicas(j); break;
        case 'i' : listaMusicasInterprete(j); break;
        case 'g' : listaMusicasGenero(j); break;
        case 'p' : listaMusicasEmMaisPlaylists(j); break;
        case 't' : listaMusicasMaisTocadas(j); break;
        default  : printf("Dados invalidos.\n");
    }
}

//funcoes listar
void totalEListagemMusicas(jukebox j){
    char *nomeMusica = malloc(sizeof(char) * MAXNOME);
    int contaMusicas = 0;
    iterador myIt = criaIteradorNomesMusicas(j);
    while(temSeguinteIterador(myIt))
    {
        strcpy(nomeMusica, seguinteIterador(myIt));
        contaMusicas++;
        printf("%s\n.", nomeMusica);
    }
    printf("Total de musicas %d.\n", contaMusicas);
}

void listaMusicasInterprete(jukebox j){
    musica m;
    char *autorMusica = malloc(sizeof(char) * MAXNOME);
    scanf("%s", autorMusica);
    if(!numeroMusicasJukebox(j))
        printf("Sem musicas.\n");
    int contaInterprete = 0;
    iterador myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(!strcmp(autorMusica, interpreteMusica(m)))
        {
            contaInterprete++;
            printf("%s\n", nomeMusica(m));
        }
    }
    if(!contaInterprete)
        printf("Autor desconhecido.\n");
}

void listaMusicasGenero(jukebox j){
    musica m;
    char *generoMusica = malloc(sizeof(char) * MAXGENERO);
    scanf("%s", generoMusica);
    if(!numeroMusicasJukebox(j))
        printf("Sem musicas.\n");
    int contaGenero = 0;
    iterador myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(!strcmp(generoMusica, generoMusica(m)))
        {
            contaGenero++;
            printf("%s\n", generoMusica(m));
        }
    }
    if(!contaGenero)
        printf("Genero desconhecido.\n");
}

void listaMusicasEmMaisPlaylists(jukebox j){
    musica m;
    int maxPlaylists = 0;
    if(!numeroMusicasJukebox(j))
        printf("Sem musicas.\n");
    if(!numeroPlaylistsJukebox(j))
        printf("Sem playlists.\n");
    iterador myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(numeroPlaylistsMusica(m) > maxPlaylists)
            maxPlaylists = numeroPlaylistsMusica(m);
    }
    myIt = criaIteradorMusicas(j); //tag
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(numeroPlaylistsMusica(m) == maxPlaylists)
            printf("%s\n", nomeMusica(m));
    }
    printf("Em %d playlists.\n", maxPlaylists);
}


void listaMusicasMaisTocadas(jukebox j){
    musica m;
    int top3 = 0, top2 = 0, top1 = 0; //top 3 e a terceira musica que foi tocada mais vezes
    if(!numeroMusicasJukebox(j))
        printf("Sem musicas.\n");
    if(!numeroPlaylistsJukebox(j))
        printf("Sem playlists.\n");
    iterador myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(numeroVezesTocada(m) > top1)
            top1 = numeroVezesTocada(m);
        else if((numeroVezesTocada(m) > top2) && (numeroVezesTocada(m) < top1)) //testar
            top2 = numeroVezesTocada(m);
        else if((numeroVezesTocada(m) > top3) && (numeroVezesTocada(m) < top2))
            top3 = numeroVezesTocada(m);
    }
    criaIteradorTop(j, top1);
    criaIteradorTop(j, top2);
    criaIteradorTop(j, top3);
    }
}

void criaIteradorTop(jukebox j, int top){
    myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(numeroVezesTocada(m) == top)
            printf("%s tocada %d vezes.\n", nomeMusica(m), top);
}
//**************

void criaPlaylist(jukebox j, char *linha, int numeroMusicas, int tempoDuracao){
    char *comando;
    int numeroMusicasLimite;
    if(sscanf(linha, "%s %d", comando, &numeroMusicasLimite) != 2 || numeroMusicasLimite < 1)
        printf("Dados invalidos.\n");
    if(numeroMusicasLimite > numeroMusicas){
        printf("Playlist excedeu dimensao.\n");
        printf("Playlist nao criada.\n");
    }
    scanf("%s", nomePlaylist); //nao da para usar scan ate enter porque nao se quer mandar a linha mas sim a proxima
    nomePlaylist[strlen(nomePlaylist) - 1] = '\0';

}

void tocaPlaylist(char *linha){

}

void listaPlaylist(char *linha, ){

}

void modificarPlaylist(char *linha, ){

}

void destroiPlaylist(char *linha, ){

}
