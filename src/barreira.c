#include "barreira.h"
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
