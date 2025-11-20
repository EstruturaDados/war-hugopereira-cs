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

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int numTropas;
};

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa.
void inicializarTerritorios(struct Territorio* territorios);
void faseDeAtaque(struct Territorio* territorios);
void simularAtaque(struct Territorio* territorios, int atacante, int defensor);
void limparBufferEntrada();

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // Define o locale para português, permitindo suporte a caracteres acentuados e formatação regional.
    setlocale(LC_ALL, "Portuguese");

    // Chamada para inicializar o gerador de números aleatórios.
    srand((time(NULL)));
    // Aloca um array de estruturas Territorio na pilha (stack), dinamicamente.
    struct Territorio *territorios;
    territorios = (struct Territorio *) calloc(NUM_TERRITORIOS, sizeof(struct Territorio));
    
    // Verifica se alocação foi bem sucedida
    if (territorios == NULL) {
        printf("ERRO: Falha na alocação de memória.\n");
    };
    // Chama a função para inicializar os territórios, pedindo ao usuário para cadastrá-los e exibindo o mapa.
    inicializarTerritorios(territorios);


    return 0;
};

// --- Implementação das Funções ---
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritorios(struct Territorio* territorios) {
    printf("===================================\n\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf(" --- Cadastrando território %d --- \n", i + 1);
        printf("Nome do território: ");
        fgets(territorios[i].nome, TAM_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército (ex: Preto, Amarelo): ");
        fgets(territorios[i].corExercito, TAM_COR, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numTropas);
        limparBufferEntrada();
        printf("\n");
    }

    // Exibe listagem com os territórios cadastrados
    printf("\n===================================\n");
    printf("\n       MAPA DO MUNDO - ESTADO\n");
    printf("\n===================================\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
        printf("-------------------------\n");
    }
};

// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
void faseDeAtaque(struct Territorio* territorios) {
    int territorioAtacante;
    int territorioDefensor;
    printf("\n--- Fase de ataque ---\n");
    printf("Digite o território atacante (1 a 5, ou 0 para sair): ");
    scanf("%d", &territorioAtacante);
    limparBufferEntrada();
    
    // Valida se o atacante quer sair
    if (territorioAtacante == 0) {
        printf("Saindo da fase de ataque.\n");
        return;
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
void simularAtaque(struct Territorio* territorios, int atacante, int defensor) {
    // Gera números aleatórios para simular dados de batalha (1 a 6), eliminando a possibilidade de empate
    int dadoAtaque = 0;
    int dadoDefesa = 0;
    do {
        int dadoAtaque = rand() % 6 + 1;
        int dadoDefesa = rand() % 6 + 1;

    } while (dadoAtaque == dadoDefesa);
    
    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Atacante: %s (Dado: %d)\n", territorios[atacante].nome, dadoAtaque);
    printf("Defensor: %s (Dado: %d)\n", territorios[defensor].nome, dadoDefesa);
    
    // Compara os dados
    if (dadoAtaque >= dadoDefesa) {
        printf("\n>>> ATACANTE VENCEU! <<<\n");
        territorios[defensor].numTropas--;
        printf("%s perdeu 1 tropa. Tropas restantes: %d\n", territorios[defensor].nome, territorios[defensor].numTropas);
        
        // Verifica se o defensor perdeu o território
        if (territorios[defensor].numTropas == 0) {
            printf("\n!!! %s foi conquistado por %s !!!\n", territorios[defensor].nome, territorios[atacante].nome);
            // Transferir o território para o atacante
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);
            territorios[defensor].numTropas = 1;  // Coloca 1 tropa do atacante no novo território conquistado
        }
    } else {
        printf("\n>>> DEFENSOR VENCEU! <<<\n");
        printf("%s mantém o controle de %s!\n", territorios[defensor].nome, territorios[defensor].nome);
    }
    
    printf("===========================\n\n");
};// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
};