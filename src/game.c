#include "game.h"
#include "barreira.h"
#include "dados.h"
#include "fisica.h"
#include "gol.h"
#include "goleiro.h"
#include "placar.h"
#include "torcida.h"
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

static const Nivel niveis[] = {
    {COBRANCA_PENALTI, 0, 500, 620, 0, 0},
    {COBRANCA_PENALTI, 0, 500, 620, 0, 0},
    {COBRANCA_PENALTI, 0, 500, 620, 0, 0},
    {COBRANCA_FALTA_ESQUERDA, 1, 340, 620, 455, 390},
    {COBRANCA_FALTA_FRONTAL, 1, 500, 620, 490, 390},
    {COBRANCA_FALTA_DIREITA, 1, 660, 620, 525, 390},
    {COBRANCA_FALTA_ESQUERDA, 2, 340, 620, 425, 390},
    {COBRANCA_FALTA_FRONTAL, 2, 500, 620, 460, 390},
    {COBRANCA_FALTA_DIREITA, 2, 660, 620, 495, 390},
    {COBRANCA_FALTA_ESQUERDA, 3, 340, 620, 395, 390},
    {COBRANCA_FALTA_FRONTAL, 3, 500, 620, 430, 390},
    {COBRANCA_FALTA_DIREITA, 3, 660, 620, 465, 390},
    {COBRANCA_FALTA_ESQUERDA, 4, 340, 620, 365, 390},
    {COBRANCA_FALTA_FRONTAL, 4, 500, 620, 400, 390},
    {COBRANCA_FALTA_DIREITA, 4, 660, 620, 435, 390},
    {COBRANCA_FALTA_ESQUERDA, 5, 340, 620, 335, 390},
    {COBRANCA_FALTA_FRONTAL, 5, 500, 620, 370, 390},
    {COBRANCA_FALTA_DIREITA, 5, 660, 620, 405, 390},
};

static const int total_niveis = sizeof(niveis) / sizeof(niveis[0]);

static void resetar_medidor_chute(Jogo *jogo) {
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

static void aplicar_nivel(Jogo *jogo) {
  Nivel nivel = niveis[jogo->nivel_atual];

  liberar_barreira(jogo->barreira);
  resetar_bola(&jogo->bola);
  posicionar_bola(&jogo->bola, nivel.bola_x, nivel.bola_y);
  inicializar_goleiro(&jogo->goleiro, &jogo->gol);
  jogo->barreira = criar_barreira_posicionada(
      nivel.quantidade_barreira, nivel.barreira_x, nivel.barreira_y);
  jogo->tipo_cobranca_atual = nivel.tipo;
  jogo->chances_restantes = jogo->total_niveis - jogo->nivel_atual;
}

static void salvar_pontuacao_final(Jogo *jogo) {
  if (jogo->pontuacao_salva) {
    return;
  }

  salvar_score("JOGADOR", jogo->pontuacao_atual);
  jogo->qtd_scores = carregar_scores(jogo->scores, MAX_SCORES);
  jogo->pontuacao_salva = true;
}

void inicializar_jogo(Jogo *jogo) {
  srand(time(NULL));

  jogo->estado_atual = MENU;
  jogo->pontuacao_atual = 0;
  jogo->chances_restantes = total_niveis;
  jogo->nivel_atual = 0;
  jogo->total_niveis = total_niveis;
  jogo->barreira = NULL;
  jogo->pontuacao_salva = false;
  jogo->qtd_scores = carregar_scores(jogo->scores, MAX_SCORES);

  inicializar_gol(&jogo->gol);
  aplicar_nivel(jogo);
  inicializar_torcida(&jogo->torcida);
  jogo->resultado_chute = CHUTE_NENHUM;
  jogo->tempo_resultado = 0;

  jogo->medidor_atual.x = 200;
  jogo->medidor_atual.y = 640;
  jogo->medidor_atual.largura = 600;
  jogo->medidor_atual.altura = 25;
  jogo->medidor_atual.velocidade = 0.02f;
  resetar_medidor_chute(jogo);
}

void reiniciar_jogo(Jogo *jogo) {
  jogo->pontuacao_atual = 0;
  jogo->chances_restantes = total_niveis;
  jogo->nivel_atual = 0;
  jogo->total_niveis = total_niveis;
  jogo->pontuacao_salva = false;
  jogo->qtd_scores = carregar_scores(jogo->scores, MAX_SCORES);

  aplicar_nivel(jogo);
  inicializar_torcida(&jogo->torcida);
  jogo->resultado_chute = CHUTE_NENHUM;
  jogo->tempo_resultado = 0;
  resetar_medidor_chute(jogo);

  jogo->estado_atual = MIRANDO;
}

void resetar_cobranca(Jogo *jogo) {
  if (jogo->resultado_chute == CHUTE_NENHUM) {
    return;
  }

  if (jogo->resultado_chute == CHUTE_GOL) {
    jogo->nivel_atual++;
  } else {
    jogo->nivel_atual = 0;
  }

  if (jogo->nivel_atual >= jogo->total_niveis) {
    jogo->estado_atual = GAME_OVER;
    salvar_pontuacao_final(jogo);
    return;
  }

  aplicar_nivel(jogo);
  jogo->resultado_chute = CHUTE_NENHUM;
  jogo->tempo_resultado = 0;

  jogo->estado_atual = MIRANDO;
  resetar_medidor_chute(jogo);
}

void avancar_nivel_debug(Jogo *jogo) {
  jogo->nivel_atual++;

  if (jogo->nivel_atual >= jogo->total_niveis) {
    jogo->estado_atual = GAME_OVER;
    salvar_pontuacao_final(jogo);
    return;
  }

  aplicar_nivel(jogo);
  jogo->resultado_chute = CHUTE_NENHUM;
  jogo->tempo_resultado = 0;
  jogo->estado_atual = MIRANDO;
  resetar_medidor_chute(jogo);
}

void atualizar_jogo(Jogo *jogo) {
  if (jogo->estado_atual == RESULTADO) {
    jogo->tempo_resultado--;

    if (jogo->tempo_resultado <= 0) {
      resetar_cobranca(jogo);
    }

    return;
  }

  atualizar_barreira(jogo->barreira, &jogo->bola);
  atualizar_goleiro(&jogo->goleiro);
  atualizar_torcida(&jogo->torcida);

  if (!jogo->bola.em_movimento) {
    return;
  }

  if (bola_colidiu_barreira(&jogo->bola, jogo->barreira)) {
    jogo->bola.visivel = false;
    jogo->bola.em_movimento = false;
    torcida_reage(&jogo->torcida, TORCIDA_DESANIMADA);
    jogo->resultado_chute = CHUTE_BARREIRA;
    jogo->estado_atual = RESULTADO;
    jogo->tempo_resultado = 90;
    return;
  }

  int regiao = obter_regiao_gol(&jogo->gol, &jogo->bola);

  if (regiao != 0) {
    int regiao_defesa = jogo->goleiro.regiao_defesa;

    if (regiao_defesa == regiao) {
      tocar_defesa(&jogo->audio);
      torcida_reage(&jogo->torcida, TORCIDA_DESANIMADA);
      jogo->resultado_chute = CHUTE_DEFESA;
      jogo->estado_atual = RESULTADO;
      jogo->tempo_resultado = 90;
    } else {
      jogo->bola.visivel = false;
      jogo->bola.em_movimento = false;
      jogo->pontuacao_atual++;
      torcida_reage(&jogo->torcida, TORCIDA_COMEMORANDO);
      jogo->resultado_chute = CHUTE_GOL;
      jogo->estado_atual = RESULTADO;
      jogo->tempo_resultado = 90;
    }

    return;
  }

  if (bola_passou_fora_do_gol(&jogo->gol, &jogo->bola)) {
    tocar_fora(&jogo->audio);
    torcida_reage(&jogo->torcida, TORCIDA_DESANIMADA);
    jogo->resultado_chute = CHUTE_FORA;
    jogo->estado_atual = RESULTADO;
    jogo->tempo_resultado = 90;
    return;
  }

  if (jogo->bola.y > 760 || jogo->bola.x < -80 || jogo->bola.x > 1080) {
    tocar_fora(&jogo->audio);
    torcida_reage(&jogo->torcida, TORCIDA_DESANIMADA);
    jogo->resultado_chute = CHUTE_FORA;
    jogo->estado_atual = RESULTADO;
    jogo->tempo_resultado = 90;
  }
}
