#include "child.h"


void isSafe(Child child) {
    if (child.coords.y == 0 || child.coords.y == FOREST_HEIGHT || child.coords.x == 0 || child.coords.x ==
        FOREST_WIDTH) {
        child.isSafe = 1;
    } else {
        child.isSafe = 0;
    }
}

int isGameOver(const GameStep step, Child child, const Wolf *wolf) {
    // TODO
    return step == STEP_WOLF_MOVE;
}

void moveChildStep(Child *child, const Forest forest) {
    if (child == NULL || forest == NULL) return;
    for (unsigned char i = 0; i < 9; i++) {
        srand(time(NULL));
        signed char new_x = rand() % 3;
        signed char new_y = rand() % 3;
        if (new_x == 2) new_x = -1;
        if (new_y == 2) new_x = -1;
        if (!forest[child->coords.x + new_y][child->coords.y + new_x]) {
            //TODO : ajouter le déplacement au graph avec les coords(child->coords.x,child->coords.y) et les coords(child->coords.x+new_y,child->coords.y+new_x)
            child->coords.x += new_x;
            child->coords.y += new_y;
            break;
        }
    }
}

void initChild(Child *child, unsigned char start_y, unsigned char start_x) {
    Coords coords = createCoords(start_x, start_y);
    child->coords = coords;
    child->isDead = 0;
    isSafe(*child);
}
