#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       

#define TAMANHOLINHA 1000
#define TAMANHOPALAVRA 50

typedef struct Ocorrencia {
    int linha;
    char conteudo[TAMANHOLINHA];   
    struct Ocorrencia *prox;
} Ocorrencia;

typedef struct No {
    char palavra[TAMANHOPALAVRA];
    Ocorrencia *ocorrencias;
    int contador;
    struct No *esquerda;
    struct No *direita;
} treeno;

treeno *criarNo(const char *palavra, int linha, const char *conteudo);
void imprimirArvore(treeno* raiz);
treeno *inserirPalavra(treeno *raiz, const char *palavra, int linha, const char *conteudoLinha);
void TreeVerificarPalavra(treeno *raiz, const char *alvo);
void liberarArvore(treeno *raiz);
