// Por que `Jogo *jogo`? Porquê essas funções precisam alterar o estado do jogo.
// Se passar em ponteiro, mexe numa cópia. Com ponteiro mexe no jogo real.

#include "dados.h"

void inicializar_jogo(Jogo *jogo);
void atualizar_jogo(Jogo *jogo);
void resetar_cobranca(Jogo *jogo);
