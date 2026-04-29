SRC = src/barreira.c src/dados.c src/fisica.c src/game.c src/goleiro.c src/input.c src/main.c src/placar.c src/render.c

all: # Vai rodar todos files do projeto! Por enquanto só está rodando o main.c, por teste.
	cc $(SRC) $(shell pkg-config --libs --cflags raylib) -o build/stan-james

run: all
	./build/stan-james

clean: # Apagar arquivos de compilação.
	rm -f build/stan-james
