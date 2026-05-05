#include "fisica.h"

void inicializar_bola(Bola *bola) {
  bola->x = 400;
  bola->y = 520;

  bola->velocidade_x = 0;
  bola->velocidade_y = 0;

  bola->potencia = 0;
  bola->curva = 0;

  bola->em_movimento = false;
}

void atualizar_bola(Bola *b) {
  if (b->em_movimento) {
    b->x += b->velocidade_x;
    b->y += b->velocidade_y;

    b->velocidade_y += 0.2f;     // gravidade
    b->velocidade_x += b->curva; // curva/efeito da bola
  }
}

void resetar_bola(Bola *bola) {
  bola->x = 400;
  bola->y = 520;

  bola->velocidade_x = 0;
  bola->velocidade_y = 0;

  bola->potencia = 0;
  bola->curva = 0;

  bola->em_movimento = false;
}

void chutar_bola(Bola *bola, float direcao, float altura, float curva,
                 float forca_chute) {

  float forca = 6.0f + (forca_chute * 8.0f);
  bola->velocidade_x = (direcao - 0.5f) * forca;
  bola->velocidade_y = -(3.0f + altura * forca);
  bola->curva = (curva - 0.5f) * 0.12f;

  bola->potencia = forca;
  bola->em_movimento = true;
}
