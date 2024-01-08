#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 1000

typedef struct Ocorrencia {
    int linha;
    struct Ocorrencia *prox;
} Ocorrencia;

typedef struct Node {
    char palavra[TAMANHO];
    Ocorrencia* numOcorr;
    struct Node* prox;
} no;



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
    strncpy(novoNode->palavra, palavra, TAMANHO);
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

    while (atual != NULL) {
        if (strcmp(atual->palavra, alvo) == 0) {
            if (!encontrada) {
                encontrada = 1;
                printf("Palavra '%s' encontrada nas seguintes linhas:\n", alvo);
            }
            Ocorrencia *ocorrenciaAtual = atual->numOcorr;
            while (ocorrenciaAtual != NULL) {
                printf("   Linha: %d\n", ocorrenciaAtual->linha);
                ocorrenciaAtual = ocorrenciaAtual->prox;
            }
        }
        atual = atual->prox;
    }

if (!encontrada) 
        printf("Palavra '%s' não encontrada no arquivo.\n", alvo);
    encontrada = 0;
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

int main() {
    FILE* in;
    char palavraBuscada[TAMANHO];
    char * linha;
    char * quebra_de_linha;
    int contador_linha = 1;
	char * copia_ponteiro_linha;
    char* palavra;

    // Inicializar a lista ligada
    no *lista = NULL;

    // Abrir o arquivo
    in = fopen("texto.txt", "r");
    if (in == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    linha = (char *) malloc((TAMANHO + 1) * sizeof(char));

		while(in && fgets(linha, TAMANHO, in)){
			
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;
            printf("linha %03d: '%s'\n", contador_linha , linha);

            copia_ponteiro_linha = linha;

			while( (palavra = strsep(&copia_ponteiro_linha, " ")) )
            inserirNaLista(&lista, palavra, contador_linha);

            
            contador_linha++;
            }



return 0;
}