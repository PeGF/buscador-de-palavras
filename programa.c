#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvore.c"
#include "listaLigada.c"

int main(int argc, char ** argv){

	FILE * in;
    char palavraBuscada[TAMANHOPALAVRA];
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;	
	int contador_linha = 1;
    char nomeArquivo[50];
    char indice[10];
    char busca[6];

    if(argc == 2) {

		in = fopen(argv[1], "r");

		printf(">>>>> Carregando arquivo...\n");

		contador_linha = 0;
 		linha = (char *) malloc((TAMANHOLINHA + 1) * sizeof(char));

    }

    scanf("%s", indice);

    if (strcmp(indice, "lista") == 0){
    
    clock_t inicio = clock();
    // Inicializar a lista ligada
    no *lista = NULL;

    printf("Tipo de indice: 'lista'\n");
    printf("Arquivo texto: '%s'\n", argv[1]);



    
    linha = (char *) malloc((TAMANHOLINHA + 1) * sizeof(char));

		while(in && fgets(linha, TAMANHOLINHA, in)){
			
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

            copia_ponteiro_linha = linha;

			while( (palavra = strsep(&copia_ponteiro_linha, " ")) )
            inserirNaLista(&lista, palavra, contador_linha);

            
            contador_linha++;
            }

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)/CLOCKS_PER_SEC) * 1000.0;

    printf("Numero de linhas no arquivo: %d\n", contador_linha);
    printf("Tempo para carregar o arquivo e construir o indice: %.4f ms\n ", tempo);

    while (1){
    clock_t inicio = clock();

    printf("> ");
    scanf("%s", busca);

    if (strcmp(busca, "fim") == 0)
        break;

    if (strcmp(busca, "busca") == 0){
        scanf("%s", palavraBuscada);
        verificarPalavra(lista, palavraBuscada);
    }

    else{
        printf("Opcao invalida!\n");
        while (getchar() != '\n');
    }

    clock_t fim = clock();
    tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    printf("Tempo de busca: %.4f\n", tempo);

}

}

else if (strcmp(indice, "arvore") == 0){
    clock_t inicio = clock();
        treeno *raiz = NULL;

        printf("Tipo de indice: 'arvore'\n");
        printf("Arquivo texto: '%s'\n", argv[1]);

        in = fopen(argv[1], "r");
        if (in == NULL) {
            perror("Erro ao abrir o arquivo");
            return EXIT_FAILURE;
    }

        
        contador_linha = 0;
 		linha = (char *) malloc((TAMANHOLINHA + 1) * sizeof(char));

        while (fgets(linha, TAMANHOLINHA, in) != NULL) {
            contador_linha++;

            // Remove o caractere de nova linha, se presente
            char *quebraDeLinha = strchr(linha, '\n');
            if (quebraDeLinha != NULL) {
                *quebraDeLinha = '\0';
            }

            char conteudoLinha[TAMANHOLINHA];
            strncpy(conteudoLinha, linha, TAMANHOLINHA - 1);
            conteudoLinha[TAMANHOLINHA - 1] = '\0';


            // Tokeniza a linha para obter as palavras
            palavra = strtok(linha, " ");

            while (palavra != NULL) {
                // Inserir a palavra na árvore
                raiz = inserirPalavra(raiz, palavra, contador_linha, conteudoLinha);

                // Continua com a próxima palavra
                palavra = strtok(NULL, " ");
            }
        }

    fclose(in);
    printf(">>>>> Arquivo carregado!\n");

    

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)/CLOCKS_PER_SEC) * 1000.0;

    printf("Numero de linhas no arquivo: %d\n", contador_linha);
    printf("Tempo para carregar o arquivo e construir o indice: %.4f ms\n ", tempo);

    while (1){
    clock_t inicio = clock();

    printf("> ");
    scanf("%s", busca);

    if (strcmp(busca, "fim") == 0)
        break;

    if (strcmp(busca, "busca") == 0){
        scanf("%s", palavraBuscada);
        TreeVerificarPalavra(raiz, palavraBuscada);
    }

    else{
        printf("Opcao invalida!\n");
        while (getchar() != '\n');
    }

    clock_t fim = clock();
    tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    printf("Tempo de busca: %.4f\n", tempo);

    

}


}

return 0;
}