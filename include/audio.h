#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"
#include <stdbool.h>

#define MAX_GRUPOS_BARREIRA_AUDIO 6
#define AUDIOS_POR_GRUPO_BARREIRA 4

typedef struct {
  Sound chute;
  Sound colisao;
  Sound gol;
  Sound defesa;
  Sound pulo;
  Sound fora;

  Sound inicio_nivel[MAX_GRUPOS_BARREIRA_AUDIO][AUDIOS_POR_GRUPO_BARREIRA];

  bool inicializado;
} AudioJogo;

void inicializar_audio(AudioJogo *audio);
void liberar_audio(AudioJogo *audio);

void tocar_chute(AudioJogo *audio);
void tocar_colisao(AudioJogo *audio);
void tocar_gol(AudioJogo *audio);
void tocar_defesa(AudioJogo *audio)
void tocar_fora(AudioJogo *audio);
void tocar_pulo(AudioJogo *audio);

void tocar_audio_inicio_nivel(AudioJogo *audio, int quantidade_barreira);

#endif