#include <assert.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct RegistrosExcel
{
    int nmrContrato;
	int ano;
	char nmrProcesso[100];
	char ete[100];
	char municipio[100];
	char uf[100];
	char prestadora[100];
	char baciaHidrografica[100];
	char comite[100];
	char cpReceptor[100];    
} RegistrosExcel;

typedef RegistrosExcel TPExcel;

static void imprimir(int n, TPExcel *reg)
{
    int i = 0;
    for (i = 0; i < n; i++){
		printf("\tNúmero de contrato: %d\n", reg[i].nmrContrato);
        printf("\tAno: %d\n", reg[i].ano);
        printf("\tNúmero do processo: %s\n", reg[i].nmrProcesso);
        printf("\tEstação de tratamento: %s\n", reg[i].ete);
        printf("\tMunicípio: %s\n", reg[i].municipio);
        printf("\tUF: %s\n", reg[i].uf);
        printf("\tPrestadora: %s\n", reg[i].prestadora);
        printf("\tBacia hidrgráfica: %s\n", reg[i].baciaHidrografica);
        printf("\tComitê: %s\n", reg[i].comite);
        printf("\tCorpo receptor: %s\n", reg[i].cpReceptor);
        printf("\n");
	}
    fflush(stdout);
}

static void merge(TPExcel *reg, int inicio, int meio, int fim)
{
    int mergedSize = fim - inicio + 1;
    TPExcel *aux = (TPExcel *)malloc(mergedSize * sizeof(TPExcel));
    int mergePos = 0;
    int inicio1 = inicio;
    int inicio2 = meio + 1;

    while (inicio1 <= meio && inicio2 <= fim)
    {
        if (reg[inicio1].nmrContrato < reg[inicio2].nmrContrato)
        {
            aux[mergePos++] = reg[inicio1++];
        }
        else
        {
            aux[mergePos++] = reg[inicio2++];
        }
    }

    while (inicio1 <= meio)
    {
        aux[mergePos++] = reg[inicio1++];
    }

    while (inicio2 <= fim)
    {
        aux[mergePos++] = reg[inicio2++];
    }

    assert(mergePos == mergedSize);

    for (mergePos = 0; mergePos < mergedSize; ++mergePos)
        reg[inicio + mergePos] = aux[mergePos];

    free(aux);
}

static void mergeSort(TPExcel *reg, int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;

        mergeSort(reg, inicio, meio);
        mergeSort(reg, meio + 1, fim);

        merge(reg, inicio, meio, fim);
    }
}

int main(void) {
	
	setlocale(LC_ALL, "Portuguese");
	char arq[] = "prog_despolui.csv";
	FILE *arquivo = fopen(arq, "r");
	
	if (!arquivo) {
		printf("Não foi possível abrir o arquivo\n");
		return 0;
	}
	
	char buf[1024];
	int contLinha = 0;
	int contCampo = 0;
	int linha = 0;
	char novo[1024];
	
    int qtdLinhasExcel = 81;

    TPExcel *reg = (TPExcel *)malloc(qtdLinhasExcel * sizeof(TPExcel));	
		
	while (fgets(buf, 1024, arquivo)) {
		contCampo = 0;
		contLinha++;
		
		if (contLinha == 1) {
			continue;
		}
		
		char *campo = strtok(buf, ",");
		
		while (campo) {
			if (contCampo == 0) {
				strcpy(novo, campo);
				reg[linha].nmrContrato = atoi(novo);
			}
			if (contCampo == 1) {
				strcpy(novo, campo);
				reg[linha].ano = atoi(novo);
			}
			if (contCampo == 2) {
				strcpy(novo, campo);
				strcpy(reg[linha].nmrProcesso, novo);
			}
			if (contCampo == 3) {
				strcpy(novo, campo);
				strcpy(reg[linha].ete, novo);
				
			}
			if (contCampo == 4) {
				strcpy(novo, campo);
				strcpy(reg[linha].municipio, novo);
			}
			if (contCampo == 5) {
				strcpy(novo, campo);
				strcpy(reg[linha].uf, novo);
			}
			if (contCampo == 6) {
				strcpy(novo, campo);
				strcpy(reg[linha].prestadora, novo);
			}
			if (contCampo == 7) {
				strcpy(novo, campo);
				strcpy(reg[linha].baciaHidrografica, novo);
			}
			if (contCampo == 8) {
				strcpy(novo, campo);
				strcpy(reg[linha].comite, novo);
			}
			if (contCampo == 9) {
				strcpy(novo, campo);
				strcpy(reg[linha].cpReceptor, novo);
			}
			campo = strtok(NULL, ",");
			contCampo++;
		}
		linha++;
	}
	
    mergeSort(reg, 0, linha - 1);
    imprimir(linha, reg);    
	fclose(arquivo);
	free(reg);
	
	return 0;	
}
