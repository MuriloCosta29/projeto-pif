#include "audio.h"
#include "raylib.h"

static Sound carregar_som_opcional(const char *caminho) {
  if (!FileExists(caminho)) {
    return (Sound){0};
  }

  return LoadSound(caminho);
}

static void liberar_som_se_valido(Sound som) {
  if (IsSoundValid(som)) {
    UnloadSound(som);
  }
}

static void tocar_som_se_valido(Sound som) {
  if (IsSoundValid(som)) {
    PlaySound(som);
  }
}

void inicializar_audio(AudioJogo *audio) {
  InitAudioDevice();

  audio->chute = carregar_som_opcional("assets/sons/chute.wav");
  audio->defesa = carregar_som_opcional("assets/sons/defesa.wav");
  audio->fora = carregar_som_opcional("assets/sons/fora.wav");

  audio->inicializado = true;
}

void liberar_audio(AudioJogo *audio) {
  if (!audio->inicializado) {
    return;
  }

  liberar_som_se_valido(audio->chute);
  liberar_som_se_valido(audio->defesa);
  liberar_som_se_valido(audio->fora);

  CloseAudioDevice();
  audio->inicializado = false;
}

void tocar_chute(AudioJogo *audio) {
  if (audio->inicializado) {
    tocar_som_se_valido(audio->chute);
  }
}

void tocar_defesa(AudioJogo *audio) {
  if (audio->inicializado) {
    tocar_som_se_valido(audio->defesa);
  }
}

void tocar_fora(AudioJogo *audio) {
  if (audio->inicializado) {
    tocar_som_se_valido(audio->fora);
  }
}
