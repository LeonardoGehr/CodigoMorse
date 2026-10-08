#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MorseNode {
    char caractere;
    struct MorseNode *esquerda;
    struct MorseNode *direita;
} MorseNode;

MorseNode *criarNo(char caractere) {
    MorseNode *no = malloc(sizeof *no);
    if (no != NULL) {
        no->caractere = caractere;
        no->esquerda = NULL;
        no->direita = NULL;
    }
    return no;
}

int inserir(MorseNode *raiz, const char *codigo, char caractere) {
    MorseNode *atual = raiz;
    for (size_t i = 0; codigo[i] != '\0'; i++) {
        MorseNode **filho;
        if (codigo[i] == '.') {
            filho = &atual->esquerda;
        } else if (codigo[i] == '-') {
            filho = &atual->direita;
        } else {
            return 0;
        }
        if (*filho == NULL) {
            *filho = criarNo('\0');
            if (*filho == NULL) {
                return 0;
            }
        }
        atual = *filho;
    }
    atual->caractere = caractere;
    return 1;
}

int construirArvore(MorseNode *raiz) {
    /* Chamadas explicitas de insercao, conforme o enunciado. */
    return inserir(raiz, ".-", 'A') &&
           inserir(raiz, "-...", 'B') &&
           inserir(raiz, "-.-.", 'C') &&
           inserir(raiz, "-..", 'D') &&
           inserir(raiz, ".", 'E') &&
           inserir(raiz, "..-.", 'F') &&
           inserir(raiz, "--.", 'G') &&
           inserir(raiz, "....", 'H') &&
           inserir(raiz, "..", 'I') &&
           inserir(raiz, ".---", 'J') &&
           inserir(raiz, "-.-", 'K') &&
           inserir(raiz, ".-..", 'L') &&
           inserir(raiz, "--", 'M') &&
           inserir(raiz, "-.", 'N') &&
           inserir(raiz, "---", 'O') &&
           inserir(raiz, ".--.", 'P') &&
           inserir(raiz, "--.-", 'Q') &&
           inserir(raiz, ".-.", 'R') &&
           inserir(raiz, "...", 'S') &&
           inserir(raiz, "-", 'T') &&
           inserir(raiz, "..-", 'U') &&
           inserir(raiz, "...-", 'V') &&
           inserir(raiz, ".--", 'W') &&
           inserir(raiz, "-..-", 'X') &&
           inserir(raiz, "-.--", 'Y') &&
           inserir(raiz, "--..", 'Z') &&
           inserir(raiz, "-----", '0') &&
           inserir(raiz, ".----", '1') &&
           inserir(raiz, "..---", '2') &&
           inserir(raiz, "...--", '3') &&
           inserir(raiz, "....-", '4') &&
           inserir(raiz, ".....", '5') &&
           inserir(raiz, "-....", '6') &&
           inserir(raiz, "--...", '7') &&
           inserir(raiz, "---..", '8') &&
           inserir(raiz, "----.", '9');
}
char decodificarLetra(const MorseNode *raiz, const char *codigo) {
    const MorseNode *atual = raiz;
    if (codigo[0] == '\0') {
        return '\0';
    }
    for (size_t i = 0; codigo[i] != '\0'; i++) {
        if (codigo[i] == '.') {
            atual = atual->esquerda;
        } else if (codigo[i] == '-') {
            atual = atual->direita;
        } else {
            return '\0';
        }
        if (atual == NULL) {
            return '\0';
        }
    }
    return atual->caractere;
}

void mostrarArvore(const MorseNode *no, int nivel, const char *ligacao) {
    if (no == NULL) {
        return;
    }
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("%s: ", ligacao);
    if (no->caractere == '\0') {
        puts("[sem caractere]");
    } else {
        printf("%c\n", no->caractere);
    }
    mostrarArvore(no->esquerda, nivel + 1, ". (esquerda)");
    mostrarArvore(no->direita, nivel + 1, "- (direita)");
}

void liberarArvore(MorseNode *no) {
    if (no != NULL) {
        liberarArvore(no->esquerda);
        liberarArvore(no->direita);
        free(no);
    }
}

int lerLinha(char *entrada, int capacidade) {
    if (fgets(entrada, capacidade, stdin) == NULL) {
        return 0;
    }
    char *fim = strchr(entrada, '\n');
    if (fim != NULL) {
        *fim = '\0';
    } else {
        int c = getchar();
        if (c != EOF) {
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
            entrada[0] = '\0';
            puts("Entrada muito longa.");
        }
    }
    return 1;
}

int main(void) {
    MorseNode *raiz = criarNo('\0');
    if (raiz == NULL || !construirArvore(raiz)) {
        fputs("Nao foi possivel criar a arvore.\n", stderr);
        liberarArvore(raiz);
        return EXIT_FAILURE;
    }

    int opcao;
    char entrada[128];
    for (;;) {
        printf("\nCodigo Morse\n1 - Codificar texto\n2 - Decodificar Morse\n3 - Codificar arquivo\n4 - Decodificar arquivo\n5 - Mostrar arvore\n0 - Encerrar\nOpcao: ");
        if (!lerLinha(entrada, sizeof entrada)) {
            break;
        }
        char extra;
        if (sscanf(entrada, "%d %c", &opcao, &extra) != 1) {
            puts("Digite uma opcao numerica valida.");
            continue;
        }
        if (opcao == 0) {
            break;
        }
        if (opcao == 2) {
            printf("Digite o codigo Morse de uma letra ou numero: ");
            if (!lerLinha(entrada, sizeof entrada)) {
                break;
            }
            char letra = decodificarLetra(raiz, entrada);
            if (letra == '\0') {
                puts("Codigo invalido ou ainda nao cadastrado.");
            } else {
                printf("Resultado: %c\n", letra);
            }
        } else if (opcao == 5) {
            mostrarArvore(raiz, 0, "Raiz");
        } else if (opcao >= 1 && opcao <= 4) {
            puts("Funcionalidade ainda em desenvolvimento.");
        } else {
            puts("Opcao invalida.");
        }
    }
    liberarArvore(raiz);
    return EXIT_SUCCESS;
}