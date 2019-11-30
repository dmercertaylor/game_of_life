#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <ncurses.h>

void game_of_life(char ** input, char ** output);
int get_neighbors(char ** arr, int i, int j);
bool is_number(char *str);

int GAME_HEIGHT = 24;
int GAME_WIDTH = 79;

const char ON = '0';
const char OFF = ' ';

int main(int argc, char *argv[]){

    if(argc > 1){
        if( !is_number(argv[1]) || (GAME_WIDTH = atoi(argv[1])) == 0){
            printf("Usage: life [screen width] [screen height]\n");
            return 1;
        }
	GAME_HEIGHT = GAME_WIDTH;
        if(argc > 2){
            if( !is_number(argv[2]) || (GAME_HEIGHT = atoi(argv[2])) == 0){
                printf("Usage: life [screen width] [screen height]\n");
                return 2;
            }
        }
        if(GAME_WIDTH < 0) GAME_WIDTH *= -1;
        if(GAME_HEIGHT < 0) GAME_HEIGHT *= -1;
    }  
  
    WINDOW *window;

    initscr();
    noecho();
    cbreak();

    window = newwin(GAME_HEIGHT, GAME_WIDTH, (LINES - GAME_HEIGHT) / 2, (COLS-GAME_WIDTH) / 2);

    char ** world = malloc(sizeof(char *) * GAME_HEIGHT);
    char ** next_gen = malloc(sizeof(char *) * GAME_HEIGHT);
    srand((unsigned) time(NULL));

    RESTART: // goes here if user presses R;
    for(int i=0; i<GAME_HEIGHT; i++){
        int j=0;
        world[i] = malloc(sizeof(char) * GAME_WIDTH + 1);
        next_gen[i] = malloc(sizeof(char) * GAME_WIDTH + 1);
        for(; j<GAME_WIDTH; j++){
            world[i][j] = (rand() % 4) ? OFF : ON;
        }
        world[i][j] = '\0';
        printw("%s\n", world[i]);
    }

    char c;
    while((c = getch())){
        clear();
        game_of_life(world, next_gen);
        char **tmp = world;
        world = next_gen;
        next_gen = tmp;
        for(int i=0; i<GAME_HEIGHT; i++){
            printw("%s\n", world[i]);
        }
        refresh();
        if(c == 'R'){
            clear();
            for(int i=0; i<GAME_HEIGHT; i++){
                free(world[i]);
                free(next_gen[i]);
            }
            goto RESTART; // Naughty, naughty goto
        }
        else if(c == 'Q' || c == 'Z' || c == 'z') break;
    }

    for(int i=0; i<GAME_HEIGHT; i++){
        free(world[i]);
        free(next_gen[i]);
    }
    free(world);
    free(next_gen);

    delwin(window);
    endwin();
    return 0;
}

void game_of_life(char ** input, char ** output){
    for(int i=0; i < GAME_HEIGHT; i++){
        for(int j=0; input[i][j] != '\0'; j++){
            int neighbors = get_neighbors(input, i, j);
            char tmp = OFF;
            if(input[i][j] == ON && (neighbors == 2 || neighbors == 3)){
                tmp = ON;
            } else if(input[i][j] == OFF && neighbors == 3){
                tmp = ON;
            }
            output[i][j] = tmp;
        }
    }
}

int get_neighbors(char ** arr, int i, int j){
    int output = (arr[i][j] == ON) ? -1 : 0;
    int yMin = (i > 0) ? i - 1 : i;
    int xMin = (j > 0) ? j - 1 : j;
    int yMax = (i < GAME_HEIGHT - 1) ? i + 1 : i;
    int xMax = (j < GAME_WIDTH - 1) ? j + 1 : j;
    for(int y = yMin; y <= yMax; y++){
        for(int x = xMin; x <= xMax; x++){
            if(arr[y][x] == ON) output++;
        }
    }
    return output;
}

bool is_number(char * str){
    for(char *c = str; *c!='\0'; c++){
        if(*c < '0' || *c > '9'){
            if(*c != '-') return false;
        }
    }
    return true;
}
