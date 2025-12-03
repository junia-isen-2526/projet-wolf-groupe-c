#include "wolf.h"

int readLines(const char *filename, char lines[MAXLines][MAX_LINE_LENGTH]) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("Erreur ouverture fichier");
		return 0;
	}
	int count = 0;
	while (fgets(lines[count], MAX_LINE_LENGTH, file) && count < MAXLines) {
		lines[count][strcspn(lines[count], "\n")] = '\0';
		count++;
	}
	fclose(file);
	return count;
}

int playComptineStep(char rhyme[MAXLines][MAX_LINE_LENGTH], int rhymeCount) {
	static int currentLine = 0;
	if (currentLine < rhymeCount) {
		printf("%s\n", rhyme[currentLine]);
		currentLine++;
		return 0;
	} else {
		currentLine = 0;
		return 1;
	}
}

int wolfDressingStep(Wolf *wolf, const char clothes[MAXClothes][MAX_LINE_LENGTH], const int clothesCount) {
	static int currentCloth = 0;
	if ((currentCloth >= clothesCount) || ((currentCloth > 1) && (rand() % clothesCount == 0))) {
		printf("J'arrive !!!\n");
		return 1;
	} else {
		printf("Je mets %s !\n", clothes[currentCloth]);
		if (currentCloth == 0 && wolf->active == 0) {
			wolf->x = rand() % FOREST_WIDTH;
			wolf->y = rand() % FOREST_HEIGHT;
			wolf->active = 1;
		}
		currentCloth++;
		return 0;
	}
}

void moveWolfStep(Wolf *wolf) {
	if (wolf->active) {
		int dx = (rand() % 3) - 1;
		int dy = (rand() % 3) - 1;
		wolf->x += dx;
		wolf->y += dy;
		printf("Le loup se déplace en (%d, %d)\n", wolf->x, wolf->y);
	}
}
