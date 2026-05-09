#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"
#include <stdbool.h>

typedef struct {
  Sound chute;
  Sound colisao;
  Sound gol;
  Sound defesa;
  Sound pulo;
  bool inicializado;
} AudioJogo;

void inicializar_audio(AudioJogo *audio);
void liberar_audio(AudioJogo *audio);

void tocar_chute(AudioJogo *audio);
void tocar_colisao(AudioJogo *audio);
void tocar_gol(AudioJogo *audio);
void tocar_defesa(AudioJogo *audio);
void tocar_pulo(AudioJogo *audio);

#endif
