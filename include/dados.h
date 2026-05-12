#ifndef DADOS_H
#define DADOS_H

#include "audio.h"
#include "sprites.h"
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
  bool visivel;
} Bola;

typedef struct {
  float x;
  float y;
  float inicio_x;
  float inicio_y;
  float alvo_x;
  float alvo_y;
  float largura;
  float altura;
  float velocidade;
  int regiao_defesa;
  int tempo_defesa;
  int duracao_defesa;
  bool esta_pulando;
  bool defendendo;
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
  CHUTE_NENHUM,
  CHUTE_GOL,
  CHUTE_DEFESA,
  CHUTE_BARREIRA,
  CHUTE_FORA,
} ResultadoChute;

typedef enum {
  TORCIDA_NORMAL = 0,
  TORCIDA_COMEMORANDO = 1,
  TORCIDA_DESANIMADA = 2
} EstadoTorcida;

typedef enum {
  COBRANCA_PENALTI = 0,
  COBRANCA_FALTA_ESQUERDA = 1,
  COBRANCA_FALTA_FRONTAL = 2,
  COBRANCA_FALTA_DIREITA = 3
} TipoCobranca;

typedef struct {
  TipoCobranca tipo;
  int quantidade_barreira;
  float bola_x;
  float bola_y;
  float barreira_x;
  float barreira_y;
} Nivel;

typedef struct {
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
  int tempo_resultado;
  int nivel_atual;
  int total_niveis;
  TipoCobranca tipo_cobranca_atual;

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
  SpritesJogo sprites;
  ResultadoChute resultado_chute;

  EstadoJogo estado_atual;
} Jogo;

typedef struct {
  char nome[50];
  int pontuacao;
} Score;

#endif
