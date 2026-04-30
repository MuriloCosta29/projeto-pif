#include "input.h"
#include "raylib.h"

void atualizarMedidor(Medidor *m) {
    if (!m->ativo) {
        return;
    }

    m->valor_atual += m->velocidade * m->direcao_movimento;

    if (m->valor_atual >= 1.0f) {
        m->valor_atual = 1.0f;
        m->direcao_movimento = -1;
    }

    if (m->valor_atual <= 0.0f) {
        m->valor_atual = 0.0f;
        m->direcao_movimento = 1;
    }
}

void processarInput(Jogo *j) {
    Medidor *m = &j->medidor_atual;

    if (j->estado_atual != 1) {
        return;
    }

    if (j->bola.em_movimento) {
        return;
    }

    atualizarMedidor(m);

    if (IsKeyPressed(KEY_SPACE)) {

        switch (j->etapa_chute) {

            case 0:
                j->direcao_chute = m->valor_atual;
                m->tipo = 1;
                break;

            case 1:
                j->altura_chute = m->valor_atual;
                m->tipo = 2;
                break;

            case 2:
                j->curva_chute = m->valor_atual;
                m->tipo = 3;
                break;

            case 3: {
                j->forca_chute = m->valor_atual;

                float forca = 6.0f + (j->forca_chute * 8.0f);

                j->bola.velocidade_x = (j->direcao_chute - 0.5f) * forca;
                j->bola.velocidade_y = -(3.0f + j->altura_chute * forca);
                j->bola.curva = (j->curva_chute - 0.5f) * 0.12f;

                j->bola.potencia = forca;
                j->bola.em_movimento = true;

                m->ativo = false;
                break;
            }
        }

        j->etapa_chute++;
        m->valor_atual = 0.5f;
    }
}