#include "raylib.h"
#include "dados.h"
#include "fisica.h"
#include "gol.h"
#include "input.h"
#include "desenho.h"

void resetar_cobranca(Jogo *jogo) {
  resetar_bola(&jogo->bola);

  jogo->estado_atual = MIRANDO;

  jogo->etapa_chute = 0;
  jogo->direcao_chute = 0.5f;
  jogo->altura_chute = 0.5f;
  jogo->curva_chute = 0.5f;
  jogo->forca_chute = 0.5f;

  jogo->medidor_atual.valor_atual = 0.5f;
  jogo->medidor_atual.direcao_movimento = 1;
  jogo->medidor_atual.ativo = true;
  jogo->medidor_atual.tipo = 0;
}

int bola_entrou_no_gol(Jogo *jogo) {
  return jogo->bola.x >= jogo->gol.x &&
         jogo->bola.x <= jogo->gol.x + jogo->gol.largura &&
         jogo->bola.y >= jogo->gol.y &&
         jogo->bola.y <= jogo->gol.y + jogo->gol.altura;
}

int main() {
  InitWindow(1000, 700, "Stan James - Free Kick");
  SetTargetFPS(60);

  Jogo jogo = {0};

  inicializar_gol(&jogo.gol);

  inicializar_bola(&jogo.bola);

  jogo.estado_atual = MIRANDO;
  jogo.chances_restantes = 5;
  jogo.pontuacao_atual = 0;

  jogo.etapa_chute = 0;
  jogo.direcao_chute = 0.5f;
  jogo.altura_chute = 0.5f;
  jogo.curva_chute = 0.5f;
  jogo.forca_chute = 0.5f;

  jogo.medidor_atual.x = 200;
  jogo.medidor_atual.y = 640;
  jogo.medidor_atual.largura = 600;
  jogo.medidor_atual.altura = 25;
  jogo.medidor_atual.valor_atual = 0.5f;
  jogo.medidor_atual.velocidade = 0.02f;
  jogo.medidor_atual.direcao_movimento = 1;
  jogo.medidor_atual.ativo = true;
  jogo.medidor_atual.tipo = 0;

  while (!WindowShouldClose()) {
    processarInput(&jogo);
    atualizar_bola(&jogo.bola);

    if (bola_entrou_no_gol(&jogo)) {
      jogo.pontuacao_atual++;
      resetar_cobranca(&jogo);
    }

    if (jogo.bola.y > 760 || jogo.bola.x < -80 || jogo.bola.x > 1080) {
      jogo.chances_restantes--;
      resetar_cobranca(&jogo);
    }

    BeginDrawing();

    desenhar_campo();

    desenhar_gol_bonito(
      jogo.gol.x,
      jogo.gol.y,
      jogo.gol.largura,
      jogo.gol.altura
    );

    desenhar_bola(&jogo.bola);
    desenhar_hud(&jogo);
    desenhar_medidor(&jogo);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}