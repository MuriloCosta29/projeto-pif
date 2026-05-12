#include "gol.h"

void inicializar_gol(Gol *gol) {
  gol->x = 300;
  gol->y = 90;
  gol->largura = 400;
  gol->altura = 180;
  int contador = 1;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      gol->matriz[i][j] = contador;
      contador++;
    }
  }
}

int obter_regiao_gol(Gol *gol, Bola *bola) {
  float bola_y_visual = bola->y - bola->z;

  if (bola->x < gol->x || bola->x > gol->x + gol->largura ||
      bola_y_visual < gol->y || bola_y_visual > gol->y + gol->altura) {
    return 0;
  }
  float largura_coluna = gol->largura / 3.0f;
  float altura_linha = gol->altura / 3.0f;

  int coluna = (bola->x - gol->x) / largura_coluna;
  int linha = (bola_y_visual - gol->y) / altura_linha;

  if (coluna > 2) {
    coluna = 2;
  }
  if (coluna < 0) {
    coluna = 0;
  }

  if (linha > 2) {
    linha = 2;
  }
  if (linha < 0) {
    linha = 0;
  }

  return gol->matriz[linha][coluna];
}

bool bola_passou_fora_do_gol(Gol *gol, Bola *bola) {
  float bola_y_visual = bola->y - bola->z;
  bool passou_linha_gol = bola_y_visual <= gol->y + gol->altura;
  bool fora_lateral = bola->x < gol->x || bola->x > gol->x + gol->largura;
  bool fora_por_cima = bola_y_visual < gol->y;

  return bola->em_movimento && passou_linha_gol &&
         (fora_lateral || fora_por_cima);
}
