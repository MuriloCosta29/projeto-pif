#include "goleiro.h"
#include "raylib.h"

void inicializar_goleiro(Goleiro *goleiro, Gol *gol) {
  goleiro->largura = 40;
  goleiro->altura = 70;
  goleiro->x = gol->x + gol->largura / 2 - goleiro->largura / 2;
  goleiro->y = gol->y + gol->altura - goleiro->altura;
  goleiro->inicio_x = goleiro->x;
  goleiro->inicio_y = goleiro->y;
  goleiro->alvo_x = goleiro->x;
  goleiro->alvo_y = goleiro->y;
  goleiro->velocidade = 0;
  goleiro->regiao_defesa = 0;
  goleiro->tempo_defesa = 0;
  goleiro->duracao_defesa = 28;
  goleiro->esta_pulando = false;
  goleiro->defendendo = false;
}

void iniciar_defesa_goleiro(Goleiro *goleiro, Gol *gol) {
  int regiao = escolher_regiao_defesa();
  int linha = (regiao - 1) / 3;
  int coluna = (regiao - 1) % 3;

  float largura_coluna = gol->largura / 3.0f;
  float altura_linha = gol->altura / 3.0f;
  float centro_x = gol->x + coluna * largura_coluna + largura_coluna / 2.0f;
  float centro_y = gol->y + linha * altura_linha + altura_linha / 2.0f;

  goleiro->inicio_x = goleiro->x;
  goleiro->inicio_y = goleiro->y;
  goleiro->alvo_x = centro_x - goleiro->largura / 2.0f;
  goleiro->alvo_y = centro_y - goleiro->altura / 2.0f;
  goleiro->regiao_defesa = regiao;
  goleiro->tempo_defesa = 0;
  goleiro->duracao_defesa = 28;
  goleiro->defendendo = true;
  goleiro->esta_pulando = true;
}

void atualizar_goleiro(Goleiro *goleiro) {
  if (!goleiro->defendendo) {
    return;
  }

  goleiro->tempo_defesa++;

  float t = (float)goleiro->tempo_defesa / (float)goleiro->duracao_defesa;
  if (t > 1.0f) {
    t = 1.0f;
  }

  float suavizado = 1.0f - (1.0f - t) * (1.0f - t);
  goleiro->x =
      goleiro->inicio_x + (goleiro->alvo_x - goleiro->inicio_x) * suavizado;
  goleiro->y =
      goleiro->inicio_y + (goleiro->alvo_y - goleiro->inicio_y) * suavizado;

  if (t >= 1.0f) {
    goleiro->esta_pulando = false;
  }
}

int escolher_regiao_defesa(void) { return GetRandomValue(1, 9); }
