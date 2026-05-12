#include "fisica.h"

void inicializar_bola(Bola *bola) {
  bola->x = 500;
  bola->y = 570;
  bola->z = 0;

  bola->velocidade_x = 0;
  bola->velocidade_y = 0;
  bola->velocidade_z = 0;

  bola->potencia = 0;
  bola->curva = 0;

  bola->em_movimento = false;
  bola->visivel = true;
}

void atualizar_bola(Bola *b) {
  if (b->em_movimento) {
    b->x += b->velocidade_x;
    b->y += b->velocidade_y;

    b->z += b->velocidade_z;
    b->velocidade_z -= 0.35f;
    if (b->z < 0) {
      b->z = 0;
      b->velocidade_z = 0;
    }
    b->velocidade_x += b->curva;
    b->velocidade_x *= 0.992f;
    b->velocidade_y *= 0.997f;
  }
}

void resetar_bola(Bola *bola) {
  bola->x = 500;
  bola->y = 620;
  bola->z = 0;

  bola->velocidade_x = 0;
  bola->velocidade_y = 0;
  bola->velocidade_z = 0;

  bola->potencia = 0;
  bola->curva = 0;

  bola->em_movimento = false;
  bola->visivel = true;
}

void chutar_bola(Bola *bola, float direcao, float altura, float curva,
                 float forca_chute) {

  float potencia = 7.0f + (forca_chute * 7.0f);

  bola->velocidade_x = (direcao - 0.5f) * potencia * 1.85f;
  bola->velocidade_y = -(5.5f + potencia * 0.25f);
  bola->velocidade_z = 4.0f + altura * 8.0f;
  bola->curva = (curva - 0.5f) * 0.24f;

  bola->potencia = potencia;
  bola->em_movimento = true;
  bola->visivel = true;
}
