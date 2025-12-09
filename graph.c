//
// Created by Thanh on 09/12/2025.
//
#include <stdio.h>
#include "graph.h"

int getNextId() {
    static int id = 0;
    return ++id;
}
int exportGraphToMermaid(const Graph* g, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier Mermaid");
        return -1;
    }

    fprintf(file, "graph TD\n");

    Node* current = g->firstNode;
    while (current != NULL) {
        Edge* e = current->edge;
        if (e != NULL && e->from != NULL && e->to != NULL) {
            // On écrit l'id + les coordonnées si elles existent
            if (e->from->coord != NULL && e->to->coord != NULL) {
                fprintf(file, "    %d(%d,%d) --> %d(%d,%d)\n",
                    e->from->id, e->from->coord->x, e->from->coord->y,
                    e->to->id, e->to->coord->x, e->to->coord->y);
            } else {
                // sinon juste l'id
                fprintf(file, "    %d --> %d\n", e->from->id, e->to->id);
            }
        }
        current = current->nextNode;
    }

    fclose(file);
    return 0;
}


