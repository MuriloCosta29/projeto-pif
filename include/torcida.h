#ifndef TORCIDA_H
#define TORCIDA_H

#include "dados.h"

void inicializar_torcida(Torcida *torcida);
void atualizar_torcida(Torcida *torcida);
void torcida_reage(Torcida *torcida, EstadoTorcida estado);

#endif
