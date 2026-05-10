SRC = src/audio.c src/barreira.c src/dados.c src/fisica.c src/game.c src/goleiro.c src/input.c src/main.c src/placar.c src/render.c src/medidor.c src/gol.c src/desenho.c src/torcida.c src/sprites.c

all: # Compila todos os arquivos e gera o executável `stan-james`
	cc $(SRC) -Iinclude $(shell pkg-config --libs --cflags raylib) -o build/stan-james

run: all # `all` garante que compile todos os arquivos e depois rodamos o jogo.
	./build/stan-james

clean: # Apagar arquivos de compilação.
	rm -f build/stan-james
