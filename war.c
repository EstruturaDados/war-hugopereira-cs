// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define NUM_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10
#define NUM_MISSOES 2
#define TAM_DESCRICAO 100

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int numTropas;
} Territorio;

// Define as missões, utilizando enumeração para os tipos de missão.
typedef enum {
    CONQUISTAR_TRES_TERRITORIOS = 0,
    ELIMINAR_EXERCITO_VERDE = 1
} TipoMIssao;

// Define a estrutura Missão.
typedef struct {
    TipoMIssao tipo;
    char descrissao[TAM_DESCRICAO];
    int concluida;
} Missao;

// Define a estrutura do jogador
typedef struct {
    char corJogador[TAM_COR];
    Missao missao;
} Jogador;

/*  --- PAREI AQUI!!! ---  */


// --- Protótipos das Funções ---
// Inicialização
void inicializarTerritoriosAutomatico(Territorio* territorios);
void atribuirMissao(Jogador* jogador);

// Exibição
void exibirMapa(const Territorio* territorios);
void exibirMenu();
void exibirMissao(const Jogador* jogador);

// Lógica de Jogo
void faseDeAtaque(Territorio* territorios, const Jogador* jogador);
void simularAtaque(Territorio* territorios, int atacante, int defensor);
int verificarMissao(const Territorio* territorios, Jogador* jogador);

// Utilitáias
void limparBufferEntrada();
int contarTerritoriosPorCor(const Territorio* territorios, const char* cor);
int existeExercitoCor(const Territorio* territorios, const char* cor);

// --- Função Principal (main) ---
int main() {
    // Define o locale para português, permitindo suporte a caracteres acentuados e formatação regional.
    setlocale(LC_ALL, "Portuguese");

    // Chamada para inicializar o gerador de números aleatórios.
    srand((time(NULL)));

    // Aloca um array de estruturas Territorio na pilha (stack), dinamicamente.
    Territorio *territorios;
    territorios = (Territorio *) calloc(NUM_TERRITORIOS, sizeof(Territorio));
    
    // Verifica se alocação foi bem sucedida
    if (territorios == NULL) {
        printf("ERRO: Falha na alocação de memória.\n");
    };

    // Configuração do jogador
    Jogador jogador;
    strcpy(jogador.corJogador, "Amarelo");
    jogador.missao.concluida = 0;
    
    // Inicialização automática
    inicializarTerritoriosAutomatico(territorios);
    atribuirMissao(&jogador);

    printf("===================================\n");
    printf("    BEM VINDO AO JOGO WAR!\n");
    printf("===================================\n");
    printf("\nVocê comanda o exército %s\n, jogador.corJogador");
    exibirMisaao(&jogador);

    
    int opcao;
    int jogoAtivo = 1;

    while (jogoAtivo) {
        exibirMapa(territorios);
        exibirMenu();
        
        printf("\nEscolha uma opção");
        if (scanf("%d", opcao) !=1) {
            limparBufferEntrada();
            printf("ERRO; Opção inválida!\n");
            continue;
        };
        limparBufferEntrada();

        switch(opcao) {
            case 1:
                faseDeAtaque(territorios, &jogador);
                if (verificarMissao(territorios, &jogador)) {
                    jogoAtivo = 0;
                }
                break;
            case 2:
                exibirMissao(&jogador);
                if (verificarMissao(territorios, &jogador)) {
                    printf("\nParabéns!!! Você cumpriu sua Missão!\n");
                } else {
                    printf("\nVocẽ ainda não cumpriu sua missão. Continue a lutar!\n");
                }
                printf("\nPressione Enter para continuar jogando...\n");
                getchar();
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                printf("Jogo encerrado. Até a próxima!\n");
                jogoAtivo = 0;
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    }

    // Libera a memória alocada dinamicamente antes de encerrar o programa.
    free(territorios);

    return 0;
};

// --- Implementação das Funções ---
// Preenche, automaticamente, os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritoriosAutomatico(Territorio* territorios) {
    const char* nomes[] = {"America", "Europa", "Ásia", "África", "Oceania"};
    const char* cores[] = {"Amarelo", "Azul", "Vermelho", "Verde", "Preto"};
    const int tropas[] = {5, 5, 4, 3, 2};

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].corExercito, cores[i]);
        territorios[i].numTropas = tropas[i];
    }
};

// Atribui, aleatoriamente, uma missão ao jogador.
void atribuirMissao(Jogador* jogador) {
    jogador->missao.tipo = rand() % NUM_MISSOES;
    jogador->missao.concluida = 0;

    switch (jogador->missao.tipo) {
        case CONQUISTAR_TRES_TERRITORIOS:
            strcpy(jogador->missao.descrissao, "Conquistar 3 territórios.");
            break;
        case ELIMINAR_EXERCITO_VERDE:
            strcpy(jogador->missao.descrissao, "Eliminar o exército Azul.");
            break;
    }
};

void exibirMapa(const Territorio* territorios) {
    // Exibe listagem com os territórios cadastrados
    printf("\n========= MAPA DO MUNDO - ESTADO ATUAL =========\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d. %-15s (Exército: %-20s, Tropas: %d)\n", i + 1, territorios[i].nome, territorios[i].corExercito, territorios[i].numTropas);
    };
    printf("\n===================================\n");
};

// Exibe o menu principal
void exibirMenu() {
    printf("--- MENU DE AÇÕES ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");

};

// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
void faseDeAtaque(Territorio* territorios, const Jogador* jogador) {
    int territorioAtacante;
    int territorioDefensor;
    printf("\n--- Fase de ataque ---\n");
    printf("Digite o território atacante (1 a 5, ou 0 para sair): ");
    scanf("%d", &territorioAtacante);

    limparBufferEntrada();

    if (territorioAtacante == 0) {
        free(territorios);
        printf("Jogo encerrado e memória liberada. Até a próxima!\n");
        exit(0);
    }
    
    // Valida se o território atacante é válido
    if (territorioAtacante < 1 || territorioAtacante > NUM_TERRITORIOS) {
        printf("ERRO: Território atacante inválido!\n");
        return;
    }
    
    printf("Digite o território defensor (1 a 5): ");
    scanf("%d", &territorioDefensor);
    limparBufferEntrada();
    
    // Valida se o território defensor é válido
    if (territorioDefensor < 1 || territorioDefensor > NUM_TERRITORIOS) {
        printf("ERRO: Território defensor inválido!\n");
        return;
    }
    
    // Valida se o atacante tem tropas
    if (territorios[territorioAtacante - 1].numTropas == 0) {
        printf("ERRO: O território atacante não tem tropas!\n");
        return;
    }
    
    // Chama a função para simular o ataque
    simularAtaque(territorios, territorioAtacante - 1, territorioDefensor - 1);
};

// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
void simularAtaque(Territorio* territorios, int atacante, int defensor) {
    // Gera números aleatórios para simular dados de batalha (1 a 6)
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;
    
    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", territorios[atacante].nome, dadoAtaque);
    printf("O defensor %s rolou um dado e tirou: %d\n", territorios[defensor].nome, dadoDefesa);

    // Compara os dados
    if (dadoAtaque >= dadoDefesa) {
        territorios[defensor].numTropas--;
        printf("VITÓRIA DO ATAQUE!!! O defensor perdeu 1 tropa. Tropas restantes: %d\n", territorios[defensor].numTropas);

        // Verifica se o defensor perdeu o território
        if (territorios[defensor].numTropas == 0) {
            printf("\n!!! %s foi conquistado pelo exército %s !!!\n", territorios[defensor].nome, territorios[atacante].corExercito);
            // Transferir o território para o atacante
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);
            territorios[defensor].numTropas = 1;  // Coloca 1 tropa do atacante no novo território conquistado
        }
    } else {
        printf("VITÓRIA DO DEFENSOR!!! O defensor mantém o controle da tropa!\n");
    }
    
    printf("===================================\n\n");

    printf("Pressione Enter para ir para o próximo turno...");
    getchar();
};

// Verifica se o jogador cumpriu os objetivos da missão.
int verificarMissao(const Territorio* territorios, Jogador* jogador) {
    int missaoCumprida = 0;

    switch (jogador->missao.tipo) {
        case ELIMINAR_EXERCITO_VERDE:
            if(!existeExercitoCor(territorios, "Verde")) {
                missaoCumprida = 1;
            }
            break;
        case CONQUISTAR_TRES_TERRITORIOS:
            if (contarTerritoriosPorCor(territorios, jogador->corJogador) >= 3) {
                missaoCumprida = 1;
            }
            break;            
    }

    if (missaoCumprida) {
        jogador->missao.concluida = 1;
        printf("\n");
        printf("╔═══════════════════════════════════════╗\n");
        printf("║                                       ║\n");
        printf("║    🏆 PARABÉNS! VOCÊ VENCEU! 🏆       ║\n");
        printf("║                                       ║\n");
        printf("║    Missão cumprida com sucesso!       ║\n");
        printf("║                                       ║\n");
        printf("╚═══════════════════════════════════════╝\n");
        return 1;
    }

    return 0;
};

// Verifica quantos territorios foram conquistados pelo jogador.
int contarTerritoriosPorCor(const Territorio* territorios, const char* cor) {
    int contador = 0;

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(territorios[i].corExercito, cor) == 0) {
            contador++;
        }
    }
    return contador;
};

// Verifica se o exército inimigo ainda tem tropas no território.
int existeExercitoCor(const Territorio* territorios, const char* cor) {
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(territorios[i].corExercito, cor) == 0) {
            return 1;
        }
    }
    return 0;
}

// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
};