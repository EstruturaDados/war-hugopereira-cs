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
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
void inicializarTerritorios(struct Territorio* territorios);
void limparBufferEntrada();

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // Define o locale para português, permitindo suporte a caracteres acentuados e formatação regional.
    setlocale(LC_ALL, "Portuguese");

    // Aloca um array de estruturas Territorio na pilha (stack) com tamanho fixo de NUM_TERRITORIOS elementos.
    struct Territorio territorios[NUM_TERRITORIOS];
    
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

// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
};