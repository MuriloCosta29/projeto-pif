#include "placar.h"
#include "raylib.h"
#include <stdio.h>

#define ARQUIVO_SCORES "data/scores.txt"
#define ARQUIVO_SCORES_FALLBACK "scores.txt"

static FILE *abrir_arquivo_scores(const char *modo, const char **caminho_usado) {
  FILE *arquivo = fopen(ARQUIVO_SCORES, modo);

  if (arquivo != NULL) {
    *caminho_usado = ARQUIVO_SCORES;
    return arquivo;
  }

  arquivo = fopen(ARQUIVO_SCORES_FALLBACK, modo);
  if (arquivo != NULL) {
    *caminho_usado = ARQUIVO_SCORES_FALLBACK;
  }

  return arquivo;
}

static void ordenar_scores(Score scores[], int qtd) {
  for (int i = 0; i < qtd - 1; i++) {
    for (int j = i + 1; j < qtd; j++) {
      if (scores[j].pontuacao > scores[i].pontuacao) {
        Score temp = scores[i];
        scores[i] = scores[j];
        scores[j] = temp;
      }
    }
  }
}

int carregar_scores(Score scores[], int max_scores) {
  const char *caminho_usado = NULL;
  FILE *arquivo = abrir_arquivo_scores("r", &caminho_usado);
  int qtd = 0;

  if (arquivo == NULL) {
    return 0;
  }

  while (qtd < max_scores &&
         fscanf(arquivo, "%49s %d", scores[qtd].nome,
                &scores[qtd].pontuacao) == 2) {
    qtd++;
  }

  fclose(arquivo);
  ordenar_scores(scores, qtd);
  return qtd;
}

void salvar_score(const char *nome, int pontuacao) {
  Score scores[MAX_SCORES + 1];
  int qtd = carregar_scores(scores, MAX_SCORES);

  snprintf(scores[qtd].nome, sizeof(scores[qtd].nome), "%s", nome);
  scores[qtd].pontuacao = pontuacao;
  qtd++;

  ordenar_scores(scores, qtd);

  if (qtd > MAX_SCORES) {
    qtd = MAX_SCORES;
  }

  const char *caminho_usado = NULL;
  FILE *arquivo = abrir_arquivo_scores("w", &caminho_usado);
  if (arquivo == NULL) {
    TraceLog(LOG_WARNING, "Nao foi possivel salvar scores");
    return;
  }

  for (int i = 0; i < qtd; i++) {
    fprintf(arquivo, "%s %d\n", scores[i].nome, scores[i].pontuacao);
  }

  fclose(arquivo);
  TraceLog(LOG_INFO, "Score salvo em %s", caminho_usado);
}
