#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "biblio__1.h"

int verify_manager() {
    char input_password[20];
    char input_id[20];
    printf("IDENTIFIANT DU GERANT : ");
    scanf("%s", input_id);
    printf("MOT DE PASSE : ");
    scanf("%s", input_password);
    if (strcmp(input_id, "ADMIN") == 0 && strcmp(input_password, "PASSWORD") == 0) {
        return 1;
    } else {
        printf("ERREUR : IDENTIFIANT OU MOT de PASSE INCORRECTE.\n");
        return 0;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
void ajouter_caissier(FILE* CAISS_fichier) {
    if (CAISS_fichier == NULL) {
        printf("Erreur d'ouverture du fichier caissiers.txt.\n");
        return;
    }
    Caissier nouveau_caissier;
    printf("ENTRER L IDENTIFIANT DU CAISSIER : ");
    scanf("%d", &nouveau_caissier.id_caissier);
    printf("ENTRER LE NOM DU CAISSIER : ");
    getchar();
    fgets(nouveau_caissier.nom, sizeof(nouveau_caissier.nom), stdin);
    nouveau_caissier.nom[strcspn(nouveau_caissier.nom, "\n")] = '\0'; // La fonction strcspn trouve la position du caractère de nouvelle ligne dans la chaîne et le remplace par le caractère de fin de chaîne (\0).
    fprintf(CAISS_fichier, "%d %s\n", nouveau_caissier.id_caissier, nouveau_caissier.nom);
    printf("CAISSIER AJOUTEE AVEC SUCCEES.\n");
}
////////////////////////////////////////////////////////////////////////////////////
void afficher_caissier(FILE* CAISS_fichier){
    Caissier caissier ;
    if (CAISS_fichier == NULL) {
        printf("Erreur d'ouverture du fichier caissiers.txt.\n");
        return;
    }
    printf("\n-----LISTE DES CAISSIERS-----\n");
    printf("+-----------------+-------------------------+\n");
    printf("| %-15s | %-23s |\n", "ID_CAISSIER", "NOM");
    printf("+-----------------+-------------------------+\n");
    fseek(CAISS_fichier, 0, SEEK_SET);
    while (fscanf(CAISS_fichier, "%d %s",&caissier.id_caissier, caissier.nom) != EOF) {
        printf("| %-15d | %-23s |\n", caissier.id_caissier, caissier.nom);
    }
    printf("+-----------------+-------------------------+\n"); }
