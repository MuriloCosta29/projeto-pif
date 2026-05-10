#include "torcida.h"

void inicializar_torcida(Torcida *torcida) {
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
