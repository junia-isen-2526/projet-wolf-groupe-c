#include <time.h>
#include <stdlib.h>
#include "wolf.h"
#include "child.h"

/*
 * TODO :
 * -structure de données pour la carte enregistré sur le disque (PC) et sur la mémoire (du programme)
 * -creer la structure Child
 *
*/

int main() {
	srand(time(NULL));

	char rhyme[MAXLines][MAX_LINE_LENGTH];
	const int rhymeCount = readLines("../ressources/comptine.txt", rhyme);

	char clothes[MAXClothes][MAX_LINE_LENGTH];
	const int clothesCount = readLines("../ressources/vetements.txt", clothes);

	Wolf wolf = {-1, -1, 0};
	Child child;

	GameStep step = STEP_COMPTINE;

	while (!isGameOver(step, child, &wolf)) {
		switch (step) {
			case STEP_COMPTINE: if (playComptineStep(rhyme, rhymeCount)) step = STEP_DRESSING;
				break;
			case STEP_DRESSING:
				if (wolfDressingStep(&wolf, clothes, clothesCount)) {
					step = STEP_WOLF_MOVE;
				} else {
					step = STEP_COMPTINE;
				}
				break;
			case STEP_WOLF_MOVE: moveWolfStep(&wolf);
				break;
		}
		moveChildStep(&child);
	}

	return 0;
}
