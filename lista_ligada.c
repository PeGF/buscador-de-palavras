#include <stdio.h>
#include <stdlib.h>

#include "lista_ligada.h"

ListaLigada * cria_lista(){

	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->primeiro = NULL;
	
	return lista;
}

void destroi_lista(ListaLigada * lista){

	No * p = lista->primeiro;
	No * tmp;

	while(p){
		
		tmp = p;
		p = p->proximo;
		free(tmp);
	}

	free(lista);
}

int tamanho(ListaLigada * lista){

	int tamanho = 0;

	No * p = lista->primeiro;

	while(p){
		
		tamanho++;
		p = p->proximo;
	}

	return tamanho;
}

void imprime(ListaLigada * lista){

	No * p;

	printf("Lista:");

	for(p = lista->primeiro; p; p = p->proximo){

		printf(" %d", p->valor);
	}

	printf("\n");
}

#ifdef LISTA_ORDENADA
int busca(ListaLigada * lista, Elemento e){

	int i = 0;
	No * p = lista->primeiro;

	while(p && p->valor < e){

		p = p->proximo;
		i++;
	}
	return p ? (p->valor == e ? i : -1) : -1;
}
#else
int busca(ListaLigada * lista, Elemento e){

	int i = 0;
	No * p = lista->primeiro;

	while(p){

		if(p->valor == e) return i;
		
		p = p->proximo;
		i++;
	}

	return -1;
}
#endif

#ifdef LISTA_ORDENADA
Boolean insere(ListaLigada * lista, Elemento e){

	No * p;
	No * anterior;
	No * novo = (No *) malloc(sizeof(No));

	novo->valor = e;

	anterior = NULL;
	p = lista->primeiro;

	while(p){

		if(e < p->valor) break;
 			
		anterior = p;
		p = p->proximo;
	}
	
	novo->proximo = p;
		
	if(anterior) anterior->proximo = novo;
	else lista->primeiro = novo;

	return TRUE;
}
#else
Boolean insere(ListaLigada * lista, Elemento e, int indice){

	int i;

	No * p;
	No * novo = (No *) malloc(sizeof(No));

	novo->valor = e;
	
	if(indice >= 0 && indice <= tamanho(lista)){

		if(indice == 0){

			novo->proximo = lista->primeiro;
			lista->primeiro = novo;
		}
		else {

			i = 0;
			p = lista->primeiro;

			while(p){

				if(i == indice - 1) break;

				i++;
				p = p->proximo;
			}
		
			novo->proximo = p->proximo;
			p->proximo = novo;
		}

		return TRUE;
	}

	return FALSE;
}
#endif

Boolean remove_elemento(ListaLigada * lista, Elemento e){

	int i;
	int indice = busca(lista, e);
	No * p;
	No * tmp;

	if(indice >= 0) {

		if(indice == 0){

			tmp = lista->primeiro;
			lista->primeiro = tmp->proximo;
			free(tmp);
		}
		else{

			i = 0;
			p = lista->primeiro;

			while(p){

				if(i == indice - 1) break;

				i++;
				p = p->proximo;
			}
			
			tmp = p->proximo;
			p->proximo = p->proximo->proximo;
			free(tmp);
		}
		
		return TRUE;
	}

	return FALSE;
}
