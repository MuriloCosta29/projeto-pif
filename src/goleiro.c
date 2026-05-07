#include "goleiro.h"
#include "raylib.h"

void inicializar_goleiro(Goleiro *goleiro, Gol *gol) {
  goleiro->largura = 40;
  goleiro->altura = 70;
  goleiro->x = gol->x + gol->largura / 2 - goleiro->largura / 2;
  goleiro->y = gol->y + gol->altura - goleiro->altura;
  goleiro->velocidade = 0;
  goleiro->esta_pulando = false;
}

int escolher_regiao_defesa(void) { return GetRandomValue(1, 9); }
