#include "sprites.h"

static Texture2D carregar_textura(const char *caminho) {
  Texture2D textura = LoadTexture(caminho);

  if (textura.id == 0) {
    TraceLog(LOG_WARNING, "Nao foi possivel carregar textura: %s", caminho);
  }

  return textura;
}

static void configurar_filtro(Texture2D textura) {
  if (textura.id != 0) {
    SetTextureFilter(textura, TEXTURE_FILTER_BILINEAR);
  }
}

void carregar_sprites(SpritesJogo *sprites) {
  sprites->cobrador = carregar_textura("assets/sprites/cobrador.png");
  sprites->goleiro = carregar_textura("assets/sprites/goleiro.png");
  sprites->barreira_a = carregar_textura("assets/sprites/barreira_a.png");
  sprites->barreira_b = carregar_textura("assets/sprites/barreira_b.png");
  sprites->gol = carregar_textura("assets/sprites/gol.png");
  sprites->arquibancada = carregar_textura("assets/sprites/arquibancada.png");

  configurar_filtro(sprites->cobrador);
  configurar_filtro(sprites->goleiro);
  configurar_filtro(sprites->barreira_a);
  configurar_filtro(sprites->barreira_b);
  configurar_filtro(sprites->gol);
  configurar_filtro(sprites->arquibancada);

  sprites->inicializado = true;
}

void liberar_sprites(SpritesJogo *sprites) {
  if (!sprites->inicializado) {
    return;
  }

  UnloadTexture(sprites->cobrador);
  UnloadTexture(sprites->goleiro);
  UnloadTexture(sprites->barreira_a);
  UnloadTexture(sprites->barreira_b);
  UnloadTexture(sprites->gol);
  UnloadTexture(sprites->arquibancada);

  sprites->inicializado = false;
}
