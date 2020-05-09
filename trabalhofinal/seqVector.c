#include <stdlib.h>
#include "iterador.h"
#include "sequencia.h"

/* Estrutura de dados: sequencia implementada em vector */
struct _sequencia{
	void * * elems; // apontador para vector de enderecos de elementos
	int numElems;
	int capacidade; // capacidade corrente do vector
};


sequencia criaSequencia(int cap){
	sequencia s = (sequencia)malloc(sizeof(struct _sequencia));
	if(s == NULL) return NULL;
	s -> elems      =  (void** )malloc(sizeof(void* )* cap);
	if(s -> elems == NULL){
        free (s);
        return NULL;
	}
	s -> numElems   = 0;
	s -> capacidade = cap;
	return s;
}


void destroiSequencia (sequencia s ){
	free(s->elems);
	free(s);
}


void destroiSeqElems(sequencia s, void (*destroi)(void *) ){
    for(int i = 0; i < tamanhoSequencia(s); i++)
        destroi(s -> elems[i]);
    destroiSequencia(s);
}


int vaziaSequencia(sequencia s){
	if(!(s -> numElems)) return 1;
	else return 0; //se tiver vazia return 1 se tiver algo return 0

}


int tamanhoSequencia(sequencia s){
	return(s -> numElems);
}


void * elementoPosSequencia(sequencia s, int i){
	return(s -> elems[i-1]);//tirei -1
}

void adicionaPosSequencia(sequencia s, void * elem, int i){
    //i--;
    int j;
    for(j = s->numElems; j >= i; j--)
        s->elems[j] = s->elems[j - 1];
    s->elems[i-1] = elem;
    s->numElems++;
}


void * removePosSequencia(sequencia s, int i){
    void *copiaElemento =  (void*)malloc(sizeof(void*));
	i--; //aqui a sequencia funciona como vetor logo vai ter posicao 0 sendo que quando recebe uma posicao no main e tratado apenas a partir da posicao 1
    copiaElemento = s -> elems[i];
    for(; i < s -> numElems; i++)
        s -> elems[i] = s -> elems[i + 1];
	s -> numElems--;
	return copiaElemento;
}


iterador iteradorSequencia(sequencia s){
	//CUIDADO DEVE DAR AO ITERADOR UMA COPIA DO VECTOR A PERCORRER
	int i;
	void ** iteradorS = (void** )malloc(sizeof(void *) * s->numElems);
	for(i = 0; i < s->numElems; i++)
        iteradorS[i] = s->elems[i];
	return(criaIterador(iteradorS, s->numElems));
}
