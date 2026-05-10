#ifndef SPRITES_H
#define SPRITES_H

#include "raylib.h"
#include <stdbool.h>

typedef struct {
  Texture2D cobrador;
  Texture2D goleiro;
  Texture2D barreira_a;
  Texture2D barreira_b;
  Texture2D gol;
  Texture2D arquibancada;
  bool inicializado;
} SpritesJogo;

void carregar_sprites(SpritesJogo *sprites);
void liberar_sprites(SpritesJogo *sprites);

#endif
