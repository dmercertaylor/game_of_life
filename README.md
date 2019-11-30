# game_of_life

A simple implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), written in C using ncurses. To compile, just run `cc -o life game_of_life.c -lncurses`, provided you have the library. The game will start of with a board of randomly filled cells, and advance one generation on a keypress. Hitting 'R' will instantly generate a new, randomly filled board, and 'Q' will quit. The program takes two arguments: the board width and height. For example, `./life 24 24` will make a 24 x 24 board. If only one argument is specified, it will be used for both width and height. If no arguments are provided, the board will default to 24 x 79.
