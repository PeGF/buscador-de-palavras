#include "structs.h"

int main(){
    FILE* in;
    char palavraBuscada[TAMANHOPALAVRA];
    char * linha;
    char * quebra_de_linha;
    int contador_linha = 1;
	char * copia_ponteiro_linha;
    char* palavra;
    char nomeArquivo[50];
    char indice[10];
    char busca[6];


    scanf("%s %s", nomeArquivo, indice);

    if (strcmp(indice, "lista") == 0){
    
    clock_t inicio = clock();
    // Inicializar a lista ligada
    no *lista = NULL;

    printf("Tipo de indice: 'lista'\n");
    printf("Arquivo texto: '%s'\n", nomeArquivo);


    in = fopen(nomeArquivo, "r");
    if (in == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    
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
return 0;
}