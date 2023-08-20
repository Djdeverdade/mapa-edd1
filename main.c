/*MAPA Estrutura de Dados I
 02/07/2023
 Djordan Lopes da Silva
 RA: 22073736-5
 Algoritmo escrito em DEV C++ WINDOWS OS (Compilar no mesmo para melhor experiência).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

// Constantes
#define sequenciaMaxima 101

// Estruturas
typedef struct nucleotideosNO {
    char nucleotideo;
    struct nucleotideosNO *proximo;
} noNucleotideo;

// Variáveis globais
typedef noNucleotideo *ptr_no;
ptr_no fila;
ptr_no pilha;
char sequenciaNucleotideos[sequenciaMaxima];

// Prototipação
char troca(ptr_no *fila);
void menuPrincipal();
void menuLerDNA();
void lerDNA_Auto();
void lerDNA_Manual();
void insereDNA(ptr_no *fila, void (*func)());
void inserir_fila(ptr_no *fila, char nuc);
void imprimir_fila(ptr_no fila, int print_type);
void limpar_fila(ptr_no *fila);
void limpar_pilha(ptr_no *pilha);
char removerDaFila(ptr_no *fila);
void inserir_pilha(ptr_no *pilha, char nucleotideo);
void imprimir_pilha(ptr_no pilha);

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");
    fila = NULL;
    pilha = NULL;
    menuPrincipal();
    return 0;
}

// Funções
void menuPrincipal() {
    int op = -1;
    do {
        system("cls");
        printf("+--------------------------------------------+\n");
        printf("¦               MENU PRINCIPAL               ¦\n");
        printf("¦--------------------------------------------¦\n");
        printf("¦  1 - Ler DNA                               ¦\n");
        printf("¦  0 - Sair                                  ¦\n");
        printf("+--------------------------------------------+\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        fflush(stdin);
        switch (op) {
            case 1:
                menuLerDNA();
                break;
            default:
                if (op != 0) {
                    printf("Opção inválida!\n");
                    system("pause");
                } else {
                    printf("\nSaindo do programa!\n");
                    break;
                }
                break;
        }
    } while (op != 0);
}

void menuLerDNA() {
    int op = -1;
    do {
        system("cls");
        printf("+--------------------------------------------+\n");
        printf("¦                  LER DNA                   ¦\n");
        printf("¦--------------------------------------------¦\n");
        printf("¦  1 - Ler DNA automaticamente               ¦\n");
        printf("¦  2 - Inserir DNA manualmente               ¦\n");
        printf("¦  0 - Voltar ao menu principal              ¦\n");
        printf("+--------------------------------------------+\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        fflush(stdin);
        switch (op) {
            case 1:
                insereDNA(&fila, lerDNA_Auto);
                break;
            case 2:
                insereDNA(&fila, lerDNA_Manual);
                break;
            default:
                if (op != 0) {
                    printf("Opção inválida!\n");
                    system("pause");
                } else {
                    break;
                }
                break;
        }
    } while (op != 0);
}

void lerDNA_Auto() {
    int tamanho, i;
    srand(time(NULL));
    system("cls");
    printf("+--------------------------------------------+\n");
    printf("¦           LER DNA AUTOMATICAMENTE          ¦\n");
    printf("+--------------------------------------------+\n");
    printf("Insira o tamanho do DNA (máximo 100): ");
    scanf("%d", &tamanho);
    fflush(stdin);
    for (i = 0; i < tamanho; i++) {
        int numero_aleatorio = rand() % 8;
        switch (numero_aleatorio) {
            case 0:
                sequenciaNucleotideos[i] = 'A';
                break;
            case 1:
                sequenciaNucleotideos[i] = 'C';
                break;
            case 2:
                sequenciaNucleotideos[i] = 'T';
                break;
            case 3:
                sequenciaNucleotideos[i] = 'G';
                break;
            case 4:
                sequenciaNucleotideos[i] = 'A';
                break;
            case 5:
                sequenciaNucleotideos[i] = 'C';
                break;
            case 6:
                sequenciaNucleotideos[i] = 'T';
                break;
            case 7:
                sequenciaNucleotideos[i] = 'G';
                break;
        }
    }
    sequenciaNucleotideos[tamanho] = '\0';
    i = 0;
    printf("\nSequencia: ");
    while (sequenciaNucleotideos[i] != '\0') {
        printf("%c", sequenciaNucleotideos[i]);
        fflush(stdout);
        usleep(200000);
        i++;
    }
    printf("\n");
}

void lerDNA_Manual() {
    int sequenciaValida;
    do {
        system("cls");
        printf("+----------------------------------+\n");
        printf("¦      INSERIR DNA MANUALMENTE     ¦\n");
        printf("+----------------------------------+\n");
        printf("Insira a sequência de nucleotídeos\n(A, C, T, G) do DNA (máximo de 100):\n");
        printf("\nSequencia: ");
        fgets(sequenciaNucleotideos, sequenciaMaxima, stdin);
        fflush(stdin);
        sequenciaNucleotideos[strcspn(sequenciaNucleotideos, "\r\n")] = '\0';
        int i = 0;
        sequenciaValida = 1;
        while (sequenciaNucleotideos[i] != '\0') {
            if (sequenciaNucleotideos[i] != 'A' && sequenciaNucleotideos[i] != 'T' &&
                sequenciaNucleotideos[i] != 'G' && sequenciaNucleotideos[i] != 'C' &&
                sequenciaNucleotideos[i] != 'a' && sequenciaNucleotideos[i] != 't' &&
                sequenciaNucleotideos[i] != 'g' && sequenciaNucleotideos[i] != 'c') {
                printf("Caractere inválido: %c\n", sequenciaNucleotideos[i]);
                sequenciaValida = 0;
                system("pause");
                break;
            }
            i++;
        }
    } while (!sequenciaValida);
}

void insereDNA(ptr_no *fila, void (*func)()) {
    int i = 0;
    char aux;
    (*func)();
    while (sequenciaNucleotideos[i] != '\0') {
        inserir_fila(fila, sequenciaNucleotideos[i]);
        i++;
    }
    i = 0;
    printf("\n");
    int type = 1;
    imprimir_fila(*fila, type);
  	while (sequenciaNucleotideos[i] != '\0'){
    	aux = troca(fila);
    	inserir_pilha(&pilha, aux);
    	i++;
	}
	imprimir_pilha(pilha);
    printf("\n");
    system("pause");
    limpar_fila(fila);
    limpar_pilha(&pilha);
}

void inserir_fila(ptr_no *fila, char nuc) {
    if (*fila == NULL) {
        *fila = (ptr_no)malloc(sizeof(noNucleotideo));
        (*fila)->nucleotideo = nuc;
        (*fila)->proximo = NULL;
    } else {
        ptr_no temp = *fila;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = (ptr_no)malloc(sizeof(noNucleotideo));
        temp = temp->proximo;
        temp->nucleotideo = nuc;
        temp->proximo = NULL;
    }
}

void imprimir_fila(ptr_no fila, int print_type) {
    switch (print_type){
        case 1:
            printf("Fila : ");
            while (fila != NULL) {
                printf("%c", fila->nucleotideo);
                fflush(stdout);
                usleep(200000);
                fila = fila->proximo;
            }
            printf("\n");
            fflush(stdout);
            usleep(200000);
            break;
        case 2:
            printf("Fila: ");
            while (fila != NULL) {
                printf("%c", fila->nucleotideo);
                fila = fila->proximo;
            }
            printf("\n");
            break;
    }
}

char removerDaFila(ptr_no *fila){
    ptr_no atual;
    char nuc = (*fila)->nucleotideo;
    atual = (ptr_no) malloc(sizeof(noNucleotideo));
    atual = *fila;
    if(atual->proximo != NULL){
        *fila = (*fila)->proximo;
        atual->proximo = (*fila)->proximo;
    }
    return nuc;
}

void limpar_fila(ptr_no *fila) {
    ptr_no atual = *fila;
    while (atual != NULL) {
        ptr_no proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *fila = NULL;
}

char troca(ptr_no *fila){
    char aux = removerDaFila(fila);
    if(aux == 'A' || aux == 'a'){
        aux = 'T';
    }else if(aux == 'T' || aux == 't'){
        aux = 'A';
    }else if(aux == 'G' || aux == 'g'){
        aux = 'C';
    }else if(aux == 'C' || aux == 'c'){
        aux = 'G';
    }
    return aux;
}

void inserir_pilha(ptr_no *pilha, char nucleotideo) {
    ptr_no novo_no = (ptr_no)malloc(sizeof(noNucleotideo));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para o novo nó da pilha.\n");
        return;
    }
    novo_no->nucleotideo = nucleotideo;
    novo_no->proximo = *pilha;
    *pilha = novo_no;
}

void imprimir_pilha(ptr_no pilha){
	printf("Pilha: ");
    while (pilha != NULL) {
        printf("%c", pilha->nucleotideo);
        fflush(stdout);
        usleep(200000);
        pilha = pilha->proximo;
    }
    printf("\n");
    fflush(stdout);
    usleep(200000);
}

void limpar_pilha(ptr_no *pilha) {
    ptr_no atual = *pilha;
    while (atual != NULL) {
        ptr_no proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *pilha = NULL;
}
