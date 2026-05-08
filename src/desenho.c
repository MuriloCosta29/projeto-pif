#include "desenho.h"
#include "dados.h"
#include "raylib.h"
#include <stdlib.h>

void desenhar_campo(void) {
  ClearBackground(SKYBLUE);

  // campo maior
  DrawRectangle(0, 340, 1000, 360, DARKGREEN);

  // linhas da área em perspectiva
  DrawLine(140, 310, 860, 310, WHITE);
  DrawLine(230, 260, 770, 260, WHITE);
  DrawLine(140, 310, 230, 260, WHITE);
  DrawLine(860, 310, 770, 260, WHITE);

  // sol simples
  DrawCircle(900, 80, 45, YELLOW);
}

void desenhar_gol_bonito(float x, float y, float largura, float altura) {
  float profundidade = 45.0f;

  Color brancoFrente = WHITE;
  Color brancoFundo = Fade(WHITE, 0.55f);
  Color corRede = Fade(LIGHTGRAY, 0.65f);
  Color sombra = Fade(BLACK, 0.18f);

  Vector2 frenteSupEsq = {x, y};
  Vector2 frenteSupDir = {x + largura, y};
  Vector2 frenteInfEsq = {x, y + altura};
  Vector2 frenteInfDir = {x + largura, y + altura};

  Vector2 fundoSupEsq = {x + profundidade, y + profundidade * 0.35f};
  Vector2 fundoSupDir = {x + largura - profundidade, y + profundidade * 0.35f};
  Vector2 fundoInfEsq = {x + profundidade, y + altura + profundidade * 0.35f};
  Vector2 fundoInfDir = {x + largura - profundidade,
                         y + altura + profundidade * 0.35f};

  // sombra
  DrawEllipse(x + largura / 2, y + altura + 22, largura / 2.2f, 22, sombra);

  // rede de fundo
  DrawLineEx(fundoSupEsq, fundoSupDir, 2.0f, brancoFundo);
  DrawLineEx(fundoSupEsq, fundoInfEsq, 2.0f, brancoFundo);
  DrawLineEx(fundoSupDir, fundoInfDir, 2.0f, brancoFundo);

  // ligações da frente ao fundo
  DrawLineEx(frenteSupEsq, fundoSupEsq, 2.0f, brancoFundo);
  DrawLineEx(frenteSupDir, fundoSupDir, 2.0f, brancoFundo);
  DrawLineEx(frenteInfEsq, fundoInfEsq, 2.0f, brancoFundo);
  DrawLineEx(frenteInfDir, fundoInfDir, 2.0f, brancoFundo);

  // rede vertical
  for (int i = 1; i < 10; i++) {
    float t = i / 10.0f;

    Vector2 p1 = {frenteSupEsq.x + (frenteSupDir.x - frenteSupEsq.x) * t,
                  frenteSupEsq.y};

    Vector2 p2 = {fundoSupEsq.x + (fundoSupDir.x - fundoSupEsq.x) * t,
                  fundoSupEsq.y};

    Vector2 p3 = {frenteInfEsq.x + (frenteInfDir.x - frenteInfEsq.x) * t,
                  frenteInfEsq.y};

    Vector2 p4 = {fundoInfEsq.x + (fundoInfDir.x - fundoInfEsq.x) * t,
                  fundoInfEsq.y};

    DrawLineEx(p1, p2, 1.0f, corRede);
    DrawLineEx(p3, p4, 1.0f, corRede);
  }

  // rede horizontal
  for (int i = 1; i < 7; i++) {
    float t = i / 7.0f;

    Vector2 esqFrente = {frenteSupEsq.x, frenteSupEsq.y + altura * t};

    Vector2 dirFrente = {frenteSupDir.x, frenteSupDir.y + altura * t};

    Vector2 esqFundo = {fundoSupEsq.x, fundoSupEsq.y + altura * t};

    Vector2 dirFundo = {fundoSupDir.x, fundoSupDir.y + altura * t};

    DrawLineEx(esqFrente, esqFundo, 1.0f, corRede);
    DrawLineEx(dirFrente, dirFundo, 1.0f, corRede);
    DrawLineEx(esqFundo, dirFundo, 1.0f, corRede);
  }

  // trave da frente por cima
  DrawLineEx(frenteSupEsq, frenteSupDir, 6.0f, brancoFrente);
  DrawLineEx(frenteSupEsq, frenteInfEsq, 6.0f, brancoFrente);
  DrawLineEx(frenteSupDir, frenteInfDir, 6.0f, brancoFrente);
}

void desenhar_bola(Bola *bola) {
  DrawCircle(bola->x + 4, bola->y + 4, 10, Fade(BLACK, 0.3f));
  DrawCircle(bola->x, bola->y, 10, WHITE);
  DrawCircleLines(bola->x, bola->y, 10, BLACK);
  DrawCircle(bola->x - 3, bola->y - 3, 3, BLACK);
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
  DrawRectangle(goleiro->x, goleiro->y, goleiro->largura, goleiro->altura,
                BLUE);
}

void desenhar_barreira(Defensor *barreira) {
  Defensor *atual = barreira;

  while (atual != NULL) {
    DrawRectangle(atual->x, atual->y, atual->largura, atual->altura, RED);
    atual = atual->proximo;
  }
}
