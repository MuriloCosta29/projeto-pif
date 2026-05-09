#include "audio.h"
#include "barreira.h"
#include "desenho.h"
#include "fisica.h"
#include "game.h"
#include "input.h"
#include "raylib.h"

int main() {
  InitWindow(1000, 700, "Stan James - Free Kick");
  SetTargetFPS(60);

  Jogo jogo = {0};

  inicializar_jogo(&jogo);
  inicializar_audio(&jogo.audio);

  while (!WindowShouldClose()) {
    processarInput(&jogo);
    atualizar_bola(&jogo.bola);
    atualizar_jogo(&jogo);

    BeginDrawing();

    desenhar_campo();

    desenhar_gol_bonito(jogo.gol.x, jogo.gol.y, jogo.gol.largura,
                        jogo.gol.altura);

    desenhar_goleiro(&jogo.goleiro);

    desenhar_barreira(jogo.barreira);
    desenhar_bola(&jogo.bola);
    desenhar_hud(&jogo);
    desenhar_medidor(&jogo);

    EndDrawing();
  }

  liberar_barreira(jogo.barreira);
  liberar_audio(&jogo.audio);
  CloseWindow();
  return 0;
}
