#ifndef JUKEBOX_H_INCLUDED
#define JUKEBOX_H_INCLUDED

typedef struct _jukebox *jukebox;

/***********************************************
criaJukebox - funcao da instancia da estrutura
associada a uma jukebox que contem um dicionario
de playlists e um dicionario ordenado de musicas
Parametros:
Retorno: apontador para a instancia criada
***********************************************/
jukebox criaJukebox();

/***********************************************
novaMusicaJukebox - funcao que adiciona uma musica
a jukebox que recebe como parametro
Parametros: j - apontador para a jukebox
            nomeMusica - nome da musica para adicionar a jukebox
            interprete - interprete da musica
            genero - genero da musica
            anoLancamento - ano lancamento da musica
            duracao - duracao da musica
Retorno: 0 - nao foi possivel adicionar pois ja existe a musica
         1 - foi adicionada a musica ao dicionario de musicas
***********************************************/
int novaMusicaJukebox(jukebox j, char *nomeMusica, char *interprete, char *genero, int anoLancamento, int duracao);

/***********************************************
criaPlaylistJukebox - funcao para criar uma playlist na jukebox
Parametros: j - apontador para a jukebox
            nomePlaylist - nome da playlist para adicionar a jukebox
            numeroMusicasLimite - numero de musicas limite declarado
            no inicio do programa
Retorno: p - retorna a playlist se for possivel adicionar
         NULL - caso nao tenha sido possivel adicionar
         por ja haver uma playlist com o mesmo nome
***********************************************/
playlist criaPlaylistJukebox(jukebox j, char* nomePlaylist, int numeroMusicasLimite);

/***********************************************
existePlaylistJukebox - funcao para verificar se existe uma playlist na jukebox
Parametros: j - apontador para a jukebox
            nomePlaylist - nome a procurar nas chaves do dicionario
Retorno: 0 - caso nao exista
         1 - caso exista
***********************************************/
int existePlaylistJukebox(jukebox j, char* nomePlaylist);

/***********************************************
existeMusicaJukebox - funcao para verificar se existe uma playlist na jukebox
Parametros: j - apontador para a jukebox
            nomeMusica - nome a procurar nas chaves do dicionario
Retorno: 0 - caso nao exista
         1 - caso exista
***********************************************/
int existeMusicaJukebox(jukebox j, char* nomeMusica);

/***********************************************
numeroMusicas/PlaylistsJukebox - funcao para saber quantas musicas
                                 playlists ha na jukebox
Parametros: j - apontador para a jukebox
Retorno: int - numero de musicas/playlist totais
***********************************************/
int numeroMusicasJukebox(jukebox j);
int numeroPlaylistsJukebox(jukebox j);

/***********************************************
criaIterador - funcao para criar iterador de chaves ou
               de elementos de determinado dicionario
Parametros: j - apontador para a jukebox
Retorno: myIt - retorna o iterador criado para percorrer
                 o dicionario ou as chaves
***********************************************/
iterador criaIteradorNomesMusicas(jukebox j);
iterador criaIteradorMusicas(jukebox j);
iterador criaIteradorNomesPlaylists(jukebox j);
iterador criaIteradorPlaylists(jukebox j);

/***********************************************
apagarMusicaJukebox - funcao para apagar uma musica do dicionario de musicas
                      presentes na jukebox
Parametros: j - apontador para a jukebox
            nomeMusica - nome da musica a apagar
Retorno: 1 - se encontrou a musica e conseguiu apagar
         0 - se nao encontrou e nao apagou
***********************************************/
int apagarMusicaJukebox(jukebox j, char *nomeMusica);

/***********************************************
devolveMusica/PlaylistJukebox - funcao para aceder a uma certa musica/playlist da jukebox
Parametros: j - apontador para a jukebox
            nomeMusica - nome da musica que se quer apagar
            nomePlaylist - nome da playlist que se quer apagar
Retorno: musica - apontador para uma estrutura do tipo musica
          NULL - caso nao exista uma musica com esse nome
***********************************************/
musica devolveMusicaJukebox(jukebox j, char *nomeMusica);
playlist devolvePlaylistJukebox(jukebox j, char *nomePlaylist);

/***********************************************
destruirPlaylistJukebox - funcao para destruir uma playlist da jukebox
Parametros: j - apontador para a jukebox
            nomePlaylist - nome da playlist que se quer destruir
Retorno : 0 - nao encontrou e nao destruiu
          1 - encontrou e destruiu
***********************************************/
int destruirPlaylistJukebox(jukebox j, char* nomePlaylist);

/***********************************************
destroiPlaylistsEMusicas - funcao que destroi as playlists todas
                           da jukebox e todas as musicas dentro delas
Parametros: j - apontador para a jukebox
***********************************************/
void destroiPlaylistsEMusicas(jukebox j);

/***********************************************
destroiJukebox- funcao que destroi a jukebox recebida como parametro
Parametros: j - apontador para a jukebox
***********************************************/
void destroiJukebox(jukebox j);
#endif // JUKEBOX_H_INCLUDED
