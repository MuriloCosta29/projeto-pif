#ifndef DADOS_H
#define DADOS_H

#include "audio.h"
#include <stdbool.h>

#define TORCIDA_LINHAS 5
#define TORCIDA_COLUNAS 14
#define MAX_TORCEDORES (TORCIDA_LINHAS * TORCIDA_COLUNAS)

typedef struct {
  float x;
  float y;
  float z;
  float velocidade_x;
  float velocidade_y;
  float velocidade_z;
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

typedef struct Defensor {
  float x;
  float y;
  float largura;
  float altura;
  bool esta_pulando;
  int tempo_pulo;
  bool ja_tentou_pular;
  struct Defensor *proximo;
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

typedef enum {
  MENU = 0,
  MIRANDO = 1,
  CHUTANDO = 2,
  RESULTADO = 3,
  GAME_OVER = 4
} EstadoJogo;

typedef enum {
  TORCIDA_NORMAL = 0,
  TORCIDA_COMEMORANDO = 1,
  TORCIDA_DESANIMADA = 2
} EstadoTorcida;

typedef struct {
  float x;
  float y;
  unsigned char cor_r;
  unsigned char cor_g;
  unsigned char cor_b;
  float fase;
} Torcedor;

typedef struct {
  Torcedor torcedores[MAX_TORCEDORES];
  int qtd;
  EstadoTorcida estado;
  int tempo_evento;
  float tempo;
} Torcida;

typedef struct {
  float x;
  float y;
  float largura;
  float altura;
  int matriz[3][3];
} Gol;

typedef struct {
  int pontuacao_atual;
  int chances_restantes;

  int etapa_chute;
  float direcao_chute;
  float altura_chute;
  float curva_chute;
  float forca_chute;

  Bola bola;
  Goleiro goleiro;
  Defensor *barreira;
  Medidor medidor_atual;
  Gol gol;
  Torcida torcida;
  AudioJogo audio;
  

  EstadoJogo estado_atual;
} Jogo;

typedef struct {
  char nome[50];
  int pontuacao;
} Score;

#endif
