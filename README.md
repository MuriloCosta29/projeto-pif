# Stan James

Jogo de cobrança de faltas desenvolvido em **C** com **raylib** para a disciplina de **Programação Imperativa e Funcional**.

O jogador usa a barra de espaço para controlar medidores de **direção**, **altura**, **curva** e **força**. Depois do chute, o jogo calcula se o resultado foi **gol**, **defesa**, **barreira** ou **fora**.

## Integrantes

- Arthur Morais Barbosa de Almeida
- Carlos Murilo de Oliveira Costa Filho
- Danilo Araújo Duleba

## Tecnologias

- Linguagem C
- raylib
- Makefile

## Como compilar

É necessário ter a **raylib** instalada.

No macOS com Homebrew:

```bash
brew install raylib
```

No Linux Ubuntu, Debian ou derivados:

```bash
sudo apt update
sudo apt install build-essential cmake pkg-config libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Para compilar

`make`

## Como rodar

`make run` ou `./build/stan-james`

## Como jogar

`SPACE` no menu: inicia o jogo.  

`SPACE` durante a cobrança: trava cada medidor.  

Ordem dos medidores:  
direção  
altura  
curva  
força  

`SPACE` no Game Over: reinicia o jogo.

## Objetivo

Marcar a maior quantidade de gols possível.

Ao fazer gol, o jogador avança para a próxima cobrança. Ao errar, bater na barreira ou sofrer defesa, a sequência volta para o início.

## Resultados do chute

Gol  
Defesa  
Barreira  
Fora  

## Pontuação

Cada gol aumenta a pontuação.  
Ao final do jogo, a pontuação é salva em:  
`data/scores.txt`  
O jogo também carrega os melhores scores nesse arquivo.

## Estrutura do projeto

include/       **Headers**  
src/           **Código-fonte**  
assets/        **Sprites e sons**  
data/          **Arquivos de pontuação**  
build/         **Executável gerado pelo `make`**  
Makefile       **Compilação do projeto**  
README.md      **Documentação**  

## Funcionalidade de cada arquivo `.c`

`src/main.c:` loop principal do jogo.  
`src/game.c:` estados, níveis, pontuação e resultado.  
`src/input.c:` leitura do teclado.  
`src/fisica.c:` trajetória da bola.  
`src/gol.c:` matriz 3x3 do gol.  
`src/goleiro.c:` lógica e animação do goleiro.  
`src/barreira.c:` lista encadeada da barreira.  
`src/desenho.c:` renderização do jogo.  
`src/sprites.c:` carregamento de sprites.  
`src/audio.c:` sistema de áudio.  
`src/placar.c:` leitura e escrita de scores.  

## Limpeza

Para remover o executável:
`make clean`
