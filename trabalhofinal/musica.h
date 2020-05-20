#ifndef MUSICA_H_INCLUDED
#define MUSICA_H_INCLUDED

typedef struct _musica *musica;

/***********************************************
criaMusica - funcao da instancia da estrutura
associada a uma musica
Parametros: nome - nome da musica
            interprete - interprete da musica
            genero - genero da musica
            anoLancamento - ano que a musica foi lancada
            duracao - duracao da musica em segundos
Retorno: m - se a musica foi criada com sucesso
         NULL - se a musica nao foi criada
***********************************************/
musica criaMusica(char *nome, char *interprete, char *genero, int anoLancamento, int duracao);

/***********************************************
retornaVarMusica - funcao que tem como objetivo
devolver as varias variaveis da estrutura musica
Parametros: m - apontador para a musica
***********************************************/
char *nomeMusica(musica m);
char *interpreteMusica(musica m);
char *generoMusica(musica m);
int anoLancamentoMusica(musica m);
int duracaoMusica(musica m);
int numeroVezesTocada(musica m);
int numeroPlaylistsMusica(musica m);

/***********************************************
incrementaNumeroVezesTocada - funcao para aceder de fora da tad musica
para poder incrementar o numero de vezes que a musica e tocada
Parametros: m - apontador para a musica
***********************************************/
void incrementaNumeroVezesTocada(musica m);

void incrementaNumeroPlaylistsPresente(musica m);
void decrementaNumeroPlaylistsPresente(musica m, int numeroVezesMusicaPlaylist);

/***********************************************
destroiMusica - funcao para destruir a memoria associada a tad musica
Parametros: m - apontador para a musica
***********************************************/
void destroiMusica(musica m);
void destroiGenMusica(void *m);

//funcao usada para libertar memoria numa funcao destroi(void*)
//void destroiGenMusica(void *m)
#endif // MUSICA_H_INCLUDED
