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
  const char *titulo = "DIRECAO";
  const char *rot_esq = "ESQ";
  const char *rot_meio = "CENTRO";
  const char *rot_dir = "DIR";

  if (jogo->etapa_chute == 1) {
    titulo = "ALTURA";
    rot_esq = "BAIXA";
    rot_meio = "MEDIA";
    rot_dir = "ALTA";
  } else if (jogo->etapa_chute == 2) {
    titulo = "CURVA";
    rot_esq = "ESQ";
    rot_meio = "RETA";
    rot_dir = "DIR";
  } else if (jogo->etapa_chute == 3) {
    titulo = "FORCA";
    rot_esq = "FRACA";
    rot_meio = "MEDIA";
    rot_dir = "FORTE";
  } else if (jogo->etapa_chute >= 4) {
    titulo = "CHUTE!";
    rot_esq = "";
    rot_meio = "";
    rot_dir = "";
  }

  Medidor *m = &jogo->medidor_atual;

  int titulo_w = MeasureText(titulo, 24);
  DrawText(titulo, m->x + m->largura / 2 - titulo_w / 2, m->y - 32, 24, BLACK);

  DrawRectangle(m->x, m->y, m->largura, m->altura, LIGHTGRAY);
  DrawRectangleLines(m->x, m->y, m->largura, m->altura, BLACK);

  int rot_size = 18;
  int meio_w = MeasureText(rot_meio, rot_size);
  int dir_w = MeasureText(rot_dir, rot_size);
  int rot_y = m->y + m->altura + 6;

  DrawText(rot_esq, m->x, rot_y, rot_size, DARKGRAY);
  DrawText(rot_meio, m->x + m->largura / 2 - meio_w / 2, rot_y, rot_size,
           DARKGRAY);
  DrawText(rot_dir, m->x + m->largura - dir_w, rot_y, rot_size, DARKGRAY);

  float marcadorX = m->x + m->valor_atual * m->largura;
  DrawCircle(marcadorX, m->y + m->altura / 2, 10, RED);
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
  float topo_camisa = goleiro->y;
  float fim_camisa = goleiro->y + goleiro->altura * 0.55f;
  float fim_calcao = goleiro->y + goleiro->altura;

  Color cor_camisa = (Color){40, 90, 170, 255};
  Color cor_calcao = (Color){25, 25, 25, 255};
  Color cor_luva = (Color){255, 170, 30, 255};
  Color cor_cabelo = (Color){70, 45, 25, 255};

  DrawEllipse(centro_x, fim_calcao + 24, 22, 5, Fade(BLACK, 0.3f));

  DrawRectangle(centro_x - 5, fim_calcao, 4, 20, BEIGE);
  DrawRectangle(centro_x + 1, fim_calcao, 4, 20, BEIGE);
  DrawRectangle(centro_x - 9, fim_calcao + 18, 12, 4, BLACK);
  DrawRectangle(centro_x - 3, fim_calcao + 18, 12, 4, BLACK);

  DrawRectangle(goleiro->x, fim_camisa, goleiro->largura,
                fim_calcao - fim_camisa, cor_calcao);

  DrawRectangle(goleiro->x, topo_camisa, goleiro->largura,
                fim_camisa - topo_camisa, cor_camisa);
  DrawLine(goleiro->x, fim_camisa, goleiro->x + goleiro->largura, fim_camisa,
           BLACK);

  DrawTriangle((Vector2){centro_x, topo_camisa},
               (Vector2){centro_x - 6, topo_camisa + 8},
               (Vector2){centro_x + 6, topo_camisa + 8}, BEIGE);

  Vector2 ombro_esq = {goleiro->x + 4, topo_camisa + 8};
  Vector2 ombro_dir = {goleiro->x + goleiro->largura - 4, topo_camisa + 8};
  Vector2 mao_esq = {goleiro->x - 18, topo_camisa - 12};
  Vector2 mao_dir = {goleiro->x + goleiro->largura + 18, topo_camisa - 12};

  DrawLineEx(ombro_esq, mao_esq, 7, cor_camisa);
  DrawLineEx(ombro_dir, mao_dir, 7, cor_camisa);
  DrawCircle(mao_esq.x, mao_esq.y, 8, cor_luva);
  DrawCircle(mao_dir.x, mao_dir.y, 8, cor_luva);

  DrawCircle(centro_x, topo_camisa - 12, 13, BEIGE);
  DrawCircleSector((Vector2){centro_x, topo_camisa - 14}, 13, 180, 360, 16,
                   cor_cabelo);
  DrawCircle(centro_x - 4, topo_camisa - 12, 1.5f, BLACK);
  DrawCircle(centro_x + 4, topo_camisa - 12, 1.5f, BLACK);
}

void desenhar_barreira(Defensor *barreira) {
  Defensor *atual = barreira;

  Color cor_camisa = (Color){200, 40, 40, 255};
  Color cor_calcao = (Color){240, 240, 240, 255};
  Color cor_cabelo = (Color){45, 30, 20, 255};

  while (atual != NULL) {
    float centro_x = atual->x + atual->largura / 2;

    float deslocamento_pulo = 0;
    if (atual->esta_pulando) {
      float progresso = (30 - atual->tempo_pulo) / 30.0f;
      deslocamento_pulo = -4 * progresso * (1 - progresso) * 40;
    }

    float y_desenho = atual->y + deslocamento_pulo;
    float topo_camisa = y_desenho;
    float fim_camisa = y_desenho + atual->altura * 0.6f;
    float fim_calcao = y_desenho + atual->altura;

    DrawEllipse(centro_x, atual->y + atual->altura + 28, atual->largura * 0.7f,
                4, Fade(BLACK, 0.3f));

    DrawRectangle(centro_x - 5, fim_calcao, 4, 18, BEIGE);
    DrawRectangle(centro_x + 1, fim_calcao, 4, 18, BEIGE);
    DrawRectangle(centro_x - 8, fim_calcao + 16, 10, 4, BLACK);
    DrawRectangle(centro_x - 2, fim_calcao + 16, 10, 4, BLACK);

    DrawRectangle(atual->x, fim_camisa, atual->largura, fim_calcao - fim_camisa,
                  cor_calcao);

    DrawRectangle(atual->x, topo_camisa, atual->largura,
                  fim_camisa - topo_camisa, cor_camisa);
    DrawLine(atual->x, fim_camisa, atual->x + atual->largura, fim_camisa,
             BLACK);

    DrawTriangle((Vector2){centro_x, topo_camisa},
                 (Vector2){centro_x - 4, topo_camisa + 6},
                 (Vector2){centro_x + 4, topo_camisa + 6}, BEIGE);

    Vector2 ombro_esq = {atual->x + 3, topo_camisa + 8};
    Vector2 ombro_dir = {atual->x + atual->largura - 3, topo_camisa + 8};
    Vector2 mao_esq = {centro_x + 3, fim_camisa + 4};
    Vector2 mao_dir = {centro_x - 3, fim_camisa + 4};

    DrawLineEx(ombro_esq, mao_esq, 5, cor_camisa);
    DrawLineEx(ombro_dir, mao_dir, 5, cor_camisa);
    DrawCircle(mao_esq.x, mao_esq.y, 3.5f, BEIGE);
    DrawCircle(mao_dir.x, mao_dir.y, 3.5f, BEIGE);

    DrawCircle(centro_x, topo_camisa - 10, 11, BEIGE);
    DrawCircleSector((Vector2){centro_x, topo_camisa - 12}, 11, 180, 360, 16,
                     cor_cabelo);
    DrawCircle(centro_x - 3, topo_camisa - 10, 1.3f, BLACK);
    DrawCircle(centro_x + 3, topo_camisa - 10, 1.3f, BLACK);

    atual = atual->proximo;
  }
}
