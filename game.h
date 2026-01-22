#ifndef WOLF_GAME_H
#define WOLF_GAME_H

#include "child.h"
#include "wolf.h"
#include "forest.h"
#include "graph.h"
#include "pathmap.h"

typedef enum {
    GAME_RUNNING,
    GAME_CHILD_SAFE,
    GAME_CHILD_EATEN
} GameState;

typedef struct {
    Child child;
    Wolf wolf;
    Forest forest;
    Graph *graph;
    PathMap pathMap;  // Carte de trajet
    GameStep step;
    GameState state;
    int stepCount;
} Game;

/* Init */
Game* initGame(const char *forestFile,
               const char *comptineFile,
               const char *clothesFile);

/* update étape */
GameState updateGame(Game *game,
                     char rhyme[MAX_LINES][MAX_LINE_LENGTH],
                     int rhymeCount,
                     char clothes[MAX_CLOTHES][MAX_LINE_LENGTH],
                     int clothesCount);

/* Boucle principale du jeu */
int runGame(Game *game,
            char rhyme[MAX_LINES][MAX_LINE_LENGTH],
            int rhymeCount,
            char clothes[MAX_CLOTHES][MAX_LINE_LENGTH],
            int clothesCount);

/* Afficher l'état du jeu */
void printGameState(const Game *game);

/* free */
void freeGame(Game *game);

#endif // WOLF_GAME_H