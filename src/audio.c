#include "audio.h"

void inicializar_audio(AudioJogo *audio) {
  InitAudioDevice();

  audio->chute = LoadSound("assets/sons/chute.wav");
  audio->colisao = LoadSound("assets/sons/colisao.wav");
  audio->gol = LoadSound("assets/sons/gol.wav");
  audio->defesa = LoadSound("assets/sons/defesa.wav");
  audio->pulo = LoadSound("assets/sons/pulo.wav");

  audio->inicializado = true;
}

void liberar_audio(AudioJogo *audio) {
  if (!audio->inicializado) {
    return;
  }

  UnloadSound(audio->chute);
  UnloadSound(audio->colisao);
  UnloadSound(audio->gol);
  UnloadSound(audio->defesa);
  UnloadSound(audio->pulo);

  CloseAudioDevice();
  audio->inicializado = false;
}

void tocar_chute(AudioJogo *audio) {
  if (audio->inicializado) {
    PlaySound(audio->chute);
  }
}

void tocar_colisao(AudioJogo *audio) {
  if (audio->inicializado) {
    PlaySound(audio->colisao);
  }
}

void tocar_gol(AudioJogo *audio) {
  if (audio->inicializado) {
    PlaySound(audio->gol);
  }
}

void tocar_defesa(AudioJogo *audio) {
  if (audio->inicializado) {
    PlaySound(audio->defesa);
  }
}

void tocar_pulo(AudioJogo *audio) {
  if (audio->inicializado) {
    PlaySound(audio->pulo);
  }
}
