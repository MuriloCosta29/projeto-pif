#include "barreira.h"
#include <stdbool.h>
#include <stdlib.h>

Defensor *criar_barreira(int quantidade) {
  Defensor *inicio = NULL;
  Defensor *anterior = NULL;

  for (int i = 0; i < quantidade; i++) {
    Defensor *novo = malloc(sizeof(Defensor));

    if (novo == NULL) {
      return inicio;
    }

    novo->largura = 22;
    novo->altura = 60;
    novo->x = 400 + i * 60;
    novo->y = 390;
    novo->esta_pulando = false;
    novo->tempo_pulo = 0;
    novo->ja_tentou_pular = false;
    novo->proximo = NULL;

    if (inicio == NULL) {
      inicio = novo;
    }

    if (anterior != NULL) {
      anterior->proximo = novo;
    }
    anterior = novo;
  }
  return inicio;
}

void liberar_barreira(Defensor *barreira) {
  Defensor *atual = barreira;

  while (atual != NULL) {
    Defensor *proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }
}

void resetar_barreira(Defensor *barreira) {
  Defensor *atual = barreira;
  while (atual != NULL) {
    atual->esta_pulando = false;
    atual->tempo_pulo = 0;
    atual->ja_tentou_pular = false;
    atual = atual->proximo;
  }
}

void atualizar_barreira(Defensor *barreira, Bola *bola, AudioJogo *audio) {
  Defensor *atual = barreira;

  while (atual != NULL) {
    bool bola_na_faixa_y =
        bola->y >= atual->y && bola->y <= atual->y + atual->altura;

    if (bola_na_faixa_y && !atual->ja_tentou_pular) {
      atual->ja_tentou_pular = true;
      if (rand() % 100 < 30) {
        atual->esta_pulando = true;
        atual->tempo_pulo = 30;
        tocar_pulo(audio);
      }
    }

    if (atual->esta_pulando) {
      atual->tempo_pulo--;
      if (atual->tempo_pulo <= 0) {
        atual->esta_pulando = false;
        atual->tempo_pulo = 0;
      }
    }

    atual = atual->proximo;
  }
}

bool bola_colidiu_barreira(Bola *bola, Defensor *barreira) {
  Defensor *atual = barreira;
  float raio = 10;

  while (atual != NULL) {
    float altura_bloqueio = 38.0f;

    if (atual->esta_pulando) {
      altura_bloqueio += 28.0f;
    }

    bool colidiu_xy = bola->x + raio >= atual->x &&
                      bola->x - raio <= atual->x + atual->largura &&
                      bola->y + raio >= atual->y &&
                      bola->y - raio <= atual->y + atual->altura;

    bool baixa_o_bastante = bola->z < altura_bloqueio;

    if (colidiu_xy && baixa_o_bastante) {
      return true;
    }

    atual = atual->proximo;
  }
  return false;
}
