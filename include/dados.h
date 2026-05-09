#ifndef DADOS_H
#define DADOS_H

#include "audio.h"
#include <stdbool.h>

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
  AudioJogo audio;

  EstadoJogo estado_atual;
} Jogo;

typedef struct {
  char nome[50];
  int pontuacao;
} Score;

#endif
