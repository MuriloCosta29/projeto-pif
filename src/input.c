#include "input.h"
#include "dados.h"
#include "fisica.h"
#include "medidor.h"
#include "raylib.h"
#include <stdbool.h>

void processarInput(Jogo *j) {
  Medidor *m = &j->medidor_atual;

  if (j->estado_atual == MENU) {
    if (IsKeyPressed(KEY_SPACE)) {
      j->estado_atual = MIRANDO;
    }
    return;
  }

  if (j->estado_atual != MIRANDO) {
    return;
  }

  if (j->bola.em_movimento) {
    return;
  }

  atualizar_medidor(m);

  if (IsKeyPressed(KEY_SPACE)) {
    switch (j->etapa_chute) {
    case 0:
      j->direcao_chute = m->valor_atual;
      m->tipo = 1;
      break;

    case 1:
      j->altura_chute = m->valor_atual;
      m->tipo = 2;
      break;

    case 2:
      j->curva_chute = m->valor_atual;
      m->tipo = 3;
      break;

    case 3:
      j->forca_chute = m->valor_atual;

      chutar_bola(&j->bola,
                  j->direcao_chute,
                  j->altura_chute,
                  j->curva_chute,
                  j->forca_chute);

      j->estado_atual = CHUTANDO;
      m->ativo = false;
      break;
    }

    j->etapa_chute++;
    m->valor_atual = 0.5f;
  }
}
