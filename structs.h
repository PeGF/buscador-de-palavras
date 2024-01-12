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

typedef struct Node {
    char palavra[TAMANHOPALAVRA];
    Ocorrencia* numOcorr;
    struct Node* prox;
} no;

typedef struct No {
    char palavra[TAMANHOPALAVRA];
    Ocorrencia *ocorrencias;
    struct No *esquerda;
    struct No *direita;
} treeno;

treeno *criarNo(const char *palavra, int linha, const char *conteudo) {
    treeno *novoNo = (treeno *)malloc(sizeof(treeno));
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }

    strncpy(novoNo->palavra, palavra, TAMANHOPALAVRA - 1);
    novoNo->palavra[TAMANHOPALAVRA - 1] = '\0';

    Ocorrencia *novaOcorrencia = (Ocorrencia *)malloc(sizeof(Ocorrencia));
    if (novaOcorrencia == NULL) {
        perror("Erro ao alocar memória para a ocorrência");
        exit(EXIT_FAILURE);
    }

    novaOcorrencia->linha = linha;
    strncpy(novaOcorrencia->conteudo, conteudo, TAMANHOLINHA - 1);
    novaOcorrencia->conteudo[TAMANHOLINHA - 1] = '\0';
    novaOcorrencia->prox = NULL;

    novoNo->ocorrencias = novaOcorrencia;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;

    return novoNo;
}



void imprimirArvore(treeno* raiz){
    if (raiz != NULL){
        
        imprimirArvore(raiz->esquerda);
        printf("Palavra: %s\n", raiz->palavra);

        Ocorrencia* ocorrenciaAtual = raiz->ocorrencias;
        while (ocorrenciaAtual != NULL){
            printf("   Linha %d: %s\n", ocorrenciaAtual->linha, ocorrenciaAtual->conteudo);
            ocorrenciaAtual = ocorrenciaAtual->prox;
        }
        printf("\n");

        imprimirArvore(raiz->direita);
    }

}





treeno *inserirPalavra(treeno *raiz, const char *palavra, int linha, const char *conteudoLinha) {
    if (raiz == NULL) {
        return criarNo(palavra, linha, conteudoLinha);
    }

    int comparacao = strcmp(palavra, raiz->palavra);

    if (comparacao < 0) {
        raiz->esquerda = inserirPalavra(raiz->esquerda, palavra, linha, conteudoLinha);
    } else if (comparacao > 0) {
        raiz->direita = inserirPalavra(raiz->direita, palavra, linha, conteudoLinha);
    } else {
        // A palavra já existe na árvore, adiciona a ocorrência
        Ocorrencia *novaOcorrencia = (Ocorrencia *)malloc(sizeof(Ocorrencia));
        if (novaOcorrencia == NULL) {
            perror("Erro ao alocar memória para a ocorrência");
            exit(EXIT_FAILURE);
        }

        novaOcorrencia->linha = linha;
        strncpy(novaOcorrencia->conteudo, conteudoLinha, TAMANHOLINHA - 1);
        novaOcorrencia->conteudo[TAMANHOLINHA - 1] = '\0';
        novaOcorrencia->prox = raiz->ocorrencias;
        raiz->ocorrencias = novaOcorrencia;
    }

    return raiz;
}

void TreeVerificarPalavra(treeno *raiz, const char *alvo) {
    if (raiz == NULL) {
        printf("Palavra '%s' não encontrada.\n", alvo);
        return;
    }

    int comparacao = strcmp(alvo, raiz->palavra);

    if (comparacao == 0) {
        printf("Palavra '%s' encontrada nas seguintes linhas:\n", alvo);

        Ocorrencia *ocorrenciaAtual = raiz->ocorrencias;
        while (ocorrenciaAtual != NULL) {
            printf("   Linha %d: %s\n", ocorrenciaAtual->linha, ocorrenciaAtual->conteudo);
            ocorrenciaAtual = ocorrenciaAtual->prox;
        }
    } else if (comparacao < 0) {
        TreeVerificarPalavra(raiz->esquerda, alvo);
    } else {
        TreeVerificarPalavra(raiz->direita, alvo);
    }
}



void liberarArvore(treeno *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);

        Ocorrencia *ocorrenciaAtual = raiz->ocorrencias;
        while (ocorrenciaAtual != NULL) {
            Ocorrencia *tempOcorrencia = ocorrenciaAtual;
            ocorrenciaAtual = ocorrenciaAtual->prox;
            free(tempOcorrencia);
        }

        free(raiz);
    }
}


void inserirNaLista(no** cabeca, const char *palavra, int linha) {

    no *atual = *cabeca;
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            // Palavra encontrada, adicionar nova ocorrência à lista de ocorrências
            Ocorrencia *novaOcorrencia = (Ocorrencia*) malloc(sizeof(Ocorrencia));
            if (novaOcorrencia == NULL) {
                perror("Erro ao alocar memória");
                exit(EXIT_FAILURE);
            }
            novaOcorrencia->linha = linha;
            novaOcorrencia->prox = atual->numOcorr;
            atual->numOcorr = novaOcorrencia;
        }
        atual = atual->prox;
    }

    no *novoNode = (no*) malloc(sizeof(no));
    if (novoNode == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    strncpy(novoNode->palavra, palavra, TAMANHOPALAVRA);
    novoNode->numOcorr = (Ocorrencia*) malloc(sizeof(Ocorrencia));
    if (novoNode->numOcorr == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    novoNode->numOcorr->linha = linha;
    novoNode->numOcorr->prox = NULL;
    novoNode->prox = *cabeca;
    *cabeca = novoNode;
}


void verificarPalavra(no* cabeca, const char *alvo) {
    no* atual = cabeca;
    int encontrada = 0;

    printf("Palavra '%s' encontrada nas seguintes linhas:\n", alvo);

    while (atual != NULL) {
        if (strcmp(atual->palavra, alvo) == 0) {
            encontrada = 1;

            Ocorrencia *ocorrenciaAtual = atual->numOcorr;
            int linhaAnterior = -1;  
            while (ocorrenciaAtual != NULL) {
                printf("   Linha %d: %s\n", ocorrenciaAtual->linha, ocorrenciaAtual->conteudo);
                ocorrenciaAtual = ocorrenciaAtual->prox;
            }
        }
        atual = atual->prox;
    }

    if (!encontrada) 
        printf("Palavra '%s' nao encontrada.\n", alvo);
}


void imprimirLista(no *cabeca) {
    no *atual = cabeca;

    while (atual != NULL) {
        printf("Palavra: %s\n", atual->palavra);
        Ocorrencia *ocorrenciaAtual = atual->numOcorr;
        while (ocorrenciaAtual != NULL) {
            printf("   Ocorrencia na linha: %d\n", ocorrenciaAtual->linha);
            ocorrenciaAtual = ocorrenciaAtual->prox;
        }
        atual = atual->prox;
    }
}


void liberarLista(no *cabeca) {
    no *atual = cabeca;
    while (atual != NULL) {
        no *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}