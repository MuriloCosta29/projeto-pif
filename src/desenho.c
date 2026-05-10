#include "desenho.h"
#include "raylib.h"
#include <math.h>
#include <stddef.h>

void desenhar_campo(void) {
  Color ceu_topo = (Color){70, 140, 215, 255};
  Color ceu_horizonte = (Color){195, 220, 235, 255};
  DrawRectangleGradientV(0, 0, 1000, 220, ceu_topo, ceu_horizonte);

  Color cor_glow = (Color){255, 220, 120, 255};
  DrawCircle(900, 90, 70, Fade(cor_glow, 0.10f));
  DrawCircle(900, 90, 58, Fade(cor_glow, 0.18f));
  DrawCircle(900, 90, 45, (Color){255, 215, 100, 255});
  DrawCircle(900, 90, 36, (Color){255, 235, 160, 255});
  DrawCircle(895, 82, 14, Fade(WHITE, 0.55f));

  Color cor_nuvem = Fade(WHITE, 0.85f);
  Color cor_nuvem_sombra = Fade((Color){170, 190, 210, 255}, 0.6f);

  DrawCircle(95, 70, 18, cor_nuvem_sombra);
  DrawCircle(120, 65, 22, cor_nuvem_sombra);
  DrawCircle(148, 70, 18, cor_nuvem_sombra);
  DrawCircle(95, 65, 16, cor_nuvem);
  DrawCircle(120, 60, 20, cor_nuvem);
  DrawCircle(148, 65, 16, cor_nuvem);

  DrawCircle(35, 145, 14, cor_nuvem_sombra);
  DrawCircle(58, 140, 18, cor_nuvem_sombra);
  DrawCircle(80, 145, 14, cor_nuvem_sombra);
  DrawCircle(35, 140, 12, cor_nuvem);
  DrawCircle(58, 135, 16, cor_nuvem);
  DrawCircle(80, 140, 12, cor_nuvem);

  DrawCircle(170, 175, 12, cor_nuvem_sombra);
  DrawCircle(190, 170, 16, cor_nuvem_sombra);
  DrawCircle(210, 175, 12, cor_nuvem_sombra);
  DrawCircle(190, 167, 14, cor_nuvem);

  Color grama_fundo = (Color){25, 95, 40, 255};
  Color grama_meio = (Color){45, 130, 55, 255};
  Color grama_frente = (Color){60, 155, 70, 255};
  DrawRectangleGradientV(0, 220, 1000, 200, grama_fundo, grama_meio);
  DrawRectangleGradientV(0, 420, 1000, 280, grama_meio, grama_frente);

  for (int i = 0; i < 6; i++) {
    int y_start = 220 + i * 80;
    if (i % 2 == 1) {
      DrawRectangle(0, y_start, 1000, 40, Fade(BLACK, 0.06f));
    }
  }

  DrawLineEx((Vector2){0, 220}, (Vector2){1000, 220}, 2, WHITE);

  DrawLine(150, 270, 850, 270, Fade(WHITE, 0.45f));
  DrawLine(120, 270, 120, 360, Fade(WHITE, 0.35f));
  DrawLine(880, 270, 880, 360, Fade(WHITE, 0.35f));
  DrawLine(120, 360, 880, 360, Fade(WHITE, 0.3f));

  DrawLine(280, 270, 720, 270, Fade(WHITE, 0.55f));
  DrawLine(280, 270, 280, 305, Fade(WHITE, 0.45f));
  DrawLine(720, 270, 720, 305, Fade(WHITE, 0.45f));
  DrawLine(280, 305, 720, 305, Fade(WHITE, 0.4f));

  DrawCircle(500, 470, 3, Fade(WHITE, 0.6f));
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

  float sombra_largura = 12 - bola->z * 0.04f;
  if (sombra_largura < 5)
    sombra_largura = 5;
  float sombra_alpha = 0.38f - bola->z * 0.003f;
  if (sombra_alpha < 0.08f)
    sombra_alpha = 0.08f;
  DrawEllipse(bola->x, bola->y + 8, sombra_largura, sombra_largura * 0.42f,
              Fade(BLACK, sombra_alpha));

  DrawCircle(bola->x, bola_y_visual, raio, (Color){250, 250, 250, 255});

  DrawCircleSector((Vector2){bola->x, bola_y_visual}, raio * 0.95f, 30, 160, 18,
                   Fade((Color){70, 80, 100, 255}, 0.22f));

  DrawCircle(bola->x, bola_y_visual, raio * 0.30f, BLACK);
  DrawCircle(bola->x + raio * 0.55f, bola_y_visual - raio * 0.30f, raio * 0.14f,
             BLACK);
  DrawCircle(bola->x - raio * 0.55f, bola_y_visual - raio * 0.30f, raio * 0.14f,
             BLACK);
  DrawCircle(bola->x, bola_y_visual + raio * 0.62f, raio * 0.14f, BLACK);

  DrawCircle(bola->x - raio * 0.40f, bola_y_visual - raio * 0.50f, raio * 0.22f,
             Fade(WHITE, 0.75f));

  DrawCircleLines(bola->x, bola_y_visual, raio, (Color){40, 40, 40, 255});
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

void desenhar_torcida(Torcida *torcida) {
  Color cor_concreto_claro = (Color){145, 145, 155, 255};
  Color cor_concreto_escuro = (Color){95, 95, 110, 255};
  Color cor_telhado = (Color){50, 55, 65, 255};
  Color cor_telhado_borda = (Color){25, 28, 35, 255};
  Color cor_pilar = (Color){70, 70, 80, 255};
  Color cor_sombra_telhado = (Color){25, 30, 40, 180};
  Color cor_pele = (Color){235, 200, 165, 255};
  Color cor_cabelo = (Color){55, 40, 25, 255};

  int x_estadio = 230;
  int largura_estadio = 540;
  int y_telhado = 30;
  int altura_telhado = 16;
  int y_arquibancada = y_telhado + altura_telhado;
  int altura_arquibancada = 169;

  DrawTriangle((Vector2){x_estadio - 12, y_telhado + altura_telhado},
               (Vector2){x_estadio + 8, y_telhado},
               (Vector2){x_estadio + largura_estadio - 8, y_telhado},
               cor_telhado);
  DrawTriangle(
      (Vector2){x_estadio - 12, y_telhado + altura_telhado},
      (Vector2){x_estadio + largura_estadio - 8, y_telhado},
      (Vector2){x_estadio + largura_estadio + 12, y_telhado + altura_telhado},
      cor_telhado);
  DrawLineEx(
      (Vector2){x_estadio - 12, y_telhado + altura_telhado},
      (Vector2){x_estadio + largura_estadio + 12, y_telhado + altura_telhado},
      2, cor_telhado_borda);
  DrawLineEx((Vector2){x_estadio + 8, y_telhado},
             (Vector2){x_estadio + largura_estadio - 8, y_telhado}, 2,
             cor_telhado_borda);

  DrawRectangleGradientV(x_estadio, y_arquibancada, largura_estadio, 14,
                         cor_sombra_telhado,
                         (Color){cor_sombra_telhado.r, cor_sombra_telhado.g,
                                 cor_sombra_telhado.b, 0});

  int altura_degrau = altura_arquibancada / TORCIDA_LINHAS;
  for (int i = 0; i < TORCIDA_LINHAS; i++) {
    int y_start = y_arquibancada + i * altura_degrau;
    Color cor = (i % 2 == 0) ? cor_concreto_claro : cor_concreto_escuro;
    DrawRectangle(x_estadio, y_start, largura_estadio, altura_degrau, cor);
    DrawLine(x_estadio, y_start + altura_degrau - 1,
             x_estadio + largura_estadio, y_start + altura_degrau - 1,
             (Color){45, 45, 55, 255});
  }

  for (int i = 1; i < 8; i++) {
    int x_div = x_estadio + i * (largura_estadio / 8);
    DrawLine(x_div, y_arquibancada, x_div, y_arquibancada + altura_arquibancada,
             Fade(BLACK, 0.10f));
  }

  DrawRectangle(x_estadio - 8, y_arquibancada, 8, altura_arquibancada,
                cor_pilar);
  DrawRectangle(x_estadio + largura_estadio, y_arquibancada, 8,
                altura_arquibancada, cor_pilar);
  DrawRectangleLines(x_estadio - 8, y_arquibancada, 8, altura_arquibancada,
                     cor_telhado_borda);
  DrawRectangleLines(x_estadio + largura_estadio, y_arquibancada, 8,
                     altura_arquibancada, cor_telhado_borda);

  DrawRectangleLines(x_estadio, y_arquibancada, largura_estadio,
                     altura_arquibancada, cor_telhado_borda);

  for (int i = 0; i < torcida->qtd; i++) {
    Torcedor *t = &torcida->torcedores[i];

    float dy = 0.0f;
    bool bracos_pra_cima = false;

    if (torcida->estado == TORCIDA_NORMAL) {
      dy = sinf(torcida->tempo * 0.05f + t->fase) * 1.2f;
    } else if (torcida->estado == TORCIDA_COMEMORANDO) {
      float onda = sinf(torcida->tempo * 0.4f + t->fase);
      dy = -fabsf(onda) * 6.0f;
      bracos_pra_cima = true;
    } else if (torcida->estado == TORCIDA_DESANIMADA) {
      dy = 1.5f;
    }

    Color cor_camisa = (Color){t->cor_r, t->cor_g, t->cor_b, 255};
    Color cor_camisa_escura = (Color){(unsigned char)(t->cor_r * 0.7f),
                                      (unsigned char)(t->cor_g * 0.7f),
                                      (unsigned char)(t->cor_b * 0.7f), 255};

    float cx = t->x;
    float cy = t->y + dy;

    DrawRectangle(cx - 3, cy + 4, 7, 7, cor_camisa);
    DrawRectangle(cx - 3, cy + 9, 7, 2, cor_camisa_escura);
    DrawCircle(cx, cy + 1, 3.5f, cor_pele);
    DrawCircleSector((Vector2){cx, cy + 0.5f}, 3.5f, 180, 360, 8, cor_cabelo);

    if (bracos_pra_cima) {
      DrawLineEx((Vector2){cx - 3, cy + 5}, (Vector2){cx - 6, cy - 4}, 2,
                 cor_camisa);
      DrawLineEx((Vector2){cx + 3, cy + 5}, (Vector2){cx + 6, cy - 4}, 2,
                 cor_camisa);
      DrawCircle(cx - 6, cy - 4, 1.5f, cor_pele);
      DrawCircle(cx + 6, cy - 4, 1.5f, cor_pele);
    }
  }
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

void desenhar_menu(void) {
  desenhar_campo();
  DrawRectangle(0, 0, 1000, 700, Fade(BLACK, 0.55f));

  const char *titulo = "STAN JAMES";
  const char *subtitulo = "FREE KICK";
  const char *instrucao = "Pressione SPACE para comecar";
  const char *controles_titulo = "CONTROLES";
  const char *ctrl1 = "SPACE - travar DIRECAO";
  const char *ctrl2 = "SPACE - travar ALTURA";
  const char *ctrl3 = "SPACE - travar CURVA";
  const char *ctrl4 = "SPACE - travar FORCA e chutar";

  int titulo_w = MeasureText(titulo, 80);
  DrawText(titulo, 500 - titulo_w / 2, 130, 80, WHITE);

  int sub_w = MeasureText(subtitulo, 40);
  DrawText(subtitulo, 500 - sub_w / 2, 220, 40, (Color){255, 215, 100, 255});

  int instr_w = MeasureText(instrucao, 28);
  DrawText(instrucao, 500 - instr_w / 2, 320, 28, WHITE);

  int ctitulo_w = MeasureText(controles_titulo, 24);
  DrawText(controles_titulo, 500 - ctitulo_w / 2, 420, 24,
           (Color){255, 215, 100, 255});

  int c1_w = MeasureText(ctrl1, 20);
  int c2_w = MeasureText(ctrl2, 20);
  int c3_w = MeasureText(ctrl3, 20);
  int c4_w = MeasureText(ctrl4, 20);
  DrawText(ctrl1, 500 - c1_w / 2, 460, 20, LIGHTGRAY);
  DrawText(ctrl2, 500 - c2_w / 2, 490, 20, LIGHTGRAY);
  DrawText(ctrl3, 500 - c3_w / 2, 520, 20, LIGHTGRAY);
  DrawText(ctrl4, 500 - c4_w / 2, 550, 20, LIGHTGRAY);
}

void desenhar_game_over(Jogo *jogo) {
  desenhar_campo();
  DrawRectangle(0, 0, 1000, 700, Fade(BLACK, 0.65f));

  const char *titulo = "FIM DE JOGO";
  const char *instrucao = "Pressione SPACE para reiniciar";

  int titulo_w = MeasureText(titulo, 70);
  DrawText(titulo, 500 - titulo_w / 2, 180, 70, WHITE);

  const char *rotulo_pontos = "Pontuacao Final";
  int rot_w = MeasureText(rotulo_pontos, 28);
  DrawText(rotulo_pontos, 500 - rot_w / 2, 300, 28,
           (Color){255, 215, 100, 255});

  const char *placar = TextFormat("%d", jogo->pontuacao_atual);
  int placar_w = MeasureText(placar, 90);
  DrawText(placar, 500 - placar_w / 2, 340, 90, WHITE);

  int instr_w = MeasureText(instrucao, 26);
  DrawText(instrucao, 500 - instr_w / 2, 490, 26, LIGHTGRAY);
}

void desenhar_resultado(Jogo *jogo) {
  const char *texto = NULL;
  Color cor = WHITE;

  if (jogo->resultado_chute == CHUTE_GOL) {
    texto = "GOL!";
    cor = (Color){255, 215, 0, 255};
  } else if (jogo->resultado_chute == CHUTE_DEFESA) {
    texto = "DEFESA!";
    cor = BLUE;
  } else if (jogo->resultado_chute == CHUTE_BARREIRA) {
    texto = "BARREIRA!";
    cor = RED;
  } else if (jogo->resultado_chute == CHUTE_FORA) {
    texto = "FORA!";
    cor = ORANGE;
  }

  if (texto == NULL) {
    return;
  }

  int tamanho = 70;
  int largura_texto = MeasureText(texto, tamanho);

  DrawRectangle(0, 0, 1000, 700, Fade(BLACK, 0.35f));
  DrawText(texto, 500 - largura_texto / 2, 280, tamanho, cor);
}
