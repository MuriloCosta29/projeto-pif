#ifndef PLACAR_H
#define PLACAR_H

#include "dados.h"

int carregar_scores(Score scores[], int max_scores);
void salvar_score(const char *nome, int pontuacao);

#endif
