#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "listaLigada.c"

int main(int argc, char *argv[]) {
    if (argc != 3 || (strcmp(argv[2], "lista") != 0 && strcmp(argv[2], "arvore") != 0)) {
        printf("Uso: ./ep1 <arquivo> <lista|arvore>\n");
        return 1;
    }

    char *nomeArquivo = argv[1];
    char *tipoEstrutura = argv[2];

    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Arquivo '%s' não encontrado.\n", nomeArquivo);
        return 1;
    }

    clock_t inicioTempo = clock();

    Indice indice = criaIndex(file);

    clock_t fimTempo = clock();
    double tempoIndex = ((double)(fimTempo - inicioTempo)/CLOCKS_PER_SEC) * 1000.0;

    printf("Tipo de indice: '%s'\n", tipoEstrutura);
    printf("Arquivo texto: '%s'\n", nomeArquivo);
    printf("Numero de linhas no arquivo: %d\n", indice.tamanho);
    printf("Tempo para carregar o arquivo e construir o indice: %lf ms\n", tempoIndex);

    char **linhas = malloc(indice.tamanho * sizeof(char *));
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < indice.tamanho; i++) {
        linhas[i] = malloc(1000 * sizeof(char));
        fgets(linhas[i], 1000, file);
    }

    while (1) {
        printf("> ");
        char comando[100];
        scanf("%s", comando);

        if (strcmp(comando, "busca") == 0) {
            char word[100];
            scanf("%s", word);

            inicioTempo = clock();
            Entrada *result = procuraPalavra(&indice, word);
            fimTempo = clock();
            int procuraTempo = (int)((fimTempo - inicioTempo) * 1000 / CLOCKS_PER_SEC);

            if (result != NULL) {
                printOcorrencias(result, linhas);
            } else {
                printf("Palavra '%s' nao encontrada.\n", word);
            }

            printf("Tempo de busca: %d ms\n", procuraTempo);
        } else if (strcmp(comando, "fim") == 0) {
            break;
        } else {
            printf("Opcao invalida!\n");
        }
    }

    fclose(file);

    for (int i = 0; i < indice.tamanho; i++) {
        free(linhas[i]);
    }
    free(linhas);

    return 0;
}