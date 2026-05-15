#ifndef BARREIRA_H
#define BARREIRA_H

#include "dados.h"
#include <stdbool.h>

Defensor *criar_barreira(int quantidade);
Defensor *criar_barreira_posicionada(int quantidade, float x, float y);
void liberar_barreira(Defensor *barreira);
void resetar_barreira(Defensor *barreira);
void atualizar_barreira(Defensor *barreira, Bola *bola);
bool bola_colidiu_barreira(Bola *bola, Defensor *barreira);

#endif
