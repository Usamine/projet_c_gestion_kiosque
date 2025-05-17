#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "biblio__1.h"

///////////////////////////////////////////////
void ajouter_lavage(char matricule[10],int choix_lavage,FILE*L_fichier) {
    if (L_fichier == NULL) {
        printf("Erreur d'ouverture du fichier lavages.txt.\n");
        return;
    }
    Lavage nouveau_lavage;
    srand(time(NULL));
    nouveau_lavage.id_lavage= rand();
    printf("L ID DE VOTRE LAVAGE EST %d. MERCI DE LE MEMORISER POUR PAYER.\n",nouveau_lavage.id_lavage);
    nouveau_lavage.statut = 0;
    nouveau_lavage.etat_recup = 0;
    strcpy(nouveau_lavage.immatriculation, matricule);
    nouveau_lavage.datedeb = time(NULL);
    nouveau_lavage.datefin = nouveau_lavage.datedeb + 3600;
    switch (choix_lavage) {
        case 1:
            nouveau_lavage.prix = 15.000;
            strcpy(nouveau_lavage.type, "LAVAGEINTERNE");
            break;
        case 2:
            nouveau_lavage.prix = 25.000;
            strcpy(nouveau_lavage.type, "LAVAGEXTERNE");
            break;
        case 3:
            nouveau_lavage.prix = 35.000;
            strcpy(nouveau_lavage.type, "LAVAGECOMPLET");
            break;
        default:
            printf("ERREUR : TYPE INVALIDE.\n");
            return 0;
    }
    fprintf(L_fichier, "%d %s %f %s %d %d %ld %ld\n",
    nouveau_lavage.id_lavage,
    nouveau_lavage.type,
    nouveau_lavage.prix,
    nouveau_lavage.immatriculation,
    nouveau_lavage.statut,
    nouveau_lavage.etat_recup,
    nouveau_lavage.datedeb,
    nouveau_lavage.datefin);
    printf("LAVAGE AJOUTEE AVEC SUCCEES.\n");
}


/////////////////////////////////////////////////////////////////
int recuperer_vehicule(char matricule[10], FILE* L_fichier) {
    if (L_fichier == NULL) {
        printf("Erreur d'ouverture du fichier lavages.txt.\n");
        return 0;
    }
    Lavage lavage;
    int trouve = 0;
    FILE *temp_fichier = fopen("temp.txt", "w+");
    if (temp_fichier == NULL) {
        printf("Erreur d'ouverture du fichier temporaire.\n");
        return 0;
    }
    fseek(L_fichier, 0, SEEK_SET);
    while (fscanf(L_fichier, "%d %s %f %s %d %d %ld %ld",
                  &lavage.id_lavage, lavage.type, &lavage.prix, lavage.immatriculation,
                  &lavage.statut, &lavage.etat_recup, &lavage.datedeb, &lavage.datefin) != EOF) {
        if (strcmp(lavage.immatriculation, matricule) == 0) {
            trouve = 1;
            if (lavage.etat_recup == 1) {
                fclose(temp_fichier);
                return 4;
            } else if (lavage.datefin > time(NULL)) {
                printf("VOUS ALLEZ ATTENDRE ENCORE %ld SECONDES\n", lavage.datefin - time(NULL));
                fclose(temp_fichier);
                return 1;
            } else {
                lavage.etat_recup = 1;
                lavage.statut = 1;
            }
        }
        fprintf(temp_fichier, "%d %s %.2f %s %d %d %ld %ld\n",
                lavage.id_lavage, lavage.type, lavage.prix, lavage.immatriculation,
                lavage.statut, lavage.etat_recup, lavage.datedeb, lavage.datefin);
    }
    if (!trouve) {
        return 0;
    }
    L_fichier=temp_fichier;
    return 2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_lavages(FILE* L_fichier) {
    Lavage nouveau_lavage;
    if (L_fichier == NULL) {
        printf("Erreur d'ouverture du fichier lavages.txt.\n");
        return;
    }
    printf("\n----- LISTE DES LAVAGES -----\n");
    printf("+------------+----------------------+--------+--------------------+--------+------------+------------+------------+\n");
    printf("| ID_LAVAGE  | TYPE                 | PRIX   | MATRICULE          | STATUT | ETAT_RECUP | DATE_DEB   | DATE_FIN   |\n");
    printf("+------------+----------------------+--------+--------------------+--------+------------+------------+------------+\n");
    fseek(L_fichier, 0, SEEK_SET);
    while (fscanf(L_fichier, "%d %s %f %s %d %d %ld %ld",
                  &nouveau_lavage.id_lavage,
                  nouveau_lavage.type,
                  &nouveau_lavage.prix,
                  nouveau_lavage.immatriculation,
                  &nouveau_lavage.statut,
                  &nouveau_lavage.etat_recup,
                  &nouveau_lavage.datedeb,
                  &nouveau_lavage.datefin) != EOF) {
        printf("| %-10d | %-20s | %-6.2f | %-18s | %-6d | %-10d | %-10ld | %-10ld |\n",
               nouveau_lavage.id_lavage,
               nouveau_lavage.type,
               nouveau_lavage.prix,
               nouveau_lavage.immatriculation,
               nouveau_lavage.statut,
               nouveau_lavage.etat_recup,
               nouveau_lavage.datedeb,
               nouveau_lavage.datefin);
    }
    printf("+------------+----------------------+--------+--------------------+--------+------------+------------+------------+\n");
}
