#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "listaLigada.c"
#include "arvore.c"

int main(int argc, char *argv[]) {
    if (argc != 3 || (strcmp(argv[2], "lista") != 0 && strcmp(argv[2], "arvore") != 0)) {
        printf("Uso: ./ep1 <arquivo> <lista|arvore>\n");
        return 1;
    }
    
    char *nomeArquivo = argv[1];
    char *tipoEstrutura = argv[2];

    clock_t abrirArquivoInicio = clock();
    FILE *file = fopen(nomeArquivo, "r");
    clock_t abrirArquivoFim = clock();
    double tempoParaAbrir = ((double)(abrirArquivoFim - abrirArquivoInicio)/CLOCKS_PER_SEC) * 1000.0;


    if (file == NULL) {
        printf("Arquivo '%s' não encontrado.\n", nomeArquivo);
        return 1;
    }

    if (strcmp(tipoEstrutura, "lista") == 0){

        clock_t inicioTempo = clock();

        Indice indice = criaIndex(file);

        clock_t fimTempo = clock();
        double tempoLista = ((double)(fimTempo - inicioTempo)/CLOCKS_PER_SEC) * 1000.0;
        double tempoTotalLista = tempoLista + tempoParaAbrir;

        printf("Tipo de indice: '%s'\n", tipoEstrutura);
        printf("Arquivo texto: '%s'\n", nomeArquivo);
        printf("Numero de linhas no arquivo: %d\n", indice.numeroDeLinhas);
        printf("Tempo para carregar o arquivo e construir o indice: %.4lf ms\n", tempoTotalLista);

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
                for (int i=0; word[i]; i++){
                    word[i] = tolower(word[i]);
                }

                inicioTempo = clock();
                Entrada *result = procuraPalavra(&indice, word);
                fimTempo = clock();
                double procuraTempo = ((double)(fimTempo - inicioTempo)/CLOCKS_PER_SEC) * 1000.0;

                if (result != NULL) {
                    printOcorrencias(result, linhas);
                } else {
                    printf("Palavra '%s' nao encontrada.\n", word);
                }

                printf("Tempo de busca: %.4lf ms\n", procuraTempo);
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

    else if (strcmp(tipoEstrutura, "arvore") == 0){
        char palavraBuscada[TAMANHOPALAVRA];
        char * linha;
        char * copia_ponteiro_linha;
        char * quebra_de_linha;
        char * palavra;	
        int contador_linha = 0;
        char indice[10];
        char busca[6];

        printf("Tipo de indice: 'arvore'\n");
        printf("Arquivo texto: '%s'\n", nomeArquivo);

        clock_t inicioArvore = clock();
        treeno *raiz = NULL;

        linha = (char *) malloc((TAMANHOLINHA + 1) * sizeof(char));

        while (fgets(linha, TAMANHOLINHA, file) != NULL) {
            contador_linha++;
            char *quebraDeLinha = strchr(linha, '\n');
            if (quebraDeLinha != NULL) {
                *quebraDeLinha = '\0';
            }

            char conteudoLinha[TAMANHOLINHA];
            strncpy(conteudoLinha, linha, TAMANHOLINHA - 1);
            conteudoLinha[TAMANHOLINHA - 1] = '\0';
            palavra = strtok(linha, " ");

            while (palavra != NULL) {
                for (int i = 0; palavra[i]; i++){
                    palavra[i] = tolower(palavra[i]);
                }
                raiz = inserirPalavra(raiz, palavra, contador_linha, conteudoLinha);
                palavra = strtok(NULL, " ");
            }
        }

        fclose(file);

        clock_t fimArvore = clock();
        double tempoArvore = ((double)(fimArvore - inicioArvore)/CLOCKS_PER_SEC) * 1000.0;
        double tempoTotalArvore = tempoArvore + tempoParaAbrir;

        printf("Numero de linhas no arquivo: %d\n", contador_linha);
        printf("Tempo para carregar o arquivo e construir o indice: %.4f ms\n ", tempoTotalArvore);

        while (1) {

            printf("> ");
            scanf("%s", busca);

            if (strcmp(busca, "fim") == 0)
                break;

            if (strcmp(busca, "busca") == 0){

                clock_t inicioBusca = clock();
                scanf("%s", palavraBuscada);
                for (int i = 0; palavraBuscada[i]; i++){
                    palavraBuscada[i] = tolower(palavraBuscada[i]);
                }
                TreeVerificarPalavra(raiz, palavraBuscada);
                clock_t fimBusca = clock();
                double tempoTotalBusca = ((double)(fimBusca - inicioBusca) / CLOCKS_PER_SEC) * 1000.0;
                printf("Tempo de busca: %.4f\n", tempoTotalBusca);

            }

            else {
                printf("Opcao invalida!\n");
                while (getchar() != '\n');
            }
        }
    }

    return 0;
}
    