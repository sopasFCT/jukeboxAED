#ifndef MUSICA_H_INCLUDED
#define MUSICA_H_INCLUDED

typedef struct _musica *musica;

//Funcao cria musica
//funcao que serve para registar uma musica. retorna uma variavel inicializada do tipo musica
musica criaMusica(char *nome, char *interprete, char *genero, int anoLancamento, int duracao);

//funcao criada para libertar memoria
void destroiMusica(musica m);

//funcao usada para libertar memoria numa funcao destroi(void*)
void destroiGenMusica(void *m)
#endif // MUSICA_H_INCLUDED
