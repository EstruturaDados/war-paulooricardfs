#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5

// ============================
// Struct para representar um território
// ============================
typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
    int dono; // ID do jogador: 1 ou 2
} Territorio;

// ============================
// Remove '\n' do final da string
// ============================
void limparNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// ============================
// Limpa o buffer do teclado após scanf
// ============================
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ============================
// Função para cadastrar territórios
// ============================
void cadastrarTerritorios(Territorio *territorios) {
    printf("===== Cadastro de Territórios =====\n\n");

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        limparNovaLinha(territorios[i].nome);

        printf("Cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        limparNovaLinha(territorios[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();

        // Atribui dono alternado (1 ou 2)
        territorios[i].dono = (i % 2 == 0) ? 1 : 2;

        printf("\n");
    }
}

// ============================
// Função para exibir o estado atual do mapa
// ============================
void exibirMapa(Territorio *territorios) {
    printf("\n===== Estado Atual do Mapa =====\n\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("Dono: Jogador %d\n", territorios[i].dono);
        printf("------------------------------\n");
    }
}

// ============================
// Função para simular um ataque
// ============================
void simularAtaque(Territorio *territorios) {
    int atacante, defensor;

    printf("\n===== Fase de Ataque =====\n");
    printf("Escolha o número do território atacante (1 a 5): ");
    scanf("%d", &atacante);
    printf("Escolha o número do território defensor (1 a 5): ");
    scanf("%d", &defensor);
    limparBufferEntrada();

    atacante--; defensor--; // Ajustar índice

    // Verificações básicas
    if (atacante < 0 || atacante >= TOTAL_TERRITORIOS ||
        defensor < 0 || defensor >= TOTAL_TERRITORIOS) {
        printf("❌ Território inválido!\n");
        return;
    }

    if (atacante == defensor) {
        printf("❌ Um território não pode atacar a si mesmo!\n");
        return;
    }

    if (territorios[atacante].tropas < 1) {
        printf("❌ Território atacante não tem tropas suficientes!\n");
        return;
    }

    if (territorios[atacante].dono == territorios[defensor].dono) {
        printf("❌ Você não pode atacar seu próprio território!\n");
        return;
    }

    // Simular dados
    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\n🎲 Dados rolados:\n");
    printf("Atacante (%s): %d\n", territorios[atacante].nome, dadoAtq);
    printf("Defensor (%s): %d\n", territorios[defensor].nome, dadoDef);

    // Comparar dados
    if (dadoAtq >= dadoDef) {
        territorios[defensor].tropas--;
        printf("✅ Ataque bem-sucedido! Defensor perdeu 1 tropa.\n");

        if (territorios[defensor].tropas <= 0) {
            printf("🏳️ Território conquistado! Agora pertence ao Jogador %d.\n",
                   territorios[atacante].dono);
            territorios[defensor].dono = territorios[atacante].dono;
            territorios[defensor].tropas = 1;
            territorios[atacante].tropas--; // Move uma tropa
        }
    } else {
        territorios[atacante].tropas--;
        printf("❌ Defesa bem-sucedida! Atacante perdeu 1 tropa.\n");
    }
}

// ============================
// Função principal
// ============================
int main() {
    srand(time(NULL)); // Inicializa semente aleatória

    // Alocação dinâmica com calloc
    Territorio *territorios = (Territorio *)calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(territorios);

    // Loop de ataque
    char continuar;
    do {
        exibirMapa(territorios);
        simularAtaque(territorios);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        limparBufferEntrada();

    } while (continuar == 's' || continuar == 'S');

    // Libera memória
    free(territorios);
    printf("\nFim do jogo. Memória liberada.\n");

    return 0;
}
