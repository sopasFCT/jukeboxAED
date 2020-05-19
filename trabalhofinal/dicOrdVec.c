/*
 * dicOrdVector.c
 */
#include <stdlib.h>
#include "iterador.h"
#include "chaves.h"
#include "tuplo.h"
#include "dicOrdenado.h"

struct _dicOrdenado{
	tuplo * elems; // apontador para vector de tuplos (chave,elemento)
	int numElems;
	int capacidade;
	int tipoCh; // 0-inteiro; 1-string
};

dicOrdenado criaDicOrdenado(int cap, int tipoChave){
	dicOrdenado d;
	d = (dicOrdenado) malloc(sizeof(struct _dicOrdenado));
	if ( d == NULL) return NULL;
	d->elems = (tuplo *) malloc(sizeof(tuplo) * cap);
	if (d->elems == NULL){
		free(d);
		return NULL;
	}
	d->numElems = 0;
	d->capacidade = cap;
	d->tipoCh =tipoChave;
	return d;
}

void destroiDicOrdenado (dicOrdenado d ){
	int i;
	for(i=0;i<d->numElems;i++)
		destroiTuplo(d->elems[i]);
	free(d->elems);
	free(d);
}

void destroiDicOrdEElems(dicOrdenado d, void (*destroi)(void *) ){
	int i;
	for(i=0;i < d->numElems;i++){
		destroi(segTuplo(d->elems[i]));
		destroiTuplo(d->elems[i]);
	}
	free(d->elems);
	free(d);
}

int vazioDicOrdenado(dicOrdenado d){
	if (d->numElems == 0)
		return 1;
	return 0;
}

int tamanhoDicOrdenado(dicOrdenado d){
	return d->numElems;
}
/* Funcao para calcular a posicao dum dado elemento no vector */
int posElemDicOrdenado(dicOrdenado d, void * ch){
	int i;
	for (i = 0; i<d->numElems;i++)
		if (igualChaves(ch,priTuplo(d->elems[i]),d->tipoCh) == 1)
			return i;
	return -1;
}
int existeElemDicOrdenado(dicOrdenado d, void * ch){
	if (posElemDicOrdenado(d,ch) != -1)
		return 1;
	return 0;
}

void * elementoDicOrdenado(dicOrdenado d, void * ch){
	int pos = posElemDicOrdenado(d,ch);
	if (pos != -1)
		return segTuplo(d->elems[pos]);
	return NULL;
}
/* Aumenta o vector do dicionario ordenado */
void incDicOrdenado (dicOrdenado d){
	int i = 0;
	tuplo* aux = (tuplo *)malloc(sizeof(tuplo) * d->capacidade*2); // duplica
	for (;i<d->numElems;i++)
		aux[i] = d->elems[i];
	free(d->elems);
	d->elems = aux;
	d->capacidade = d->capacidade * 2;
}

int adicionaElemDicOrdenado(dicOrdenado d, void * ch, void * elem){
	int pos = posElemDicOrdenado(d,ch);
	if (pos != -1)
		return 0;
	if (d->numElems == d->capacidade)
		incDicOrdenado(d);
	d->elems[d->numElems++] = criaTuplo(d->tipoCh,ch,elem);
	return 1;
}

void * removeElemDicOrdenado(dicOrdenado d, void * ch){
	void * elem;
	int pos = posElemDicOrdenado(d,ch);
	if (pos == -1)
		return NULL;
	elem = segTuplo(d->elems[pos]);
	destroiTuplo(d->elems[pos]);
	d->elems[pos] = d->elems[--d->numElems];
	return elem;
}
void ordenaDicOrdenado(tuplo * vetor, int nElems,int tipo){
   int i, j;
   tuplo aux;
	for(j=nElems-1; j>=1; j--){
		for(i=0; i<j; i++){
			if(compChaves(priTuplo(vetor[i]),priTuplo(vetor[i+1]),tipo)>0){ //==1
				aux=vetor[i];
                vetor[i]=vetor[i+1];
                vetor[i+1]=aux;
            }
        }
    }
}

iterador iteradorDicOrdenado(dicOrdenado d){
	int i;
	// vector com os elementos do dicionário
	void * * aux = (void * *) malloc(sizeof(void *)* d->numElems);
	ordenaDicOrdenado(d->elems,d->numElems,d->tipoCh);
	for(i=0;i<d->numElems;i++)
		aux[i]=segTuplo(d->elems[i]);
	return criaIterador(aux,d->numElems);
}

iterador iteradorChaveDicOrdenado(dicOrdenado d){

	int i;
	// vector com as chaves dos elementos do dicionário
	void * * aux = (void * *) malloc(sizeof(void *)* d->numElems);
    ordenaDicOrdenado(d->elems,d->numElems,d->tipoCh);
	for(i=0;i<d->numElems;i++)
		aux[i]=priTuplo(d->elems[i]);
	return criaIterador(aux,d->numElems);
}
