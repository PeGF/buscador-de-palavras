
typedef struct {
    char palavra[40];
    int *ocorrencias;
    int contador;
} Entrada;

typedef struct {
    Entrada *entrada;
    int tamanho;
    int numeroDeLinhas;
} Indice;

void adicionaOcorrencia(Entrada *entrada, int numeroLinha);
Entrada novaPalavra(char *palavra, int numeroLinha);
Entrada *procuraPalavra(Indice *indice, char *palavra);
Indice criaIndex(FILE *file);
void printOcorrencias(Entrada *entrada, char **linhas);