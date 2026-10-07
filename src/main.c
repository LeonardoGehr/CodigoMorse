#include <stdio.h>

int main(void) {
    int opcao;
    char entrada[64];
    for (;;) {
        printf("\nCodigo Morse\n1 - Codificar texto\n2 - Decodificar Morse\n3 - Codificar arquivo\n4 - Decodificar arquivo\n5 - Mostrar arvore\n0 - Encerrar\nOpcao: ");
        if (fgets(entrada, sizeof entrada, stdin) == NULL) {
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
        if (opcao >= 1 && opcao <= 5) {
            puts("Funcionalidade ainda em desenvolvimento.");
        } else {
            puts("Opcao invalida.");
        }
    }
    return 0;
}