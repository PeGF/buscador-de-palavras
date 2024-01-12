#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaLigada.h"

void adicionaOcorrencia(Entrada *entrada, int numeroLinha) {
    entrada->ocorrencias = realloc(entrada->ocorrencias, (entrada->contador + 1) * sizeof(int));
    entrada->ocorrencias[entrada->contador++] = numeroLinha;
}

Entrada novaPalavra(char *palavra, int numeroLinha) {
    Entrada entrada;
    strcpy(entrada.palavra, palavra);
    entrada.ocorrencias = NULL;
    entrada.contador = 0;
    adicionaOcorrencia(&entrada, numeroLinha);
    return entrada;
}

Entrada *procuraPalavra(Indice *indice, char *palavra) {
    for (int i = 0; i < indice->tamanho; i++) {
        if (strcmp(indice->entrada[i].palavra, palavra) == 0) {
            return &indice->entrada[i];
        }
    }
    return NULL;
}

Indice criaIndex(FILE *file) {
    Indice indice;
    indice.entrada = NULL;
    indice.tamanho = 0;

    char linha[1000];
    int numeroLinha = 0;

    while (fgets(linha, sizeof(linha), file)) {
        numeroLinha++;
        char *token = strtok(linha, " ,.!?\n");

        while (token != NULL) {
            for (int i = 0; token[i]; i++) {
                token[i] = tolower(token[i]);
            }

            Entrada *entrada = procuraPalavra(&indice, token);

            if (entrada == NULL) {
                indice.entrada = realloc(indice.entrada, (indice.tamanho + 1) * sizeof(Entrada));
                indice.entrada[indice.tamanho++] = novaPalavra(token, numeroLinha);
            } else {
                adicionaOcorrencia(entrada, numeroLinha);
            }

            token = strtok(NULL, " ,.!?\n");
        }
    }
    indice.numeroDeLinhas = numeroLinha;

    return indice;
}

void printOcorrencias(Entrada *entrada, char **linhas) {
    printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", entrada->contador, entrada->palavra);
    for (int i = 0; i < entrada->contador; i++) {
        if (entrada->ocorrencias[i] != entrada->ocorrencias[i+1]){
            printf("%05d: %s", entrada->ocorrencias[i], linhas[entrada->ocorrencias[i] - 1]);
        }
    }
}