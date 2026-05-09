#include "torcida.h"
#include <stdlib.h>

static const unsigned char paleta_camisas[6][3] = {
    {220, 50, 50},   {240, 200, 50}, {50, 130, 220},
    {60, 170, 80},   {235, 235, 235}, {30, 30, 50},
};

void inicializar_torcida(Torcida *torcida) {
  float x_inicio = 255.0f;
  float y_inicio = 65.0f;
  float passo_x = 36.0f;
  float passo_y = 32.0f;

  int idx = 0;
  for (int linha = 0; linha < TORCIDA_LINHAS; linha++) {
    for (int col = 0; col < TORCIDA_COLUNAS; col++) {
      Torcedor *t = &torcida->torcedores[idx];

      float jitter_x = (rand() % 9) - 4;
      float jitter_y = (rand() % 5) - 2;
      t->x = x_inicio + col * passo_x + jitter_x;
      t->y = y_inicio + linha * passo_y + jitter_y;

      int cor = rand() % 6;
      t->cor_r = paleta_camisas[cor][0];
      t->cor_g = paleta_camisas[cor][1];
      t->cor_b = paleta_camisas[cor][2];

      t->fase = (rand() % 1000) / 1000.0f * 6.2832f;
      idx++;
    }
  }

  torcida->qtd = MAX_TORCEDORES;
  torcida->estado = TORCIDA_NORMAL;
  torcida->tempo_evento = 0;
  torcida->tempo = 0.0f;
}

void atualizar_torcida(Torcida *torcida) {
  torcida->tempo += 1.0f;

  if (torcida->tempo_evento > 0) {
    torcida->tempo_evento--;
    if (torcida->tempo_evento == 0) {
      torcida->estado = TORCIDA_NORMAL;
    }
  }
}

void torcida_reage(Torcida *torcida, EstadoTorcida estado) {
  torcida->estado = estado;

  if (estado == TORCIDA_COMEMORANDO) {
    torcida->tempo_evento = 90;
  } else if (estado == TORCIDA_DESANIMADA) {
    torcida->tempo_evento = 80;
  } else {
    torcida->tempo_evento = 0;
  }
}
