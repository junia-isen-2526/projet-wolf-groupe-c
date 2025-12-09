#include <time.h>
#include <stdlib.h>
#include "wolf.h"
#include "child.h"
#include "forest.h"
#include "graph.h"

/*
 *globaux
 * TODO : structure de données pour la carte enregistré sur le disque (PC) et sur la mémoire (du programme)
 * TODO : Regarder le comportement du loup et l'adapter.
 *
 *à faire là
 * TODO : faire la structure Graph et edges
 * TODO : faire une fonction qui permet de save un graph en .mmd (mermaid)
 * TODO : faire une fonction qui permet de charger un graph depuis un .mmd (mermaid)
 *à faire plus tard
 * TODO : faire les fonctions de Map pour faire en sorte de pouvoir ajouter des points à la Map
 * TODO : faire les fonctions qui permettent de déplacer l'enfant
 * TODO : faire une fonction qui permet aux enfants de retrouver un chemin vers le bord en fonction de leur Map (avec l'aide du Mermaid ?)
*/

int main() {
	srand(time(NULL));

	char rhyme[MAXLines][MAX_LINE_LENGTH];
	const int rhymeCount = readLines("../ressources/comptine.txt", rhyme);

	char clothes[MAXClothes][MAX_LINE_LENGTH];
	const int clothesCount = readLines("../ressources/vetements.txt", clothes);


	// Création des sommets
	Vertex v1 = {1, &(Coords){0,0}};
	Vertex v2 = {2, &(Coords){1,0}};
	Vertex v3 = {3, &(Coords){1,1}};

	// Création des arêtes
	Edge* e1 = malloc(sizeof(Edge));
	e1->from = &v1;
	e1->to = &v2;

	Edge* e2 = malloc(sizeof(Edge));
	e2->from = &v2;
	e2->to = &v3;

	// Création des nœuds de la liste chaînée
	Node* n1 = malloc(sizeof(Node));
	n1->edge = e1;

	Node* n2 = malloc(sizeof(Node));
	n2->edge = e2;

	// Chaînage manuel
	n1->nextNode = n2;
	n2->nextNode = NULL;

	// Création du graphe
	Graph g;
	g.firstNode = n1;
	g.nodeCount = 2;

	// Export en Mermaid
	if (exportGraphToMermaid(&g, "../mmd/graph.mmd") == 0) {
		printf("Fichier Mermaid généré : graph.mmd\n");
	}

	// Libération mémoire
	free(e1);
	free(e2);
	free(n1);
	free(n2);

	Wolf wolf = {-1, -1, 0};
	Forest forest;
	Child child;
	initChild(&child,0,0);

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
		moveChildStep(&child,forest);
	}

	return 0;
}
