#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"

int main(void) {
    printf("\n╔════════════════════════════════════════════════════╗\n");
    printf("║  🌲 Promenons-nous dans les bois 🐺               ║\n");
    printf("║     Simulation de cartographie avec Mermaid        ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    // Initialisation
    srand((unsigned)time(NULL));

    // Charger la comptine (essayer plusieurs chemins)
    char rhyme[MAX_LINES][MAX_LINE_LENGTH];
    int rhymeCount = readLines("../cmake-build-debug/ressources/comptine.txt", rhyme);
    if (rhymeCount <= 0) {
        rhymeCount = readLines("comptine.txt", rhyme);
    }
    if (rhymeCount <= 0) {
        printf("❌ Erreur: Impossible de charger la comptine\n");
        printf("   Chemins testés: ../cmake-build-debug/ressources/comptine.txt, comptine.txt\n");
        return -1;
    }
    printf("✅ Comptine chargée (%d lignes)\n", rhymeCount);

    // Charger les vêtements
    char clothes[MAX_CLOTHES][MAX_LINE_LENGTH];
    int clothesCount = readLines("../cmake-build-debug/ressources/vetements.txt", clothes);
    if (clothesCount <= 0) {
        clothesCount = readLines("vetements.txt", clothes);
    }
    if (clothesCount <= 0) {
        printf("❌ Erreur: Impossible de charger les vêtements\n");
        printf("   Chemins testés: ../cmake-build-debug/ressources/vetements.txt, vetements.txt\n");
        return -1;
    }
    printf("✅ Vêtements chargés (%d items)\n", clothesCount);

    // Initialiser le jeu (essayer plusieurs chemins pour la forêt)
    Game *game = initGame("../cmake-build-debug/ressources/foret1.txt",
                          "../cmake-build-debug/ressources/comptine.txt",
                          "../cmake-build-debug/ressources/vetements.txt");
    if (!game) {
        // Essayer sans le dossier ressources/
        game = initGame("foret1.txt", "comptine.txt", "vetements.txt");
    }
    if (!game) {
        printf("❌ Erreur: Impossible d'initialiser le jeu\n");
        printf("   Chemins testés: ../ressources/foret1.txt, foret1.txt\n");
        return -1;
    }
    printf("✅ Jeu initialisé\n");
    printf("📍 Position initiale enfant: (%d, %d)\n",
           game->child.coords.x, game->child.coords.y);

    // Lancer la partie
    printf("\n📍 Début de la simulation...\n");
    int result = runGame(game, rhyme, rhymeCount, clothes, clothesCount);

    // Afficher les statistiques finales
    printGameState(game);

    // Exporter le graphe Mermaid
    printf("\n📊 Génération du graphe Mermaid...\n");
    if (exportGraphToMermaid(game->graph, "../cmake-build-debug/output/cartographie.mmd") == 0) {
        printf("✅ Fichier Mermaid généré: ../cmake-build-debug/output/cartographie.mmd\n");
    } else {
        printf("❌ Erreur lors de la génération du Mermaid\n");
    }

    // AJOUT: Exporter la carte de trajet
    printf("\n🗺️  Génération de la carte de trajet...\n");
    if (exportPathMap(game->pathMap, "../cmake-build-debug/output/trajet.txt") == 0) {
        printf("✅ Carte de trajet générée: ../cmake-build-debug/output/trajet.txt\n");
    } else {
        printf("❌ Erreur lors de la génération de la carte\n");
    }

    printGraphStats(game->graph);

    // Nettoyage
    freeGame(game);

    printf("\n╔════════════════════════════════════════════════════╗\n");
    if (result == 0) {
        printf("║  🎉 PARTIE RÉUSSIE !                              ║\n");
    } else {
        printf("║  💀 PARTIE PERDUE                                 ║\n");
    }
    printf("╚════════════════════════════════════════════════════╝\n\n");

    return result;
}