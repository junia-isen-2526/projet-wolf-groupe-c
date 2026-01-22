#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Game* initGame(const char *forestFile,
               const char *comptineFile,
               const char *clothesFile) {
    Game *game = (Game *)malloc(sizeof(Game));
    if (!game) return NULL;

    // Charger la forêt
    if (loadForest(game->forest, forestFile) < 0) {
        free(game);
        return NULL;
    }

    // Initialiser l'enfant au centre
    Coords startPos = findRandomEdgePosition(game->forest);
    initChild(&game->child, startPos);

    // Initialiser le loup
    game->wolf.x = -1;
    game->wolf.y = -1;
    game->wolf.active = 0;

    // Créer graphe
    game->graph = createGraph();
    if (!game->graph) {
        free(game);
        return NULL;
    }

    // Initialiser la carte de trajet
    initPathMap(game->pathMap);

    markVisited(game->pathMap, startPos);

    // État initial
    game->step = STEP_COMPTINE;
    game->state = GAME_RUNNING;
    game->stepCount = 0;


    return game;
}

GameState updateGame(Game *game,
                     char rhyme[MAX_LINES][MAX_LINE_LENGTH],
                     int rhymeCount,
                     char clothes[MAX_CLOTHES][MAX_LINE_LENGTH],
                     int clothesCount) {
    if (!game) return GAME_CHILD_EATEN;

    printf("\n--- ÉTAPE %d ---\n", game->stepCount++);

    // Étape 1 : Comptine/Habillage/Déplacement loup
    switch (game->step) {
        case STEP_COMPTINE:
            if (playComptineStep(rhyme, rhymeCount)) {
                game->step = STEP_DRESSING;
            }
            break;

        case STEP_DRESSING:
            if (wolfDressingStep(&game->wolf, clothes, clothesCount)) {
                game->step = STEP_WOLF_MOVE;
            } else {
                game->step = STEP_COMPTINE;
            }
            break;

        case STEP_WOLF_MOVE:
            if (game->wolf.active) {
                moveWolfStep(&game->wolf);
            }
            break;
    }

    // Étape 2 : Déplacement enfant
    int childResult = moveChildStep(&game->child, game->forest, game->graph);

    //nouvelle position dans la carte de trajet
    if (childResult >= 0) {
        markVisited(game->pathMap, game->child.coords);
    }

    // Étape 3 : Vérif fin
    if (childResult == 1 || game->child.isSafe) {
        printf("\n VICTOIRE ! L'enfant est en sécurité !\n");
        return GAME_CHILD_SAFE;
    }

    if (isChildEaten(&game->child, game->wolf.x, game->wolf.y)) {
        printf("\n DÉFAITE ! L'enfant a été mangé !\n");
        return GAME_CHILD_EATEN;
    }

    return GAME_RUNNING;
}

int runGame(Game *game,
            char rhyme[MAX_LINES][MAX_LINE_LENGTH],
            int rhymeCount,
            char clothes[MAX_CLOTHES][MAX_LINE_LENGTH],
            int clothesCount) {
    if (!game) return -1;

    while (game->state == GAME_RUNNING && game->stepCount < 1000) {
        game->state = updateGame(game, rhyme, rhymeCount,
                                 clothes, clothesCount);
    }

    return (game->state == GAME_CHILD_SAFE) ? 0 : -1;
}

void printGameState(const Game *game) {
    if (!game) return;
    printf("\n=== ÉTAT DU JEU ===\n");
    printf("Enfant: (%d, %d) [Safe: %d]\n",
           game->child.coords.x, game->child.coords.y, game->child.isSafe);
    printf("Loup: (%d, %d) [Actif: %d]\n",
           game->wolf.x, game->wolf.y, game->wolf.active);
    printf("Étapes: %d\n", game->stepCount);
    printf("Arêtes cartographiées: %d\n", game->graph->edgeCount);
    printf("===================\n\n");
}

void freeGame(Game *game) {
    if (!game) return;
    if (game->graph) freeGraph(game->graph);
    free(game);
}