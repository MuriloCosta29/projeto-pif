#ifndef FISICA_H
#define FISICA_H

#include "dados.h"

void inicializar_bola(Bola *bola);
void atualizar_bola(Bola *bola);
void resetar_bola(Bola *bola);
void posicionar_bola(Bola *bola, float x, float y);
void chutar_bola(Bola *bola, float direcao, float altura, float curva,
                 float forca_chute);

#endif
