#include "audio.h"
#include "barreira.h"
#include "dados.h"
#include "desenho.h"
#include "fisica.h"
#include "game.h"
#include "input.h"
#include "raylib.h"
#include "sprites.h"

int main() {
  InitWindow(1000, 700, "Stan James - Free Kick");
  SetTargetFPS(60);

  Jogo jogo = {0};

  inicializar_jogo(&jogo);
  inicializar_audio(&jogo.audio);
  carregar_sprites(&jogo.sprites);

  while (!WindowShouldClose()) {
    processarInput(&jogo);

    if (jogo.estado_atual != MENU && jogo.estado_atual != GAME_OVER) {
      atualizar_bola(&jogo.bola);
      atualizar_jogo(&jogo);
    }

    BeginDrawing();

    if (jogo.estado_atual == MENU) {
      desenhar_menu();
    } else if (jogo.estado_atual == GAME_OVER) {
      desenhar_game_over(&jogo);
    } else {
      desenhar_campo();
      desenhar_torcida(&jogo.torcida, jogo.sprites.arquibancada);
      desenhar_gol(&jogo.gol, jogo.sprites.gol);
      desenhar_goleiro(&jogo.goleiro, jogo.sprites.goleiro);
      desenhar_barreira(jogo.barreira, jogo.sprites.barreira_a,
                        jogo.sprites.barreira_b);
      if (!jogo.bola.em_movimento) {
        desenhar_cobrador(&jogo.bola, jogo.sprites.cobrador);
      }
      desenhar_bola(&jogo.bola);
      desenhar_hud(&jogo);
      desenhar_medidor(&jogo);

      if (jogo.estado_atual == RESULTADO) {
        desenhar_resultado(&jogo);
      }
    }

    EndDrawing();
  }

  liberar_barreira(jogo.barreira);
  liberar_sprites(&jogo.sprites);
  liberar_audio(&jogo.audio);
  CloseWindow();
  return 0;
}
