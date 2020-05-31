//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//TADs usados
#include "iterador.h"
#include "musica.h"
#include "playlist.h"
#include "jukebox.h"

//constantes
#define MAXCMD     10
#define MAXLINHA   50
#define MAXNOME    100
#define MAXGENERO  30
#define QUIT       -1
#define INVALIDO   0
#define UPLOAD     1
#define DELETE     2
#define VIEW       3
#define MUSIC      4
#define CREATE     5
#define PLAY       6
#define PLAYLIST   7
#define MODIFY     8
#define DESTROY    9

/*******************************************
Comandos menu (com saida) :
quit     - -1
upload   - 1
delete   - 2
view     - 3
music    - 4
create   - 5
play     - 6
playlist - 7
modify   - 8
destroy  - 9
*******************************************/

//prototipos
//funcoes menu
void interpretador(jukebox j);
void definirLimites(char *linhaInicio, int *numeroMusicas, int *tempoDuracao);
int trataComando(char *linha, char *comando, int num);
int trataComandoIgual(char *linha, char *comando1, char *comando2, int num1, int num2);
int trataSaida(char *linha, char *comando, int num1);
char *scanAteEnter(char *string);
char *apagarComandoLinha(char *linha);
//funcoes listagem
void totalEListagemMusicas(jukebox j);
void listaMusicasInterprete(jukebox j);
void listaMusicasGenero(jukebox j);
void listaMusicasEmMaisPlaylists(jukebox j);
void listaMusicasMaisTocadas(jukebox j);
void criaIteradorTop(jukebox j, int top);
//funcoes tadss
void uploadMusica(jukebox j, char *linha);
void deleteMusica(jukebox j, char *linha);
void viewMusica(jukebox j, char *linha);
void listaMusica(jukebox j, char *linha);
void createPlaylist(jukebox j, char *linha, int numeroMusicas, int tempoDuracao);
void tocaPlaylist(jukebox j, char *linha);
void listaPlaylist(jukebox j, char *linha);
void modificarPlaylist(jukebox j, char *linha, int tempoDuracaoMaximoPlaylist);
void destroyPlaylistJukebox(jukebox j, char *linha);
//funcao switch modify
void adicionarMusicaPlaylist(jukebox j, playlist p, int posicao, int tempoDuracaoMaximoPlaylist);
//funcao para destruir tudo
void destroiJukeboxPlaylistsMusicas(jukebox j);

int main(){
    jukebox jukeboxAED = criaJukebox();
    interpretador(jukeboxAED);
    destroiJukeboxPlaylistsMusicas(jukeboxAED);
    return 0;
}

void interpretador(jukebox j){
    int numeroMusicas, tempoDuracao;
    char linha[MAXLINHA], linhaInicio[MAXLINHA], cmd;
    int cmdVerificado;
    fgets(linhaInicio, MAXLINHA, stdin);
    definirLimites(linhaInicio, &numeroMusicas, &tempoDuracao);
    printf("> ");
    fgets(linha, MAXLINHA, stdin);
    cmd = tolower(linha[0]);
    while(trataSaida(linha, "quit", QUIT) != QUIT){
        switch(cmd){
            case 'u' : cmdVerificado = trataComando(linha, "upload", UPLOAD); break;
            case 'd' : cmdVerificado = trataComandoIgual(linha, "delete", "destroy", DELETE, DESTROY); break;
            case 'v' : cmdVerificado = trataComando(linha, "view", VIEW); break;
            case 'm' : cmdVerificado = trataComandoIgual(linha, "music", "modify", MUSIC, MODIFY); break;
            case 'c' : cmdVerificado = trataComando(linha, "create", CREATE); break;
            case 'p' : cmdVerificado = trataComandoIgual(linha, "play", "playlist", PLAY, PLAYLIST); break;
            default  : printf("Comando inexistente.\n"); cmdVerificado = -2; break;
        }
        switch(cmdVerificado){
            case UPLOAD   : uploadMusica(j, linha); break;
            case DELETE   : deleteMusica(j, linha); break;
            case VIEW     : viewMusica(j, linha); break;
            case MUSIC    : listaMusica(j, linha); break;
            case CREATE   : createPlaylist(j, linha, numeroMusicas, tempoDuracao); break;
            case PLAY     : tocaPlaylist(j, linha); break;
            case PLAYLIST : listaPlaylist(j, linha); break;
            case MODIFY   : modificarPlaylist(j, linha, tempoDuracao); break;
            case DESTROY  : destroyPlaylistJukebox(j, linha); break;
            case INVALIDO : printf("Comando inexistente.\n"); break;
            default       : break;
        }
        cmdVerificado = -2;
        printf("> ");
		fgets(linha,MAXLINHA,stdin);
        cmd = tolower(linha[0]);
    }
    printf("Jukebox encerrada.\n");
}

/***********************************************
definirLimites - funcao que define os limites de numero
de numero por playlist e do tempo de duracao maxima de cada playlist
***********************************************/
void definirLimites(char *linhaInicio, int *numeroMusicas, int *tempoDuracao){
    if(sscanf(linhaInicio, "%d %d", numeroMusicas, tempoDuracao) == 2){
        printf("Jukebox aberta.\n");
        return;
    }
    else if(sscanf(linhaInicio, "%d %d", numeroMusicas, tempoDuracao) == 1)
        exit(1);
}

/***********************************************
trataComando - funcao que avalia se o comando apos se ter avaliado
o primeiro caracter dele corresponde ao esperado se corresponder
retorna o numero correspondente ao comando - parametro num
***********************************************/
int trataComando(char *linha, char* comando, int num){
    int i = 0;
    char newcmd[MAXCMD];
    while(linha[i] != ' ' && linha[i] != '\n'){
        newcmd[i] = tolower(linha[i]);
        i++;
    }
    newcmd[i] = '\0';
    if(!strcmp(newcmd, comando))
        return num;
    else
        return INVALIDO;
}

/***********************************************
trataSaida - funciona como um trata comando mas apenas
para o comando de saida
***********************************************/
int trataSaida(char *linha, char* comando, int num){
    int i = 0;
    char newcmd[MAXCMD];
    while(linha[i] != ' ' && linha[i] != '\n'){
        newcmd[i] = tolower(linha[i]);
        i++;
    }
    newcmd[i] = '\0';
    if(!strcmp(newcmd, comando))
        return num;
    else
        return INVALIDO;
}

/***********************************************
trataComandoIgual - para quando a mesma inicial pode
corresponder a dois comandos
***********************************************/
int trataComandoIgual(char *linha, char *comando1, char *comando2, int num1, int num2){
    int i = 0;
    char newcmd[MAXCMD];
     while(linha[i] != ' ' && linha[i] != '\n'){
        newcmd[i] = tolower(linha[i]);
        i++;
    }
    newcmd[i] = '\0';
    if(!strcmp(newcmd, comando1))
        return num1;
    else if(!strcmp(newcmd, comando2))
        return num2;
    else
        return INVALIDO;
}

/***********************************************
apagarComandoLinha - comando para apagar o comando da linha
quando se mete o comando e o nome da musica ou outros elementos na mesma linha
para apagar o comando da linha e dar return do resto para ser tratado dentro das funçoes
***********************************************/
char *apagarComandoLinha(char *linha){
    int i = 0;
    int j = 0;
    char *cmd = malloc(sizeof(char) * (strlen(linha) + 1));
    while(linha[i] != ' ')
        i++;
    i++;
    for(; i < strlen(linha) - 1; i++, j++)
        cmd[j] = linha[i];
    cmd[j] = '\0';
    return cmd;
}

/***********************************************
uploadMusica - funcao que faz upload de uma musica na jukebox
***********************************************/
void uploadMusica(jukebox j, char *linha){
    char nomeMusica[MAXNOME], interpreteMusica[MAXNOME], generoMusica[MAXGENERO], cmd[MAXCMD];
    int anoLancamentoMusica, duracaoMusica;
    char lerAnoLancamento[MAXCMD], lerDuracao[MAXCMD];
    if(sscanf(linha, "%s", cmd) != 1){
        printf("Dados invalidos.\n");
        return;
    }
    fgets(nomeMusica, MAXNOME, stdin);
    nomeMusica[strlen(nomeMusica) - 1] = '\0';
    fgets(interpreteMusica, MAXNOME, stdin);
    interpreteMusica[strlen(interpreteMusica) - 1] = '\0';
    fgets(generoMusica, MAXNOME, stdin);
    generoMusica[strlen(generoMusica) - 1] = '\0';
    fgets(lerAnoLancamento, MAXCMD, stdin);
    lerAnoLancamento[strlen(lerAnoLancamento) - 1] = '\0';
    sscanf(lerAnoLancamento, "%d", &anoLancamentoMusica);
    fgets(lerDuracao, MAXCMD, stdin);
    lerDuracao[strlen(lerDuracao) - 1] = '\0';
    sscanf(lerDuracao, "%d", &duracaoMusica);
    if(novaMusicaJukebox(j, nomeMusica, interpreteMusica, generoMusica, anoLancamentoMusica, duracaoMusica)){
        printf("Musica %s adicionada.\n", nomeMusica);
        return;
    }
    else{
        printf("Musica ja existente.\n");
        return;
    }
}

/***********************************************
deleteMusica - funcao para apagar uma musica da jukebox e
apaga tambem de todas as playlists que ela esta presente
***********************************************/
void deleteMusica(jukebox j, char *linha){
    char nomeMusicaApagar[MAXNOME], cmd[MAXCMD];
    if(sscanf(linha, "%s %s", cmd, nomeMusicaApagar) != 2){
        printf("Dados invalidos.\n");
        return;
    }
    //musica m;
    strcpy(nomeMusicaApagar, apagarComandoLinha(linha));
    //m = devolveMusicaJukebox(j, nomeMusicaApagar);
    if(apagarMusicaJukebox(j, nomeMusicaApagar)){
        printf("Musica %s removida.\n", nomeMusicaApagar);
        return;
    }
    printf("Musica inexistente.\n");
}

/***********************************************
viewMusica - funcao que lista a musica
***********************************************/
void viewMusica(jukebox j, char *linha){
    char nomeMusicaVer[MAXNOME], cmd[MAXCMD];
    if(sscanf(linha, "%s %s", cmd, nomeMusicaVer) < 2){
        printf("Dados invalidos.\n");
        return;
    }
    strcpy(nomeMusicaVer, apagarComandoLinha(linha));
    musica m = devolveMusicaJukebox(j, nomeMusicaVer);
    if(m == NULL){
        printf("Musica inexistente.\n");
        return;
    }
    printf("%s\n", interpreteMusica(m));
    printf("%s\n", generoMusica(m));
    printf("%d\n", anoLancamentoMusica(m));
    printf("%d\n", duracaoMusica(m));
    printf("Tocada %d vezes.\n", numeroVezesTocada(m));
}

/***********************************************
listaMusica - funcao que le a letra para saber o que listar
melhorar funcoes para n se dar prints/scans dentro de tads
***********************************************/
void listaMusica(jukebox j, char *linha){
    char comando, cmd[MAXCMD];
    if(sscanf(linha, "%s %c", cmd, &comando) != 2){
        printf("Dados invalidos.\n");
        return;
    }
    switch(comando = tolower(comando)){
        case 'a' : totalEListagemMusicas(j); break;
        case 'i' : listaMusicasInterprete(j); break;
        case 'g' : listaMusicasGenero(j); break;
        case 'p' : listaMusicasEmMaisPlaylists(j); break;
        case 't' : listaMusicasMaisTocadas(j); break;
        default  : printf("Dados invalidos.\n"); break;
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
        printf("%s\n", nomeMusica);
    }
    printf("Total de musicas %d.\n", contaMusicas);
    free(nomeMusica);
}

void listaMusicasInterprete(jukebox j){
    musica m;
    char autorMusica[MAXNOME];
    fgets(autorMusica, MAXNOME, stdin);
    autorMusica[strlen(autorMusica) - 1] = '\0';
    if(!numeroMusicasJukebox(j)){
        printf("Sem musicas.\n");
        return;
    }
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
    if(!contaInterprete){
        printf("Autor desconhecido.\n");
        return;
    }
}

void listaMusicasGenero(jukebox j){
    musica m;
    char generoMusicaListar[MAXGENERO];
    fgets(generoMusicaListar, MAXNOME, stdin);
    generoMusicaListar[strlen(generoMusicaListar) - 1] = '\0';
    if(!numeroMusicasJukebox(j)){
        printf("Sem musicas.\n");
        return;
    }
    int contaGenero = 0;
    iterador myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(!strcmp(generoMusicaListar, generoMusica(m)))
        {
            contaGenero++;
            printf("%s\n", nomeMusica(m));
        }
    }
    if(!contaGenero)
        printf("Genero desconhecido.\n");
}

void listaMusicasEmMaisPlaylists(jukebox j){
    musica m;
    int maxPlaylists = 0;
    if(!numeroMusicasJukebox(j)){
        printf("Sem musicas.\n");
        return;
    }
    if(!numeroPlaylistsJukebox(j)){
        printf("Sem playlists.\n");
        return;
    }
    iterador myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(numeroPlaylistsMusica(m) > maxPlaylists)
            maxPlaylists = numeroPlaylistsMusica(m);
    }
    myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(numeroPlaylistsMusica(m) == maxPlaylists)
            printf("%s\n", nomeMusica(m));
    }
    printf("Em %d playlists.\n", maxPlaylists);
}

void listaMusicasMaisTocadas(jukebox j){
    musica m;
    int top3 = 0, top2 = 0, top1 = 0;
    if(!numeroMusicasJukebox(j)){
        printf("Sem musicas.\n");
        return;
    }
    if(!numeroPlaylistsJukebox(j)){
        printf("Sem playlists.\n");
        return;
    }
    iterador myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(numeroVezesTocada(m) > top1){
            top3 = top2;
            top2 = top1;
            top1 = numeroVezesTocada(m);
        }
        else if((numeroVezesTocada(m) > top2) && (numeroVezesTocada(m) < top1)){ //testar
            top3 = top2;
            top2 = numeroVezesTocada(m);
        }
        else if((numeroVezesTocada(m) > top3) && (numeroVezesTocada(m) < top2)){
            top3 = numeroVezesTocada(m);
        }
    }
    criaIteradorTop(j, top1);
    criaIteradorTop(j, top2);
    criaIteradorTop(j, top3);
}

void criaIteradorTop(jukebox j, int top){
    musica m;
    iterador myIt = criaIteradorMusicas(j);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        if(numeroVezesTocada(m) == top)
            printf("%s tocada %d vezes.\n", nomeMusica(m), top);
    }
}

/***********************************************
createPlaylist - funcao para criar playlist tendo em conta todos os erros
que podem ocorrer
***********************************************/
void createPlaylist(jukebox j, char *linha, int numeroMusicas, int tempoDuracaoMaximoPlaylist){
    char comando[MAXCMD];
    int i = 1;
    int numeroMusicasLimite;
    char nomeMusicaPlaylist[MAXNOME];
    char nomePlaylist[MAXNOME];
    playlist p;
    musica m;
    if(sscanf(linha, "%s %d", comando, &numeroMusicasLimite) != 2 || numeroMusicasLimite < 1){
        printf("Dados invalidos.\n");
        return;
    }
    fgets(nomePlaylist, MAXNOME, stdin);
    nomePlaylist[strlen(nomePlaylist) - 1] = '\0';
    if(numeroMusicasLimite > numeroMusicas){
        printf("Playlist excedeu dimensao.\n");
        printf("Playlist nao criada.\n");
        return;
    }
    p = criaPlaylistJukebox(j, nomePlaylist, numeroMusicas);
    if(p == NULL){
        printf("Playlist ja existente.\n");
        return;
    }
    while(i <= numeroMusicasLimite){
        fgets(nomeMusicaPlaylist, MAXNOME, stdin);
        nomeMusicaPlaylist[strlen(nomeMusicaPlaylist) - 1] = '\0';
        if(!existeMusicaJukebox(j, nomeMusicaPlaylist)){
            printf("Musica %s inexistente.\n", nomeMusicaPlaylist);
            printf("Playlist nao criada.\n");
            destruirPlaylistJukebox(j, nomePlaylist);
            return;
        }
        m = devolveMusicaJukebox(j, nomeMusicaPlaylist);
        int decide = adicionaMusicaPlaylist(p, m, i, nomeMusicaPlaylist, tempoDuracaoMaximoPlaylist);
        if(decide == 1){
            printf("Playlist excedeu tempo.\n");
            printf("Playlist nao criada.\n");
            destruirPlaylistJukebox(j, nomePlaylist);
            return;
        }
        else if(decide == 2 && i == numeroMusicasLimite){
            printf("Playlist %s criada.\n", nomePlaylist);
        }
        i++;
    }
}

/***********************************************
tocaPlaylist - funcao que toca todas as musicas da playlist
***********************************************/
void tocaPlaylist(jukebox j, char *linha){
    playlist p;
    char comando[MAXCMD];
    char nomePlaylist[MAXNOME];
    int tamanhoPlaylist;
    if(sscanf(linha, "%s %s", comando, nomePlaylist) != 2){
        printf("Dados invalidos.\n");
        return;
    }
    strcpy(nomePlaylist, apagarComandoLinha(linha));
    p = devolvePlaylistJukebox(j, nomePlaylist);
    if(p == NULL){
        printf("Playlist inexistente.\n");
        return;
    }
    else{
        tamanhoPlaylist = retornaNumeroMusicasPlaylist(p);
        if(!tamanhoPlaylist){
            printf("Playlist vazia.\n");
            return;
        }
        else{
            printf("Playlist %s tem %d musicas e %d segundos.\n", nomePlaylist, tamanhoPlaylist, retornaDuracaoPlaylist(p));
            incrementarNumeroVezesTocada(p);
            return;
        }
    }
}

/***********************************************
listaPlaylist - funcao que lista todas as musicas de uma certa playlist
***********************************************/
void listaPlaylist(jukebox j, char *linha){
    char comando[MAXCMD];
    char nomePlaylist[MAXNOME];
    iterador myIt;
    playlist p;
    musica m;
    if(sscanf(linha, "%s %s", comando, nomePlaylist) != 2){
        printf("Dados invalidos.\n");
        return;
    }
    strcpy(nomePlaylist, apagarComandoLinha(linha));
    p = devolvePlaylistJukebox(j, nomePlaylist);
    if(p == NULL){
        printf("Playlist inexistente.\n");
        return;
    }
    int tamanhoPlaylist = retornaNumeroMusicasPlaylist(p);
    if(!tamanhoPlaylist){
        printf("Playlist vazia.\n");
        return;
    }
    myIt = criaIteradorMusicasPlaylist(p);
    while(temSeguinteIterador(myIt)){
        m = (musica)seguinteIterador(myIt);
        printf("%s %d\n", nomeMusica(m), duracaoMusica(m));
    }
    printf("Tempo total %d, tocada %d vezes.\n", retornaDuracaoPlaylist(p), retornaNumeroVezesTocada(p));
}

void modificarPlaylist(jukebox j, char *linha, int tempoDuracaoMaximoPlaylist){
    int posicao;
    char comando, modify[MAXCMD];
    char nomePlaylist[MAXNOME];
    char *nomeMusicaRemovida;
    if(sscanf(linha, "%s %c %d", modify, &comando, &posicao) != 3 || posicao <= 0){
        printf("Dados invalidos.\n");
        return;
    }
    fgets(nomePlaylist, MAXNOME, stdin);
    nomePlaylist[strlen(nomePlaylist) - 1] = '\0';
    playlist p = devolvePlaylistJukebox(j, nomePlaylist);
    if(p == NULL){
        printf("Playlist inexistente.\n");
        return;
    }
    switch(comando = tolower(comando)){
        case 'r' : nomeMusicaRemovida = removerMusicaPlaylist(p, posicao);
                   if(nomeMusicaRemovida == NULL) {
                        printf("Posicao invalida.\n");
                        return;
                    }
                   printf("%s removida.\n", nomeMusicaRemovida); break;
        case 'i' : adicionarMusicaPlaylist(j, p, posicao, tempoDuracaoMaximoPlaylist); break;
    }
}

void adicionarMusicaPlaylist(jukebox j, playlist p, int posicao, int tempoDuracaoMaximoPlaylist){
    char nomeMusicaAdicionar[MAXNOME];
    int decide, verificaPos;
    musica m;
    //melhorar
    verificaPos = verificaCondicoesPlaylist(p, posicao);
    if(verificaPos == -1) {
        printf("Posicao invalida.\n");
        return;
    }
    //
    fgets(nomeMusicaAdicionar, MAXNOME, stdin);
    nomeMusicaAdicionar[strlen(nomeMusicaAdicionar) - 1] = '\0';
    m = devolveMusicaJukebox(j, nomeMusicaAdicionar);
    if(m == NULL){
        printf("Musica inexistente.\n");
        return;
    }
    decide = adicionaMusicaPlaylist(p, m, posicao, nomeMusicaAdicionar, tempoDuracaoMaximoPlaylist);
    switch(decide){
        case -1: printf("Playlist excedeu dimensao.\n"); break;
        case 1 : printf("Playlist excedeu tempo.\n"); break;
        case 2 : printf("Musica adicionada.\n"); break;
    }
}

void destroyPlaylistJukebox(jukebox j, char *linha){
    char nomePlaylist[MAXNOME], comando[MAXCMD];
    if(sscanf(linha, "%s %s", comando, nomePlaylist) != 2){
        printf("Dados invalidos.\n");
        return;
    }
    strcpy(nomePlaylist, apagarComandoLinha(linha));
    if(destruirPlaylistJukebox(j, nomePlaylist))
        printf("Playlist eliminada.\n");
    else
        printf("Playlist inexistente.\n");
}

void destroiJukeboxPlaylistsMusicas(jukebox j){
    destroiPlaylistsEMusicasJukebox(j);
    destroiJukebox(j);
}
