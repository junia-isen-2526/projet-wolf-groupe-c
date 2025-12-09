#include <time.h>
#include <stdlib.h>
#include "wolf.h"
#include "child.h"
#include "forest.h"

/*
 *globaux
 * TODO : structure de données pour la carte enregistré sur le disque (PC) et sur la mémoire (du programme)
 * TODO : Regarder le comportement du loup et l'adapter.
 *
 *à faire là
 * TODO : faire une fonction qui permet de générer un fichier en .mmd (mermaid) à partir de la structure de données Map (dans child.h)
 * TODO : faire une fonction qui permet de générer un fichier en .txt (texte) à partir de la structure de données Map (dans child.h) parce que pour que la partie se finisse et que les enfants gagnent il faut que tout les chemins soient découvert, donc la manière de faire cela envisagé ici c'est qu'on sait si on a trouvé tout les chemins si quand on additionne la Map avec la Foret on n'a que des 1 et aucun vide
 * TODO : faire les fonctions de Map pour faire en sorte de pouvoir ajouter des points à la Map
 * TODO : faire les fonctions qui permettent de déplacer l'enfant
 *
 *à faire plus tard
 * TODO : faire une fonction qui permet aux enfants de retrouver un chemin vers le bord en fonction de leur Map (avec l'aide du Mermaid ?)
*/

int main() {
	srand(time(NULL));

	char rhyme[MAXLines][MAX_LINE_LENGTH];
	const int rhymeCount = readLines("../ressources/comptine.txt", rhyme);

	char clothes[MAXClothes][MAX_LINE_LENGTH];
	const int clothesCount = readLines("../ressources/vetements.txt", clothes);

	Wolf wolf = {-1, -1, 0};
	Forest forest;
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
