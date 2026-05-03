#include "../include/game.h"
#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

void inicializar_jogo(Jogo *jogo) {
  jogo->estado_atual = MENU;
  jogo->pontuacao_atual = 0;
  jogo->chances_restantes = 5;
  jogo->barreira = NULL;
  jogo->bola.em_movimento = false;
}
