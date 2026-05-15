#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"
#include <stdbool.h>

typedef struct {
  Sound chute;
  Sound defesa;
  Sound fora;

  bool inicializado;
} AudioJogo;

void inicializar_audio(AudioJogo *audio);
void liberar_audio(AudioJogo *audio);

void tocar_chute(AudioJogo *audio);
void tocar_defesa(AudioJogo *audio);
void tocar_fora(AudioJogo *audio);

#endif
