#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

// Fonction pour vider le buffer
void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Fonction pour inscrire une personne
void inscrirePersonne() {
    char nom[MAX_LEN], prenom[MAX_LEN], nationalite[MAX_LEN];
    int age;
    float revenu;
    int deja_possede_logement;

    printf("\n=== Nouvelle Inscription AADL ===\n");

    printf("Nom : ");
    scanf("%s", nom);

    printf("Prénom : ");
    scanf("%s", prenom);

    printf("Âge : ");
    scanf("%d", &age);

    printf("Nationalité : ");
    scanf("%s", nationalite);

    printf("Revenu mensuel (en DZD) : ");
    scanf("%f", &revenu);

    printf("Possédez-vous déjà un logement ? (1 = Oui, 0 = Non) : ");
    scanf("%d", &deja_possede_logement);

    // Vérification des conditions
    if (strcmp(nationalite, "algerienne") != 0 && strcmp(nationalite, "Algerienne") != 0) {
        printf("❌ Refusé : nationalité non valide.\n");
        return;
    }
    if (age < 18) {
        printf("❌ Refusé : âge insuffisant.\n");
        return;
    }
    if (revenu < 24000 || revenu > 108000) {
        printf("❌ Refusé : revenu non éligible.\n");
        return;
    }
    if (deja_possede_logement) {
        printf("❌ Refusé : logement déjà possédé.\n");
        return;
    }

    // Enregistrement dans le fichier
    FILE *fichier = fopen("inscriptions.txt", "a");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }

    fprintf(fichier, "%s,%s,%d,%s,%.2f\n", nom, prenom, age, nationalite, revenu);
    fclose(fichier);

    printf("✅ Inscription acceptée et enregistrée !\n");
}

// Fonction pour afficher les inscriptions enregistrées
void afficherInscriptions() {
    char ligne[256];
    FILE *fichier = fopen("inscriptions.txt", "r");

    if (fichier == NULL) {
        printf("Aucune inscription enregistrée.\n");
        return;
    }

    printf("\n=== Liste des Inscriptions AADL ===\n");
    while (fgets(ligne, sizeof(ligne), fichier)) {
        printf("%s", ligne);
    }
    fclose(fichier);
}

int main() {
    int choix;

    do {
        printf("\n===== Menu AADL =====\n");
        printf("1. Nouvelle inscription\n");
        printf("2. Afficher les inscriptions\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        viderBuffer(); // Nettoyer le buffer après scanf

        switch (choix) {
            case 1:
                inscrirePersonne();
                break;
            case 2:
                afficherInscriptions();
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 0);

    return 0;
}
