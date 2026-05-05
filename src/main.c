#include "dados.h"
#include "fisica.h"
#include "input.h"
#include "raylib.h"

int main() {
  InitWindow(800, 600, "Stan James - Teste Medidor");
  SetTargetFPS(60);

  Jogo jogo = {0};

  inicializar_bola(&jogo.bola);

  jogo.estado_atual = MENU; // JOGANDO
  jogo.chances_restantes = 5;

  jogo.etapa_chute = 0;
  jogo.direcao_chute = 0.5f;
  jogo.altura_chute = 0.5f;
  jogo.curva_chute = 0.5f;
  jogo.forca_chute = 0.5f;

  jogo.medidor_atual.x = 150;
  jogo.medidor_atual.y = 540;
  jogo.medidor_atual.largura = 500;
  jogo.medidor_atual.altura = 25;
  jogo.medidor_atual.valor_atual = 0.5f;
  jogo.medidor_atual.velocidade = 0.02f;
  jogo.medidor_atual.direcao_movimento = 1;
  jogo.medidor_atual.ativo = true;
  jogo.medidor_atual.tipo = 0;

  while (!WindowShouldClose()) {
    processarInput(&jogo);
    atualizar_bola(&jogo.bola);

    if (jogo.bola.y > 650 || jogo.bola.x < -50 || jogo.bola.x > 850) {
      resetar_bola(&jogo.bola);

      jogo.etapa_chute = 0;
      jogo.direcao_chute = 0.5f;
      jogo.altura_chute = 0.5f;
      jogo.curva_chute = 0.5f;
      jogo.forca_chute = 0.5f;

      jogo.medidor_atual.valor_atual = 0.5f;
      jogo.medidor_atual.direcao_movimento = 1;
      jogo.medidor_atual.ativo = true;
      jogo.medidor_atual.tipo = 0;

      jogo.estado_atual = MIRANDO;
    }

    BeginDrawing();
    ClearBackground(SKYBLUE);

    DrawRectangle(0, 300, 800, 300, DARKGREEN);

    DrawRectangleLines(250, 100, 300, 120, WHITE);

    DrawCircle(jogo.bola.x + 4, jogo.bola.y + 4, 10, Fade(BLACK, 0.3f));
    DrawCircle(jogo.bola.x, jogo.bola.y, 10, WHITE);
    DrawCircleLines(jogo.bola.x, jogo.bola.y, 10, BLACK);

    const char *nomeMedidor = "DIRECAO";

    if (jogo.etapa_chute == 1) {
      nomeMedidor = "ALTURA";
    } else if (jogo.etapa_chute == 2) {
      nomeMedidor = "CURVA";
    } else if (jogo.etapa_chute == 3) {
      nomeMedidor = "FORCA";
    } else if (jogo.etapa_chute >= 4) {
      nomeMedidor = "CHUTE!";
    }

    DrawText("SPACE = travar medidor", 20, 20, 20, BLACK);
    DrawText(nomeMedidor, 330, 500, 24, BLACK);

    DrawRectangle(jogo.medidor_atual.x, jogo.medidor_atual.y,
                  jogo.medidor_atual.largura, jogo.medidor_atual.altura,
                  LIGHTGRAY);

    DrawRectangleLines(jogo.medidor_atual.x, jogo.medidor_atual.y,
                       jogo.medidor_atual.largura, jogo.medidor_atual.altura,
                       BLACK);

    float marcadorX = jogo.medidor_atual.x + jogo.medidor_atual.valor_atual *
                                                 jogo.medidor_atual.largura;

    DrawCircle(marcadorX, jogo.medidor_atual.y + 12, 10, RED);

    DrawText(TextFormat("Direcao: %.2f", jogo.direcao_chute), 20, 60, 18,
             BLACK);
    DrawText(TextFormat("Altura: %.2f", jogo.altura_chute), 20, 85, 18, BLACK);
    DrawText(TextFormat("Curva: %.2f", jogo.curva_chute), 20, 110, 18, BLACK);
    DrawText(TextFormat("Forca: %.2f", jogo.forca_chute), 20, 135, 18, BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
