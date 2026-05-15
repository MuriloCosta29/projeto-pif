#include "audio.h"
#include "raylib.h"

static const char *audios_por_barreira[MAX_GRUPOS_BARREIRA_AUDIO][AUDIOS_POR_GRUPO_BARREIRA] = {
    {
        "assets/sons/niveis/barreira_0_1.wav",
        "assets/sons/niveis/barreira_0_2.wav",
        "assets/sons/niveis/barreira_0_3.wav",
        "assets/sons/niveis/barreira_0_4.wav",
    },
    {
        "assets/sons/niveis/barreira_1_1.wav",
        "assets/sons/niveis/barreira_1_2.wav",
        "assets/sons/niveis/barreira_1_3.wav",
        "assets/sons/niveis/barreira_1_4.wav",
    },
    {
        "assets/sons/niveis/barreira_2_1.wav",
        "assets/sons/niveis/barreira_2_2.wav",
        "assets/sons/niveis/barreira_2_3.wav",
        "assets/sons/niveis/barreira_2_4.wav",
    },
    {
        "assets/sons/niveis/barreira_3_1.wav",
        "assets/sons/niveis/barreira_3_2.wav",
        "assets/sons/niveis/barreira_3_3.wav",
        "assets/sons/niveis/barreira_3_4.wav",
    },
    {
        "assets/sons/niveis/barreira_4_1.wav",
        "assets/sons/niveis/barreira_4_2.wav",
        "assets/sons/niveis/barreira_4_3.wav",
        "assets/sons/niveis/barreira_4_4.wav",
    },
    {
        "assets/sons/niveis/barreira_5_1.wav",
        "assets/sons/niveis/barreira_5_2.wav",
        "assets/sons/niveis/barreira_5_3.wav",
        "assets/sons/niveis/barreira_5_4.wav",
    },
};

void inicializar_audio(AudioJogo *audio) {
  InitAudioDevice();

  audio->chute = LoadSound("assets/sons/chute.wav");
  audio->colisao = LoadSound("assets/sons/colisao.wav");
  audio->gol = LoadSound("assets/sons/gol.wav");
  audio->defesa = LoadSound("assets/sons/defesa.wav");
  audio->pulo = LoadSound("assets/sons/pulo.wav");
  audio->fora = LoadSound("assets/sons/fora.wav");

  for (int i = 0; i < MAX_GRUPOS_BARREIRA_AUDIO; i++) {
    for (int j = 0; j < AUDIOS_POR_GRUPO_BARREIRA; j++) {
      audio->inicio_nivel[i][j] = LoadSound(audios_por_barreira[i][j]);
    }
  }

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
  UnloadSound(audio->fora);

  for (int i = 0; i < MAX_GRUPOS_BARREIRA_AUDIO; i++) {
    for (int j = 0; j < AUDIOS_POR_GRUPO_BARREIRA; j++) {
      UnloadSound(audio->inicio_nivel[i][j]);
    }
  }

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

void tocar_audio_inicio_nivel(AudioJogo *audio, int quantidade_barreira) {
  if (!audio->inicializado) {
    return;
  }

  if (quantidade_barreira < 0) {
    quantidade_barreira = 0;
  }

  if (quantidade_barreira >= MAX_GRUPOS_BARREIRA_AUDIO) {
    quantidade_barreira = MAX_GRUPOS_BARREIRA_AUDIO - 1;
  }

  int audio_sorteado = GetRandomValue(0, AUDIOS_POR_GRUPO_BARREIRA - 1);

  PlaySound(audio->inicio_nivel[quantidade_barreira][audio_sorteado]);
}
void tocar_fora(AudioJogo *audio) {
  if (audio->inicializado) {
    PlaySound(audio->fora);
  }
}