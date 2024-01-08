#define FALSE 0
#define TRUE 1

#define LISTA_LIGADA
#define LISTA_ORDENADA

typedef int Boolean;
typedef int Elemento;

typedef struct _no_ {

	Elemento valor;
	struct _no_ * proximo;

} No;

typedef struct {
	
	No * primeiro;

} ListaLigada;

ListaLigada * cria_lista();
void destroi_lista(ListaLigada * lista);
int tamanho(ListaLigada * lista);
void imprime(ListaLigada * lista);
int busca(ListaLigada * lista, Elemento e);

#ifdef LISTA_ORDENADA
Boolean insere(ListaLigada * lista, Elemento e);
#else
Boolean insere(ListaLigada * lista, Elemento e, int indice);
#endif

Boolean remove_elemento(ListaLigada * lista, Elemento e);
