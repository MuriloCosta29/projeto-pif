#ifndef DESENHO_H
#define DESENHO_H

#include "dados.h"

void desenhar_campo(void);
void desenhar_gol_bonito(float x, float y, float largura, float altura);
void desenhar_bola(Bola *bola);
void desenhar_medidor(Jogo *jogo);
void desenhar_hud(Jogo *jogo);
void desenhar_goleiro(Goleiro *goleiro);
void desenhar_barreira(Defensor *barreira);
void desenhar_torcida(Torcida *torcida);
void desenhar_menu(void);
void desenhar_game_over(Jogo *jogo);
void desenhar_resultado(Jogo *jogo);

#endif
