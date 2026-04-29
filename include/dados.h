// x vai de 0-800 ||| e y vai de 0-600 ||| como definido na em main.c
// x -> Esquerda - Direita ||| y -> Cima - Baixo
// stdbool.h

// float para posição/movimento.
// -------------------------------
// int para pontuação, chances e tipo.
// -------------------------------
// bool para verdadeiro/falso.
// -------------------------------
// Defensor *barreira aponta para o primeiro defensor da lista encadeada.
// -------------------------------
// struct `Defensor *proximo` liga um defensor ao próximo
// -------------------------------

#include <stdbool.h>

typedef struct {
  float x;
  float y;
  float velocidade_x;
  float velocidade_y;
  float potencia;
  float curva;
  bool em_movimento;
} Bola;

typedef struct {
  float x;
  float y;
  float largura;
  float altura;
  float velocidade;
  bool esta_pulando;
} Goleiro;

typedef struct {
  float x;
  float y;
  float largura;
  float altura;
  bool esta_pulando;
  struct Defensor
      *proximo; // Cada defensor guarda um ponteiro para o próximo defensor.
} Defensor;

typedef struct {
  float x;
  float y;
  float largura;
  float altura;
  float valor_atual;
  float velocidade;
  int direcao_movimento;
  bool ativo;
  int tipo;
} Medidor;

typedef struct {
  int estado_atual;
  int pontuacao_atual;
  int chances_restantes;
  Bola bola;
  // Guarda os dados usados na bola na cobrança atual.

  Goleiro goleiro;
  // Guarda os dados do goleiro, como posição, tamanho e movimento.

  Defensor *barreira;
  // Ponteiro para o primeiro defensor da lista encadeada da barreira.

  Medidor medidor_atual;
  // Guarda o medidor que está ativo no momento da cobrança.
} Jogo;

typedef struct {
  char nome[50];
  int pontuacao;
} Score;
