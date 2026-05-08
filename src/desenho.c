#include "desenho.h"
#include "raylib.h"
#include <stddef.h>

void desenhar_campo(void) {
  ClearBackground(SKYBLUE);

  DrawRectangle(0, 220, 1000, 480, DARKGREEN);

  DrawLine(0, 220, 1000, 220, WHITE);

  DrawLine(250, 360, 750, 360, Fade(WHITE, 0.5f));
  DrawLine(300, 500, 700, 500, Fade(WHITE, 0.35f));

  DrawCircle(900, 90, 45, YELLOW);
}

void desenhar_gol_bonito(float x, float y, float largura, float altura) {
  Color rede = Fade(LIGHTGRAY, 0.6f);

  DrawRectangleLines(x, y, largura, altura, WHITE);

  DrawLine(x + largura / 3, y, x + largura / 3, y + altura, rede);
  DrawLine(x + (largura / 3) * 2, y, x + (largura / 3) * 2, y + altura, rede);

  DrawLine(x, y + altura / 3, x + largura, y + altura / 3, rede);
  DrawLine(x, y + (altura / 3) * 2, x + largura, y + (altura / 3) * 2, rede);

  DrawRectangleLinesEx((Rectangle){x, y, largura, altura}, 6, WHITE);
}

void desenhar_bola(Bola *bola) {
  float bola_y_visual = bola->y - bola->z;
  float raio = 10 + bola->z * 0.03f;

  DrawEllipse(bola->x + 4, bola->y + 6, 12, 5, Fade(BLACK, 0.35f));

  DrawCircle(bola->x + 4, bola_y_visual + 4, raio, Fade(BLACK, 0.3f));
  DrawCircle(bola->x, bola_y_visual, raio, WHITE);
  DrawCircleLines(bola->x, bola_y_visual, raio, BLACK);
  DrawCircle(bola->x - 3, bola_y_visual - 3, raio * 0.28f, BLACK);
}

void desenhar_medidor(Jogo *jogo) {
  const char *nomeMedidor = "DIRECAO";

  if (jogo->etapa_chute == 1) {
    nomeMedidor = "ALTURA";
  } else if (jogo->etapa_chute == 2) {
    nomeMedidor = "CURVA";
  } else if (jogo->etapa_chute == 3) {
    nomeMedidor = "FORCA";
  } else if (jogo->etapa_chute >= 4) {
    nomeMedidor = "CHUTE!";
  }

  DrawText(nomeMedidor, 430, 600, 24, BLACK);

  DrawRectangle(jogo->medidor_atual.x, jogo->medidor_atual.y,
                jogo->medidor_atual.largura, jogo->medidor_atual.altura,
                LIGHTGRAY);

  DrawRectangleLines(jogo->medidor_atual.x, jogo->medidor_atual.y,
                     jogo->medidor_atual.largura, jogo->medidor_atual.altura,
                     BLACK);

  float marcadorX = jogo->medidor_atual.x + jogo->medidor_atual.valor_atual *
                                                jogo->medidor_atual.largura;

  DrawCircle(marcadorX, jogo->medidor_atual.y + 12, 10, RED);
}

void desenhar_hud(Jogo *jogo) {
  DrawText("SPACE = travar medidor", 20, 20, 20, BLACK);
  DrawText(TextFormat("Gols: %d", jogo->pontuacao_atual), 20, 50, 20, BLACK);
  DrawText(TextFormat("Chances: %d", jogo->chances_restantes), 20, 80, 20,
           BLACK);

  DrawText(TextFormat("Direcao: %.2f", jogo->direcao_chute), 20, 120, 18,
           BLACK);
  DrawText(TextFormat("Altura: %.2f", jogo->altura_chute), 20, 145, 18, BLACK);
  DrawText(TextFormat("Curva: %.2f", jogo->curva_chute), 20, 170, 18, BLACK);
  DrawText(TextFormat("Forca: %.2f", jogo->forca_chute), 20, 195, 18, BLACK);
}

void desenhar_goleiro(Goleiro *goleiro) {
  float centro_x = goleiro->x + goleiro->largura / 2;

  DrawCircle(centro_x, goleiro->y - 12, 14, BEIGE);

  DrawRectangle(goleiro->x, goleiro->y, goleiro->largura, goleiro->altura,
                BLUE);

  DrawLine(goleiro->x, goleiro->y + 20, goleiro->x - 25, goleiro->y + 45, BLUE);

  DrawLine(goleiro->x + goleiro->largura, goleiro->y + 20,
           goleiro->x + goleiro->largura + 25, goleiro->y + 45, BLUE);

  DrawLine(centro_x, goleiro->y + goleiro->altura, centro_x - 15,
           goleiro->y + goleiro->altura + 25, BLACK);

  DrawLine(centro_x, goleiro->y + goleiro->altura, centro_x + 15,
           goleiro->y + goleiro->altura + 25, BLACK);
}

void desenhar_barreira(Defensor *barreira) {
  Defensor *atual = barreira;

  while (atual != NULL) {
    float centro_x = atual->x + atual->largura / 2;

    float deslocamento_pulo = 0;
    if (atual->esta_pulando) {
      float progresso = (30 - atual->tempo_pulo) / 30.0f;
      deslocamento_pulo = -4 * progresso * (1 - progresso) * 40;
    }

    float y_desenho = atual->y + deslocamento_pulo;

    DrawEllipse(centro_x, atual->y + atual->altura + 28, atual->largura * 0.7f,
                4, Fade(BLACK, 0.3f));

    DrawCircle(centro_x, y_desenho - 10, 12, BEIGE);

    DrawRectangle(atual->x, y_desenho, atual->largura, atual->altura, RED);

    DrawLine(centro_x, y_desenho + atual->altura, centro_x - 12,
             y_desenho + atual->altura + 25, BLACK);

    DrawLine(centro_x, y_desenho + atual->altura, centro_x + 12,
             y_desenho + atual->altura + 25, BLACK);

    DrawLine(atual->x, y_desenho + 20, atual->x - 12, y_desenho + 45, BLACK);

    DrawLine(atual->x + atual->largura, y_desenho + 20,
             atual->x + atual->largura + 12, y_desenho + 45, BLACK);

    atual = atual->proximo;
  }
}
