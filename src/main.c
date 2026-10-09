#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

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

/* Busca o caractere na arvore e registra o caminho percorrido. */
int buscarCodigo(const MorseNode *no, char letra, char *codigo, size_t nivel) {
    if (no == NULL) {
        return 0;
    }
    if (no->caractere == letra) {
        codigo[nivel] = '\0';
        return 1;
    }
    if (nivel == 5) {
        return 0;
    }
    codigo[nivel] = '.';
    if (buscarCodigo(no->esquerda, letra, codigo, nivel + 1)) {
        return 1;
    }
    codigo[nivel] = '-';
    return buscarCodigo(no->direita, letra, codigo, nivel + 1);
}

int codificarTexto(const MorseNode *raiz, const char *texto, char *saida) {
    size_t tamanho = 0;
    for (size_t i = 0; texto[i] != '\0'; i++) {
        char letra = texto[i];
        char codigo[6];
        if (letra >= 'a' && letra <= 'z') {
            letra = (char)(letra - 'a' + 'A');
        }
        if (letra == ' ') {
            strcpy(codigo, "/");
        } else if (!buscarCodigo(raiz, letra, codigo, 0)) {
            puts("Texto invalido: use letras A-Z, numeros e espacos, sem acentos.");
            return 0;
        }
        if (i != 0) {
            saida[tamanho++] = ' ';
        }
        size_t quantidade = strlen(codigo);
        memcpy(saida + tamanho, codigo, quantidade);
        tamanho += quantidade;
    }
    saida[tamanho] = '\0';
    return 1;
}

int decodificarTexto(const MorseNode *raiz, const char *morse, char *saida) {
    char codigo[6];
    size_t tamanhoCodigo = 0;
    size_t tamanhoSaida = 0;
    for (size_t i = 0;; i++) {
        char c = morse[i];
        if (c == '.' || c == '-') {
            if (tamanhoCodigo == 5) {
                puts("Codigo Morse invalido: sequencia muito longa.");
                return 0;
            }
            codigo[tamanhoCodigo++] = c;
        } else if (c == ' ' || c == '/' || c == '\0') {
            if (tamanhoCodigo != 0) {
                codigo[tamanhoCodigo] = '\0';
                char letra = decodificarLetra(raiz, codigo);
                if (letra == '\0') {
                    puts("Codigo Morse invalido: simbolo nao cadastrado.");
                    return 0;
                }
                saida[tamanhoSaida++] = letra;
                tamanhoCodigo = 0;
            }
            if (c == '/') {
                saida[tamanhoSaida++] = ' ';
            }
            if (c == '\0') {
                break;
            }
        } else {
            puts("Morse invalido: use somente ponto, traco, barra e espaco.");
            return 0;
        }
    }
    saida[tamanhoSaida] = '\0';
    return 1;
}

/* Leitura binaria preserva quebras de linha para validar o arquivo Morse. */
char *lerArquivo(const char *caminho) {
    FILE *arquivo = fopen(caminho, "rb");
    if (arquivo == NULL) {
        puts("Nao foi possivel abrir o arquivo. Confira o caminho e as permissoes.");
        return NULL;
    }
    size_t capacidade = 1024;
    size_t tamanho = 0;
    char *texto = malloc(capacidade);
    if (texto == NULL) {
        fclose(arquivo);
        puts("Memoria insuficiente.");
        return NULL;
    }
    int c;
    while ((c = fgetc(arquivo)) != EOF) {
        if (c == '\0') {
            puts("Arquivo invalido: contem byte nulo.");
            free(texto);
            fclose(arquivo);
            return NULL;
        }
        if (tamanho == capacidade - 1) {
            if (capacidade > SIZE_MAX / 2) {
                puts("Arquivo muito grande.");
                free(texto);
                fclose(arquivo);
                return NULL;
            }
            char *novo = realloc(texto, capacidade * 2);
            if (novo == NULL) {
                puts("Memoria insuficiente.");
                free(texto);
                fclose(arquivo);
                return NULL;
            }
            texto = novo;
            capacidade *= 2;
        }
        texto[tamanho++] = (char)c;
    }
    int erro = ferror(arquivo);
    fclose(arquivo);
    if (erro || tamanho == 0) {
        puts(erro ? "Erro ao ler o arquivo." : "Arquivo vazio.");
        free(texto);
        return NULL;
    }
    texto[tamanho] = '\0';
    return texto;
}

void converterArquivo(const MorseNode *raiz, const char *caminho, int codificar) {
    char *texto = lerArquivo(caminho);
    if (texto == NULL) {
        return;
    }
    if (codificar) {
        size_t destino = 0;
        for (size_t origem = 0; texto[origem] != '\0'; origem++) {
            if (texto[origem] == '\r') {
                if (texto[origem + 1] == '\n') {
                    origem++;
                }
                texto[destino++] = ' ';
            } else {
                texto[destino++] = texto[origem] == '\n' ? ' ' : texto[origem];
            }
        }
        texto[destino] = '\0';
    }
    size_t tamanho = strlen(texto);
    if (tamanho > (SIZE_MAX - 1) / 6) {
        puts("Arquivo muito grande.");
        free(texto);
        return;
    }
    char *saida = malloc(tamanho * 6 + 1);
    if (saida == NULL) {
        puts("Memoria insuficiente.");
        free(texto);
        return;
    }
    int sucesso = codificar ? codificarTexto(raiz, texto, saida)
                           : decodificarTexto(raiz, texto, saida);
    if (sucesso) {
        printf("Resultado: %s\n", saida);
    }
    free(saida);
    free(texto);
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
        if (c != EOF && c != '\n') {
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
    char entrada[1024];
    
    /* Cada caractere de entrada gera no maximo 5 sinais e um separador. */
    char saida[sizeof entrada * 6];
    for (;;) {
        printf("\nCodigo Morse\n1 - Codificar texto\n2 - Decodificar Morse\n3 - Codificar arquivo\n4 - Decodificar arquivo\n5 - Mostrar arvore\n0 - Encerrar\nOpcao: ");
        if (!lerLinha(entrada, sizeof entrada)) {
            break;
        }
        char *fimOpcao;
        errno = 0;
        long valor = strtol(entrada, &fimOpcao, 10);
        if (fimOpcao == entrada || errno == ERANGE || valor < INT_MIN || valor > INT_MAX) {
            puts("Digite uma opcao numerica valida.");
            continue;
        }
        while (*fimOpcao == ' ' || *fimOpcao == '\t') {
            fimOpcao++;
        }
        if (*fimOpcao != '\0') {
            puts("Digite uma opcao numerica valida.");
            continue;
        }
        opcao = (int)valor;
        if (opcao == 0) {
            break;
        }
        if (opcao == 1 || opcao == 2) {
            printf("%s", opcao == 1 ? "Digite o texto: " : "Digite a mensagem Morse em uma linha: ");
            if (!lerLinha(entrada, sizeof entrada)) {
                break;
            }
            if (entrada[0] == '\0') {
                puts("Digite uma mensagem nao vazia.");
                continue;
            }
            int sucesso = opcao == 1
                ? codificarTexto(raiz, entrada, saida)
                : decodificarTexto(raiz, entrada, saida);
            if (sucesso) {
                printf("Resultado: %s\n", saida);
            }
        } else if (opcao == 5) {
            mostrarArvore(raiz, 0, "Raiz");
        } else if (opcao == 3 || opcao == 4) {
            printf("Caminho do arquivo (sem aspas): ");
            if (!lerLinha(entrada, sizeof entrada)) {
                break;
            }
            if (entrada[0] == '\0') {
                puts("Informe um caminho nao vazio.");
            } else {
                converterArquivo(raiz, entrada, opcao == 3);
            }
        } else {
            puts("Opcao invalida.");
        }
    }
    liberarArvore(raiz);
    return EXIT_SUCCESS;
}