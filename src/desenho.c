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

void desenhar_gol(Gol *gol, Texture2D sprite) {
  float escala = 1.45f;
  float largura = gol->largura * escala;
  float altura = gol->altura * escala;

  float centro_x = gol->x + gol->largura / 2.0f;
  float centro_y = gol->y + gol->altura / 2.0f;

  Rectangle src = {0, 0, (float)sprite.width, (float)sprite.height};
  Rectangle dst = {centro_x - largura / 2.0f, centro_y - altura / 2.0f, largura,
                   altura};
  DrawTexturePro(sprite, src, dst, (Vector2){0, 0}, 0, WHITE);
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

  float painel_x = m->x + 80;
  float painel_largura = m->largura - 160;
  float painel_altura = 58;
  float painel_y = 700 - painel_altura - 4;
  Rectangle painel = {painel_x, painel_y, painel_largura, painel_altura};
  Rectangle trilha = {painel_x + 110, painel_y + 22, painel_largura - 170, 14};
  Color azul_fundo = (Color){20, 43, 74, 235};
  Color azul_claro = (Color){52, 104, 156, 255};
  Color dourado = (Color){242, 196, 70, 255};
  Color vermelho = (Color){210, 36, 38, 255};
  Color texto = (Color){245, 248, 235, 255};

  DrawRectangleRec(painel, azul_fundo);
  DrawRectangleLinesEx(painel, 2, dourado);

  const char *etapas[] = {"DIR", "ALT", "CUR", "POT"};
  int abas = 4;
  float aba_largura = 22;
  float abas_y = painel_y + 6;
  float abas_x = painel_x + 8;
  for (int i = 0; i < abas; i++) {
    Rectangle aba = {abas_x + i * (aba_largura + 2), abas_y, aba_largura, 16};
    bool ativa = jogo->etapa_chute == i;
    DrawRectangleRec(aba, ativa ? dourado : (Color){25, 55, 95, 255});
    DrawRectangleLinesEx(aba, 1, ativa ? WHITE : azul_claro);

    int text_w = MeasureText(etapas[i], 10);
    DrawText(etapas[i], aba.x + aba.width / 2 - text_w / 2, aba.y + 3, 10,
             ativa ? (Color){30, 25, 12, 255} : texto);
  }

  int titulo_w = MeasureText(titulo, 14);
  DrawText(titulo, painel_x + 8, abas_y + 22, 14, dourado);

  DrawRectangleRec(trilha, (Color){8, 14, 24, 255});
  DrawRectangleLinesEx(trilha, 1, (Color){210, 225, 235, 255});

  for (int i = 1; i < 10; i++) {
    float tick_x = trilha.x + (trilha.width * i) / 10.0f;
    int tick_h = i == 5 ? 16 : 8;
    DrawLineEx((Vector2){tick_x, trilha.y + trilha.height / 2 - tick_h / 2},
               (Vector2){tick_x, trilha.y + trilha.height / 2 + tick_h / 2},
               i == 5 ? 2 : 1, Fade(WHITE, i == 5 ? 0.85f : 0.45f));
  }

  DrawRectangle(trilha.x + 2, trilha.y + 2, trilha.width - 4, trilha.height - 4,
                (Color){236, 238, 222, 255});
  DrawRectangle(trilha.x + trilha.width * 0.42f, trilha.y + 2,
                trilha.width * 0.16f, trilha.height - 4,
                (Color){96, 184, 82, 255});

  int rot_size = 10;
  int meio_w = MeasureText(rot_meio, rot_size);
  int dir_w = MeasureText(rot_dir, rot_size);
  int rot_y = trilha.y + trilha.height + 3;
  DrawText(rot_esq, trilha.x, rot_y, rot_size, texto);
  DrawText(rot_meio, trilha.x + trilha.width / 2 - meio_w / 2, rot_y, rot_size,
           texto);
  DrawText(rot_dir, trilha.x + trilha.width - dir_w, rot_y, rot_size, texto);

  float marcadorX = trilha.x + m->valor_atual * trilha.width;
  float tempo = GetTime();
  float pulso = 0.55f + 0.45f * sinf(tempo * 7.0f);
  Vector2 p1 = {marcadorX, trilha.y - 2};
  Vector2 p2 = {marcadorX - 6, trilha.y - 11 - pulso * 2.0f};
  Vector2 p3 = {marcadorX + 6, trilha.y - 11 - pulso * 2.0f};
  DrawTriangle(p1, p2, p3, vermelho);
  DrawTriangleLines(p1, p2, p3, WHITE);
  DrawRectangle(marcadorX - 1, trilha.y, 3, trilha.height, vermelho);

  Vector2 icone_centro = {painel_x + painel_largura - 25, painel_y + 30};
  Color icone_cor = Fade(dourado, 0.60f + pulso * 0.40f);

  if (jogo->etapa_chute == 0) {
    float direcao = m->valor_atual - 0.5f;

    if (fabsf(direcao) < 0.10f) {
      DrawLineEx((Vector2){icone_centro.x, icone_centro.y + 12},
                 (Vector2){icone_centro.x, icone_centro.y - 12}, 3, icone_cor);
      DrawTriangle((Vector2){icone_centro.x, icone_centro.y - 17},
                   (Vector2){icone_centro.x - 5, icone_centro.y - 8},
                   (Vector2){icone_centro.x + 5, icone_centro.y - 8}, icone_cor);
    } else if (direcao < 0.0f) {
      Vector2 inicio = {icone_centro.x + 15, icone_centro.y};
      Vector2 fim = {icone_centro.x - 15, icone_centro.y};

      DrawLineEx(inicio, fim, 3, icone_cor);
      DrawTriangle((Vector2){fim.x - 6, fim.y},
                   (Vector2){fim.x + 5, fim.y + 6},
                   (Vector2){fim.x + 5, fim.y - 6}, icone_cor);
    } else {
      Vector2 inicio = {icone_centro.x - 15, icone_centro.y};
      Vector2 fim = {icone_centro.x + 15, icone_centro.y};

      DrawLineEx(inicio, fim, 3, icone_cor);
      DrawTriangle((Vector2){fim.x + 6, fim.y},
                   (Vector2){fim.x - 4, fim.y - 5},
                   (Vector2){fim.x - 4, fim.y + 5}, icone_cor);
    }
  } else if (jogo->etapa_chute == 1) {
    float altura_seta = 8.0f + m->valor_atual * 16.0f;
    Vector2 base = {icone_centro.x, icone_centro.y + 12};
    Vector2 ponta = {icone_centro.x, base.y - altura_seta};

    DrawLineEx(base, ponta, 3, icone_cor);
    DrawTriangle((Vector2){ponta.x, ponta.y - 5},
                 (Vector2){ponta.x - 5, ponta.y + 3},
                 (Vector2){ponta.x + 5, ponta.y + 3}, icone_cor);
    DrawLineEx((Vector2){icone_centro.x - 12, base.y},
               (Vector2){icone_centro.x + 12, base.y}, 2, Fade(WHITE, 0.65f));
  } else if (jogo->etapa_chute == 2) {
    float curva = m->valor_atual - 0.5f;
    float intensidade = fabsf(curva) * 2.0f;

    if (intensidade < 0.18f) {
      Vector2 inicio = {icone_centro.x, icone_centro.y + 12};
      Vector2 fim = {icone_centro.x, icone_centro.y - 12};

      DrawLineEx(inicio, fim, 3, icone_cor);
      DrawTriangle((Vector2){fim.x, fim.y - 5}, (Vector2){fim.x - 5, fim.y + 3},
                   (Vector2){fim.x + 5, fim.y + 3}, icone_cor);
      DrawLineEx((Vector2){icone_centro.x - 10, icone_centro.y},
                 (Vector2){icone_centro.x + 10, icone_centro.y}, 2,
                 Fade(WHITE, 0.55f));
    } else {
      float direcao = curva < 0.0f ? 1.0f : -1.0f;
      float abertura = 10.0f + intensidade * 7.0f;
      Vector2 inicio = {icone_centro.x, icone_centro.y + 13.0f};
      Vector2 controle = {icone_centro.x + direcao * abertura,
                          icone_centro.y + 3.0f};
      Vector2 fim = {icone_centro.x + direcao * abertura,
                     icone_centro.y - 12.0f};
      Vector2 anterior = inicio;

      for (int i = 1; i <= 14; i++) {
        float t = (float)i / 14.0f;
        float inv = 1.0f - t;
        Vector2 ponto = {
            inv * inv * inicio.x + 2.0f * inv * t * controle.x + t * t * fim.x,
            inv * inv * inicio.y + 2.0f * inv * t * controle.y + t * t * fim.y};

        DrawLineEx(anterior, ponto, 2, icone_cor);
        anterior = ponto;
      }

      if (direcao < 0.0f) {
        DrawTriangle((Vector2){fim.x - 6.0f, fim.y},
                     (Vector2){fim.x + 4.0f, fim.y + 6.0f},
                     (Vector2){fim.x + 4.0f, fim.y - 6.0f}, icone_cor);
      } else {
        DrawTriangle((Vector2){fim.x + 6.0f, fim.y},
                     (Vector2){fim.x - 4.0f, fim.y - 6.0f},
                     (Vector2){fim.x - 4.0f, fim.y + 6.0f}, icone_cor);
      }
      DrawCircle(inicio.x, inicio.y, 2, Fade(WHITE, 0.75f));
    }
  } else if (jogo->etapa_chute == 3) {
    float preenchido = m->valor_atual * 5.0f;
    for (int i = 0; i < 5; i++) {
      Color barra_cor = i < preenchido ? icone_cor : Fade(WHITE, 0.25f);
      float altura_barra = 5.0f + i * 3.0f;
      DrawRectangle(icone_centro.x - 16 + i * 7,
                    icone_centro.y + 12 - altura_barra, 5, altura_barra,
                    barra_cor);
      DrawRectangleLines(icone_centro.x - 16 + i * 7,
                         icone_centro.y + 12 - altura_barra, 5, altura_barra,
                         Fade(BLACK, 0.45f));
    }
  }
}

void desenhar_hud(Jogo *jogo) {
  const char *tipo = "PENALTI";

  if (jogo->tipo_cobranca_atual == COBRANCA_FALTA_ESQUERDA) {
    tipo = "FALTA ESQ";
  } else if (jogo->tipo_cobranca_atual == COBRANCA_FALTA_FRONTAL) {
    tipo = "FALTA MEIO";
  } else if (jogo->tipo_cobranca_atual == COBRANCA_FALTA_DIREITA) {
    tipo = "FALTA DIR";
  }

  Rectangle painel = {20, 500, 175, 112};
  DrawRectangleRounded(painel, 0.12f, 8, Fade((Color){20, 35, 28, 255}, 0.78f));
  DrawRectangleRoundedLines(painel, 0.12f, 8, (Color){235, 235, 220, 210});

  DrawText(TextFormat("FASE  %d/%d", jogo->nivel_atual + 1, jogo->total_niveis),
           36, 514, 19, WHITE);
  DrawText(tipo, 36, 539, 18, (Color){215, 225, 215, 255});
  DrawText(TextFormat("GOLS  %d", jogo->pontuacao_atual), 36, 564, 22,
           (Color){255, 235, 120, 255});
  DrawText("SPACE: travar", 36, 592, 16, (Color){215, 225, 215, 255});
}

void desenhar_goleiro(Goleiro *goleiro, Texture2D sprite) {
  float centro_x = goleiro->x + goleiro->largura / 2;
  float fim_calcao = goleiro->y + goleiro->altura;

  DrawEllipse(centro_x, fim_calcao + 24, 26, 6, Fade(BLACK, 0.3f));

  float display_h = 150.0f;
  float display_w = display_h * ((float)sprite.width / (float)sprite.height);

  float rotacao = 0.0f;
  if (goleiro->defendendo) {
    float distancia_x = goleiro->alvo_x - goleiro->inicio_x;
    rotacao = distancia_x * 0.08f;

    if (rotacao > 24.0f) {
      rotacao = 24.0f;
    } else if (rotacao < -24.0f) {
      rotacao = -24.0f;
    }

    float alvo_cx = goleiro->alvo_x + goleiro->largura / 2;
    float alvo_cy = goleiro->alvo_y + goleiro->altura / 2;
    DrawCircleLines(alvo_cx, alvo_cy, 18,
                    Fade((Color){255, 235, 120, 255}, 0.7f));
  }

  Rectangle src = {0, 0, (float)sprite.width, (float)sprite.height};
  Rectangle dst = {centro_x, fim_calcao + 24 - display_h / 2, display_w,
                   display_h};
  DrawTexturePro(sprite, src, dst, (Vector2){display_w / 2, display_h / 2},
                 rotacao, WHITE);
}

void desenhar_torcida(Torcida *torcida, Texture2D arquibancada) {
  if (arquibancada.id == 0) {
    return;
  }

  float largura = 1060.0f;
  float altura =
      largura * ((float)arquibancada.height / (float)arquibancada.width);
  float x = -30.0f;
  float y = -82.0f;

  DrawRectangleGradientV(0, 0, 1000, 220, (Color){70, 140, 215, 255},
                         (Color){150, 205, 235, 255});

  Rectangle src = {0, 0, (float)arquibancada.width, (float)arquibancada.height};
  Rectangle dst = {x, y, largura, altura};
  DrawTexturePro(arquibancada, src, dst, (Vector2){0, 0}, 0, WHITE);

  DrawRectangleGradientV(0, 165, 1000, 58, (Color){42, 50, 62, 255},
                         (Color){24, 92, 45, 255});
  DrawRectangle(0, 165, 1000, 3, Fade(WHITE, 0.22f));
  DrawRectangle(0, 220, 1000, 4, (Color){20, 76, 36, 255});

  Color placa_verde = (Color){31, 145, 78, 255};
  Color placa_amarela = (Color){238, 204, 42, 255};
  Color placa_azul = (Color){43, 96, 185, 255};
  Color placa_vermelha = (Color){202, 42, 48, 255};
  Color placa_branca = (Color){230, 230, 220, 255};

  DrawRectangle(80, 178, 130, 28, placa_verde);
  DrawRectangle(220, 178, 130, 28, placa_amarela);
  DrawRectangle(360, 178, 130, 28, placa_azul);
  DrawRectangle(510, 178, 130, 28, placa_vermelha);
  DrawRectangle(650, 178, 130, 28, placa_branca);
  DrawRectangle(790, 178, 130, 28, placa_verde);

  for (int i = 0; i < 6; i++) {
    int px = 80 + i * 140;
    DrawRectangleLines(px, 178, 130, 28, Fade(BLACK, 0.30f));
  }

  if (torcida->estado == TORCIDA_DESANIMADA) {
    DrawRectangle(0, 0, 1000, 224, Fade(BLACK, 0.20f));
    return;
  }

  if (torcida->estado == TORCIDA_COMEMORANDO) {
    Color cores[] = {
        (Color){245, 210, 38, 255},  (Color){40, 165, 85, 255},
        (Color){220, 50, 55, 255},   (Color){45, 105, 200, 255},
        (Color){245, 245, 245, 255},
    };

    for (int i = 0; i < 30; i++) {
      float fase = torcida->tempo * 0.08f + i * 1.7f;
      float cx = x + 30.0f + fmodf(i * 47.0f, largura - 60.0f);
      float cy = y + 24.0f + fmodf(i * 19.0f, altura * 0.55f);
      float queda = fmodf(torcida->tempo * 1.4f + i * 11.0f, 34.0f);
      Rectangle papel = {cx + sinf(fase) * 4.0f, cy + queda, 5, 3};
      DrawRectangleRec(papel, cores[i % 5]);
    }
  }
}

void desenhar_barreira(Defensor *barreira, Texture2D sprite_a,
                       Texture2D sprite_b) {
  Defensor *atual = barreira;
  int indice = 0;

  while (atual != NULL) {
    float centro_x = atual->x + atual->largura / 2;
    float fim_calcao = atual->y + atual->altura;

    float deslocamento_pulo = 0;
    if (atual->esta_pulando) {
      float progresso = (30 - atual->tempo_pulo) / 30.0f;
      deslocamento_pulo = -4 * progresso * (1 - progresso) * 40;
    }

    DrawEllipse(centro_x, fim_calcao + 28, atual->largura * 0.85f, 4,
                Fade(BLACK, 0.3f));

    Texture2D sprite = (indice % 2 == 0) ? sprite_a : sprite_b;
    float display_h = 130.0f;
    float display_w = display_h * ((float)sprite.width / (float)sprite.height);

    Rectangle src = {0, 0, (float)sprite.width, (float)sprite.height};
    Rectangle dst = {centro_x - display_w / 2,
                     fim_calcao + 28 - display_h + deslocamento_pulo, display_w,
                     display_h};

    DrawTexturePro(sprite, src, dst, (Vector2){0, 0}, 0, WHITE);

    atual = atual->proximo;
    indice++;
  }
}

void desenhar_cobrador(Bola *bola, Texture2D sprite) {
  float pos_x = bola->x - 38;
  float pos_y_pes = bola->y + 8;

  DrawEllipse(pos_x, pos_y_pes + 6, 24, 5, Fade(BLACK, 0.3f));

  float display_h = 150.0f;
  float display_w = display_h * ((float)sprite.width / (float)sprite.height);

  Rectangle src = {0, 0, (float)sprite.width, (float)sprite.height};
  Rectangle dst = {pos_x - display_w / 2, pos_y_pes - display_h, display_w,
                   display_h};

  DrawTexturePro(sprite, src, dst, (Vector2){0, 0}, 0, WHITE);
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

  const char *ranking = "TOP 5";
  int ranking_w = MeasureText(ranking, 24);
  DrawText(ranking, 500 - ranking_w / 2, 455, 24, (Color){255, 215, 100, 255});

  for (int i = 0; i < jogo->qtd_scores; i++) {
    const char *linha = TextFormat("%d. %s  %d", i + 1, jogo->scores[i].nome,
                                   jogo->scores[i].pontuacao);
    int linha_w = MeasureText(linha, 20);
    DrawText(linha, 500 - linha_w / 2, 488 + i * 24, 20, LIGHTGRAY);
  }

  int instr_w = MeasureText(instrucao, 26);
  DrawText(instrucao, 500 - instr_w / 2, 625, 26, LIGHTGRAY);
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
