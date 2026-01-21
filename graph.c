#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

static int nextId = 1;

Graph* createGraph(void) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph) return NULL;

    graph->firstEdge = NULL;
    graph->firstVertex = NULL;
    graph->nodeCount = 0;
    graph->edgeCount = 0;
    return graph;
}

// Rechercher un sommet par coordonnée
static Vertex* findVertexByCoords(Graph *graph, Coords coords) {
    Vertex *current = graph->firstVertex;
    while (current != NULL) {
        if (current->coords.x == coords.x && 
            current->coords.y == coords.y) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Créer ou récupérer un sommet
static Vertex* getOrCreateVertex(Graph *graph, Coords coords) {
    // Chercher si existe déjà
    Vertex *existing = findVertexByCoords(graph, coords);
    if (existing != NULL) {
        return existing;
    }

    // Créer nouveau sommet
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    if (!vertex) return NULL;

    vertex->id = nextId++;
    vertex->coords = coords;
    
    // Ajouter en tête de liste
    vertex->next = graph->firstVertex;
    graph->firstVertex = vertex;
    graph->nodeCount++;

    return vertex;
}

int addEdge(Graph *graph, Coords from, Coords to) {
    if (!graph) return -1;

    // Créer/récupérer les sommets
    Vertex *fromV = getOrCreateVertex(graph, from);
    Vertex *toV = getOrCreateVertex(graph, to);

    if (!fromV || !toV) return -1;

    // Créer l'arête
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    if (!edge) return -1;

    edge->from = fromV;
    edge->to = toV;

    // Ajouter à la liste
    GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
    if (!node) {
        free(edge);
        return -1;
    }

    node->edge = edge;
    node->nextNode = graph->firstEdge;
    graph->firstEdge = node;

    graph->edgeCount++;
    return 0;
}

int exportGraphToMermaid(const Graph *graph, const char *filename) {
    if (!graph || !filename) return -1;

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur ouverture fichier Mermaid");
        return -1;
    }

    fprintf(file, "graph TD\n");

    GraphNode *current = graph->firstEdge;
    while (current != NULL) {
        if (current->edge && current->edge->from && current->edge->to) {
            fprintf(file, "    %d(%d,%d) --> %d(%d,%d)\n",
                    current->edge->from->id,
                    current->edge->from->coords.x,
                    current->edge->from->coords.y,
                    current->edge->to->id,
                    current->edge->to->coords.x,
                    current->edge->to->coords.y);
        }
        current = current->nextNode;
    }

    fclose(file);
    printf("✅ Graphe exporté vers %s\n", filename);
    return 0;
}

void freeGraph(Graph *graph) {
    if (!graph) return;

    // Libérer les arêtes
    GraphNode *currentEdge = graph->firstEdge;
    while (currentEdge != NULL) {
        GraphNode *nextEdge = currentEdge->nextNode;
        if (currentEdge->edge) {
            free(currentEdge->edge);
        }
        free(currentEdge);
        currentEdge = nextEdge;
    }

    // Libérer les sommets
    Vertex *currentVertex = graph->firstVertex;
    while (currentVertex != NULL) {
        Vertex *nextVertex = currentVertex->next;
        free(currentVertex);
        currentVertex = nextVertex;
    }

    free(graph);
}

void printGraphStats(const Graph *g) {
    if (!g) return;
    printf("\n=== STATISTIQUES GRAPHE ===\n");
    printf("Nombre de sommets: %d\n", g->nodeCount);
    printf("Nombre d'arêtes: %d\n", g->edgeCount);
    printf("============================\n\n");
}