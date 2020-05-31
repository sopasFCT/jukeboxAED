#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED

typedef struct _playlist *playlist;

/***********************************************
criaPlaylist - funcao da instancia da estrutura
associada a uma playlist que contem uma sequencia
de musicas e varias caracteristicas da playlist
Parametros: numeroMusicasLimite - limite de musicas
            numa playlist declarado no inicio do programa
            nome - nomePlaylist que vamos guardar na jukebox
Retorno: p - se a playlist foi criada com sucesso
         NULL - se  a playlist nao foi criada
***********************************************/
playlist criaPlaylist(int numeroMusicasLimite, char *nome);

/***********************************************
retornaVarPlaylist - funcao que tem como objetivo
devolver as varias variaveis da estrutura playlist
Parametros: p - apontador para a playlist
***********************************************/
char* retornaNomePlaylist(playlist p);
int retornaNumeroMusicasPlaylist(playlist p);
int retornaDuracaoPlaylist(playlist p);
int retornaNumeroVezesTocada(playlist p);

/***********************************************
incrementarNumeroVezesTocada - incrementar o numero de vezes
que a playlist e todas as suas musicas foram tocadas
Parametros: p - playlist a qual vamos incrementar nas musicas
                o numero de vezesTocada
***********************************************/
void incrementarNumeroVezesTocada(playlist p);

/***********************************************
devolvePosMusicaPlaylist - funcao para retornar a posicao de uma musica
                           na sequencia de musicas de uma certa playlist
Parametros: p - playlist na qual queremos procurar a musica
            m - musica a procurar na sequencia de musicas da playlist
Retorno: -1 - se nao foi encontrar a musica
         pos - se encontrar a musica
***********************************************/
int devolvePosMusicaPlaylist(playlist p, musica m);

/***********************************************
removerMusicaPlaylist - remove uma musica de uma playlist
Parametros: p - playlist a qual vamos remover uma musica
            pos - posicao da sequencia de musicas que vamos remover
Retorno: retorna o nome da musica removida
***********************************************/
char* removerMusicaPlaylist(playlist p, int pos);

/***********************************************
adicionaMusicaPlaylist - adiciona uma musica a uma playlist
Parametros: p - playlist a qual se adiciona a musica
            m - musica que se vai adicionar a playlist
            pos - posicao na sequencia de musicas da playlist
            nomeMusica - nome da musica que vamos adicionar a playlist
            tempoMaximo - parametro definido no arranque do programa
Retorno: 0 - nao consegue adicionar outra musica pois excede o tempo maximo
         1 - nao consegue adicionar pois o tempo da playlist excede o tempo maximo permitido
         2 - adicionou a musica a playlist
***********************************************/
int adicionaMusicaPlaylist(playlist p, musica m, int pos, char* nomeMusica, int tempoMaximo);

/***********************************************
verificaCondicoesPlaylist - funcao para verificar se e possivel
                            adicionar uma musica a playlist modify i
Parametros: p- playlist a qual pretendemos adicionar uma musica
            pos- posicao da sequencia a qual pretendemos adicionar
                 uma musica a sequencia
Retorno: 0- nao e possivel adicionar uma musica na posicao de parametro
         1- e possivel adicionar uma musica na posicao de parametro
***********************************************/
int verificaCondicoesPlaylist(playlist p, int pos);

/***********************************************
criaIterador - funcao para criar iterador com as musicas de
               determinada playlist
Parametros: p - playlist a qual queremos iterar musicas
Retorno: myIt - retorna o iterador criado para percorrer
                as musicas da playlist p
***********************************************/
iterador criaIteradorMusicasPlaylist(playlist p);

/**********************************************
existeMusicaPlaylist - funcao que recebe uma certa musica e avalia
                       se ela esta presente numa determinada playlist ou nao
Parametros: p - playlist que vai verificar se existe uma musica
            m - musica a verificar se existe na playlist p
Retorno: 1- se existe
         0- se nao existe
***********************************************/
int existeMusicaPlaylist(playlist p, musica m);

/***********************************************
destroiPlaylistEMusicas - funcao criada para destruir
                          uma playlist e todas as suas
                          musicas
Parametros: p - playlist que queremos destruir e destruir
                as suas musicas
***********************************************/
void destroiPlaylistEMusicas(playlist p);

/***********************************************
destroiPlaylist - funcao para destruir a playlist
Parametros: p - playlist que queremos destruir
***********************************************/
void destroiPlaylist(playlist p);
void destroiGenPlaylist(void *p);
#endif // PLAYLIST_H_INCLUDED
