#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

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
    novoNo->contador = 1;
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
            printf("Linha %d: %s\n", ocorrenciaAtual->linha, ocorrenciaAtual->conteudo);
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
        raiz->contador += 1;
    }

    return raiz;
}

void imprimeReverso(Ocorrencia* ocorrenciaAtual)
{ 
    if (ocorrenciaAtual == NULL)
       return;
 
    imprimeReverso(ocorrenciaAtual->prox);
    if (ocorrenciaAtual->prox != NULL){
        if (ocorrenciaAtual->linha != ocorrenciaAtual->prox->linha){
                printf("%05d: %s\n", ocorrenciaAtual->linha, ocorrenciaAtual->conteudo);
        }
    }
    else {
        printf("%05d: %s\n", ocorrenciaAtual->linha, ocorrenciaAtual->conteudo);
    }
}

void TreeVerificarPalavra(treeno *raiz, const char *alvo) {
    if (raiz == NULL) {
        printf("Palavra '%s' não encontrada.\n", alvo);
        return;
    }

    int comparacao = strcmp(alvo, raiz->palavra);

    if (comparacao == 0) {
        printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", raiz->contador, alvo);

        Ocorrencia *ocorrenciaAtual = raiz->ocorrencias;
        imprimeReverso(ocorrenciaAtual);
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