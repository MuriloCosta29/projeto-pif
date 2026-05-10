#ifndef GOLEIRO_H
#define GOLEIRO_H

#include "dados.h"

void inicializar_goleiro(Goleiro *goleiro, Gol *gol);
void iniciar_defesa_goleiro(Goleiro *goleiro, Gol *gol);
void atualizar_goleiro(Goleiro *goleiro);
int escolher_regiao_defesa(void);

#endif
