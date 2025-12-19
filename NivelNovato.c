#include <stdio.h>

#define TAMANHO 10 // Constante de tamanho para facilitar mudanças futuras
#define TAMANHO_NAVIO 3 // Constante para tamanho do Navio

int main() {

    int tabuleiro[TAMANHO][TAMANHO] = {0}; // Inicialização da Matriz 10x10 com posições {0}
    int i, j, k; // Variáveis para controlar os loops

    // Declaração dos Navios (Vetores unidimensionais)
    int navioHorizontal[TAMANHO_NAVIO] = {3, 3, 3};
    int navioVertical[TAMANHO_NAVIO] = {3, 3, 3};

    // --- POSICIONAMENTO DOS NAVIOS ---

    // Navio 1 - Horizontal
    int linhaNavio1 = 2;
    int colunaNavio1 = 2;

    // VALIDAÇÃO 1: verificação se o navio cabe no limite horizontal
    if (colunaNavio1 + TAMANHO_NAVIO <= TAMANHO) {
        for (k = 0; k < TAMANHO_NAVIO; k++) {
            // VALIDAÇÃO 2: verificação se a posição já esta ocupada
            if (tabuleiro[linhaNavio1][colunaNavio1 + k] == 0) {
                tabuleiro[linhaNavio1][colunaNavio1 + k] = navioHorizontal[k];
            } else {
                printf("Erro: Sobreposição detectada no navio horizontal na posição %d,%d!\n", linhaNavio1, colunaNavio1 + k);
            }
        }
    } else {
        printf("Erro: Navio Horizontal ultrapassa o limite do tabuleiro!\n");
    }

    // Navio 2 - Vertical
    int linhaNavio2 = 5;
    int colunaNavio2 = 8;

    // VALIDAÇÃO 1: verificação se o navio cabe no limite vertical
    if (linhaNavio2 + TAMANHO_NAVIO <= TAMANHO) {
        for (k = 0; k < TAMANHO_NAVIO; k++) {
            // VALIDAÇÃO 2: verificação se a posição já esta ocupada
            if (tabuleiro[linhaNavio2 + k][colunaNavio2] == 0) {
                tabuleiro[linhaNavio2 + k][colunaNavio2] = navioVertical[k];
            } else {
                printf("Erro: Sobreposição detectada no navio vertical na posição %d,%d!\n", linhaNavio2 + k, colunaNavio2);
            }
        }
    } else {
        printf("Erro: Navio Vertical ultrapassa o limite do tabuleiro!\n");
    }

    // --- Exibição do Tabuleiro ---
    printf("\n*************** BATALHA NAVAL ***************\n");
    printf("   A B C D E F G H I J\n"); // Cabeçalho das colunas

    // Loop Externo (Linhas)
    for (i = 0; i < TAMANHO; i++) {
        printf("%2d ", i + 1); // Cabeçalho das linhas
        // Loop Interno (Colunas)
        for (j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}