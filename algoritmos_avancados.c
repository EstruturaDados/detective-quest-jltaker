#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da sala
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/**
 * Cria uma sala com nome e aloca dinamicamente.
 */
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (nova == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a sala: %s\n", nome);
        exit(EXIT_FAILURE);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/**
 * Libera a memória de todas as salas da árvore binária.
 */
void liberarArvore(Sala* sala) {
    if (sala == NULL) return;
    liberarArvore(sala->esquerda);
    liberarArvore(sala->direita);
    free(sala);
}

/**
 * Permite a navegação interativa pela mansão.
 */
void explorarSalas(Sala* atual) {
    char escolha;
    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim da exploração. Sala sem saídas.\n");
            break;
        }

        printf("Escolha um caminho:\n");
        if (atual->esquerda != NULL) printf("  (e) Ir para a esquerda: %s\n", atual->esquerda->nome);
        if (atual->direita != NULL) printf("  (d) Ir para a direita: %s\n", atual->direita->nome);
        printf("  (s) Sair da mansão\n");
        printf("Sua escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e') {
            if (atual->esquerda != NULL) atual = atual->esquerda;
            else printf("Não há caminho à esquerda.\n");
        } else if (escolha == 'd') {
            if (atual->direita != NULL) atual = atual->direita;
            else printf("Não há caminho à direita.\n");
        } else if (escolha == 's') {
            printf("Exploração encerrada pelo jogador.\n");
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }
}

/**
 * Monta o mapa da mansão e inicia a exploração.
 */
int main() {
    Sala* hall = criarSala("Hall de entrada");
    Sala* salaEstar = criarSala("Sala de estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    printf("🕵️ Bem-vindo ao Detective Quest!\nExplore a mansão e descubra seus segredos...\n");
    explorarSalas(hall);

    liberarArvore(hall);
    return 0;
}