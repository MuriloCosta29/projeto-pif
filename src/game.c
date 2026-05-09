#include "game.h"
#include "barreira.h"
#include "fisica.h"
#include "gol.h"
#include "goleiro.h"
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

void inicializar_jogo(Jogo *jogo) {
  srand(time(NULL));

  jogo->estado_atual = MENU;
  jogo->pontuacao_atual = 0;
  jogo->chances_restantes = 5;

  inicializar_gol(&jogo->gol);
  inicializar_bola(&jogo->bola);
  inicializar_goleiro(&jogo->goleiro, &jogo->gol);
  jogo->barreira = criar_barreira(4);
  jogo->etapa_chute = 0;
  jogo->direcao_chute = 0.5f;
  jogo->altura_chute = 0.5f;
  jogo->curva_chute = 0.5f;
  jogo->forca_chute = 0.5f;

  jogo->medidor_atual.x = 200;
  jogo->medidor_atual.y = 640;
  jogo->medidor_atual.largura = 600;
  jogo->medidor_atual.altura = 25;
  jogo->medidor_atual.valor_atual = 0.5f;
  jogo->medidor_atual.velocidade = 0.02f;
  jogo->medidor_atual.direcao_movimento = 1;
  jogo->medidor_atual.ativo = true;
  jogo->medidor_atual.tipo = 0;
}

void resetar_cobranca(Jogo *jogo) {
  resetar_bola(&jogo->bola);
  resetar_barreira(jogo->barreira);

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

void atualizar_jogo(Jogo *jogo) {
  atualizar_barreira(jogo->barreira, &jogo->bola, &jogo->audio);

  if (bola_colidiu_barreira(&jogo->bola, jogo->barreira)) {
    tocar_colisao(&jogo->audio);
    jogo->chances_restantes--;
    resetar_cobranca(jogo);
    return;
  }

  int regiao = obter_regiao_gol(&jogo->gol, &jogo->bola);

  if (regiao != 0) {
    int regiao_defesa = escolher_regiao_defesa();

    if (regiao_defesa == regiao) {
      tocar_defesa(&jogo->audio);
      resetar_cobranca(jogo);
    } else {
      tocar_gol(&jogo->audio);
      jogo->pontuacao_atual++;
      resetar_cobranca(jogo);
    }
  }

  if (jogo->bola.y > 760 || jogo->bola.x < -80 || jogo->bola.x > 1080) {
    jogo->chances_restantes--;
    resetar_cobranca(jogo);
  }
}
