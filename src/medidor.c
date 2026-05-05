#include "medidor.h"

void atualizar_medidor(Medidor *m) {
  if (!m->ativo) {
    return;
  }

  m->valor_atual += m->velocidade * m->direcao_movimento;

  if (m->valor_atual >= 1.0f) {
    m->valor_atual = 1.0f;
    m->direcao_movimento = -1;
  }

  if (m->valor_atual <= 0.0f) {
    m->valor_atual = 0.0f;
    m->direcao_movimento = 1;
  }
}
