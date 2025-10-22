#include <stdio.h>
#include <string.h>

// Número fixo de territórios
#define TOTAL_TERRITORIOS 5

// ================================
// Definição da struct Territorio
// ================================
typedef struct {
    char nome[30];   // Nome do território
    char cor[20];    // Cor do exército dominante
    int tropas;      // Número de tropas
} Territorio;

// Função para remover o '\n' do final de strings lidas com fgets
void limparNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Função para limpar o buffer após uso de scanf
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Territorio territorios[TOTAL_TERRITORIOS]; // Vetor de 5 territórios

    printf("===== Cadastro de Territórios =====\n\n");

    // Leitura dos dados
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);

        // Nome do território
        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        limparNovaLinha(territorios[i].nome);

        // Cor do exército
        printf("Digite a cor do exército dominante: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        limparNovaLinha(territorios[i].cor);

        // Número de tropas
        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada(); // Limpar o buffer antes do próximo fgets

        printf("\n");
    }

    // Exibição dos dados
    printf("===== Estado Atual do Mapa =====\n\n");

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("------------------------------\n");
    }

    return 0;
}
