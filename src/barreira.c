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

    novo->largura = 30;
    novo->altura = 80;
    novo->x = 420 + i * 35;
    novo->y = 310;
    novo->esta_pulando = false;
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

bool bola_colidiu_barreira(Bola *bola, Defensor *barreira) {
  Defensor *atual = barreira;
  float raio = 10;

  while (atual != NULL) {
    bool colidiu = bola->x + raio >= atual->x &&
                   bola->x - raio <= atual->x + atual->largura &&
                   bola->y + raio >= atual->y &&
                   bola->y - raio <= atual->y + atual->altura;

    if (colidiu) {
      return true;
    }

    atual = atual->proximo;
  }
  return false;
}
