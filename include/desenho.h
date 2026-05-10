#ifndef DESENHO_H
#define DESENHO_H

#include "dados.h"

void desenhar_campo(void);
void desenhar_gol(Gol *gol, Texture2D sprite);
void desenhar_bola(Bola *bola);
void desenhar_medidor(Jogo *jogo);
void desenhar_hud(Jogo *jogo);
void desenhar_goleiro(Goleiro *goleiro, Texture2D sprite);
void desenhar_barreira(Defensor *barreira, Texture2D sprite_a, Texture2D sprite_b);
void desenhar_cobrador(Bola *bola, Texture2D sprite);
void desenhar_torcida(Torcida *torcida, Texture2D arquibancada);
void desenhar_menu(void);
void desenhar_game_over(Jogo *jogo);
void desenhar_resultado(Jogo *jogo);

#endif
