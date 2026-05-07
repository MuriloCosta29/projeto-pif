#include "gol.h"

void inicializar_gol(Gol *gol) {
  gol->x = 250;
  gol->y = 100;
  gol->largura = 300;
  gol->altura = 120;
  int contador = 1;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      gol->matriz[i][j] = contador;
      contador++;
    }
  }
}

int obter_regiao_gol(Gol *gol, Bola *bola) {
  if (bola->x < gol->x || bola->x > gol->x + gol->largura || bola->y < gol->y ||
      bola->y > gol->y + gol->altura) {
    return 0;
  }
  float largura_coluna = gol->largura / 3.0f;
  float altura_linha = gol->altura / 3.0f;

  int coluna = (bola->x - gol->x) / largura_coluna;
  int linha = (bola->y - gol->y) / altura_linha;

  if (coluna > 2) {
    coluna = 2;
  }

  if (linha > 2) {
    linha = 2;
  }

  return gol->matriz[linha][coluna];
}
