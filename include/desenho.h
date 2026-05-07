#ifndef DESENHO_H
#define DESENHO_H

#include "dados.h"

void desenhar_campo(void);
void desenhar_gol_bonito(float x, float y, float largura, float altura);
void desenhar_bola(Bola *bola);
void desenhar_medidor(Jogo *jogo);
void desenhar_hud(Jogo *jogo);
void desenhar_goleiro(Goleiro *goleiro);

#endif
