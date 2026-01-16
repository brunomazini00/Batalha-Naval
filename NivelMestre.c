#include <stdio.h>
#include <stdlib.h> // Necessário para função abs()

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // Tamanho da matriz da habilidade (5x5)
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5 // Valor para representar a área afetada

int main() {
    
    int tabuleiro[TAMANHO][TAMANHO] = {AGUA};
    int i, j, k;

    // Declaração dos Navios
    int navioHorizontal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};


    // Navio 1 - Horizontal 
    int linhaNavio1 = 2, colunaNavio1 = 2;
    if (colunaNavio1 + TAMANHO_NAVIO <= TAMANHO) {
        for (k = 0; k < TAMANHO_NAVIO; k++) tabuleiro[linhaNavio1][colunaNavio1 + k] = NAVIO;
    }

    // Navio 2 - Vertical
    int linhaNavio2 = 5, colunaNavio2 = 8;
    if (linhaNavio2 + TAMANHO_NAVIO <= TAMANHO) {
        for (k = 0; k < TAMANHO_NAVIO; k++) tabuleiro[linhaNavio2 + k][colunaNavio2] = NAVIO;
    }

    // Navio 3 - Diagonal Principal
    int linhaNavio3 = 5, colunaNavio3 = 3;
    if (linhaNavio3 + TAMANHO_NAVIO <= TAMANHO && colunaNavio3 + TAMANHO_NAVIO <= TAMANHO) {
        for (k = 0; k < TAMANHO_NAVIO; k++) tabuleiro[linhaNavio3 + k][colunaNavio3 + k] = NAVIO;
    }

    // Navio 4 - Diagonal Secundária
    int linhaNavio4 = 2, colunaNavio4 = 7;
    if (linhaNavio4 + TAMANHO_NAVIO <= TAMANHO && colunaNavio4 - (TAMANHO_NAVIO - 1) >= 0) {
        for (k = 0; k < TAMANHO_NAVIO; k++) tabuleiro[linhaNavio4 + k][colunaNavio4 - k] = NAVIO;
    }

    // Definição das Matrizes de Habilidade (5x5)
    int matrizCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Centro da matriz de habilidade 
    int centroHabilidade = TAMANHO_HABILIDADE / 2; // Índice 2 em uma matriz 5x5

    // Construção Dinâmica das Matrizes (Loops e Condicionais)
    printf("\nGerando matrizes de habilidade...\n");

    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            // CONE: Triângulo com base voltada para baixo
            // Exemplo visual: Linha 0 (1 ponto), Linha 1 (3 pontos), Linha 2 (5 pontos)
            if (i <= 2 && j >= (centroHabilidade - i) && j <= (centroHabilidade + i)) {
                matrizCone[i][j] = 1;
            } else {
                matrizCone[i][j] = 0;
            }

            // CRUZ: Linha central completa OU Coluna central completa
            if (i == centroHabilidade || j == centroHabilidade) {
                matrizCruz[i][j] = 1;
            } else {
                matrizCruz[i][j] = 0;
            }

            // OCTAEDRO (Losango)
            if (abs(i - centroHabilidade) + abs(j - centroHabilidade) <= 1) {
                matrizOctaedro[i][j] = 1;
            } else {
                matrizOctaedro[i][j] = 0;
            }
        }
    }

    // Aplicação das Habilidades no Tabuleiro
    // Definindo os pontos de origem (alvos) no tabuleiro principal
    int origemConeL = 0, origemConeC = 4;      // Cone no topo
    int origemCruzL = 4, origemCruzC = 4;      // Cruz no meio
    int origemOctaL = 7, origemOctaC = 1;      // Octaedro embaixo na esquerda

    int l_tabuleiro, c_tabuleiro; // Variáveis auxiliares para posição global

    // APLICAR CONE
    // Ponto de origem: Topo do cone (linha 0 da matriz coincide com origem)
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (matrizCone[i][j] == 1) {
                // Cálculo de posição:
                // Linha: Origem + i
                // Coluna: Origem + (j - centro) -> para alinhar o centro da matriz com a coluna de origem
                l_tabuleiro = origemConeL + i;
                c_tabuleiro = origemConeC + (j - centroHabilidade);

                // Verificação de Limites 
                if (l_tabuleiro >= 0 && l_tabuleiro < TAMANHO && c_tabuleiro >= 0 && c_tabuleiro < TAMANHO) {
                    tabuleiro[l_tabuleiro][c_tabuleiro] = HABILIDADE;
                }
            }
        }
    }

    // APLICAR CRUZ
    // Ponto de origem: Centro da Cruz
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (matrizCruz[i][j] == 1) {
                // Cálculo relativo ao centro
                l_tabuleiro = origemCruzL + (i - centroHabilidade);
                c_tabuleiro = origemCruzC + (j - centroHabilidade);

                if (l_tabuleiro >= 0 && l_tabuleiro < TAMANHO && c_tabuleiro >= 0 && c_tabuleiro < TAMANHO) {
                    tabuleiro[l_tabuleiro][c_tabuleiro] = HABILIDADE;
                }
            }
        }
    }

    // APLICAR OCTAEDRO
    // Ponto de origem: Centro do Octaedro
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (matrizOctaedro[i][j] == 1) {
                // Cálculo relativo ao centro
                l_tabuleiro = origemOctaL + (i - centroHabilidade);
                c_tabuleiro = origemOctaC + (j - centroHabilidade);

                if (l_tabuleiro >= 0 && l_tabuleiro < TAMANHO && c_tabuleiro >= 0 && c_tabuleiro < TAMANHO) {
                    tabuleiro[l_tabuleiro][c_tabuleiro] = HABILIDADE;
                }
            }
        }
    }


    printf("\n*************** BATALHA NAVAL ***************\n");
    printf("Legenda: 0 = Água | 3 = Navio | 5 = Habilidade\n\n");
    printf("    A B C D E F G H I J\n");

    for (i = 0; i < TAMANHO; i++) {
        printf("%2d |", i + 1);
        for (j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}