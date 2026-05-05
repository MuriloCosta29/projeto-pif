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
