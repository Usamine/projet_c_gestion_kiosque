#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "biblio__1.h"


void ajouterProduit(FILE* P_fichier) {
    if ( P_fichier == NULL) {
        printf("Erreur d'ouverture du fichier produits.txt.\n");
        return;
    }
    Produit nouveau_produit;
    printf("ENTRER LE CODE DU PRODUIT : ");
    scanf("%d", &nouveau_produit.code_produit);
    printf("ENTRER LE NOM DU PRODUIT  : ");
    getchar();
    fgets(nouveau_produit.nom, sizeof(nouveau_produit.nom), stdin);
    nouveau_produit.nom[strcspn(nouveau_produit.nom, "\n")] = '\0';
    printf("ENTRER LE PRIX DU PRODUIT : ");
    scanf("%f", &nouveau_produit.prix);
    printf("ENTRER LA QUANTITÉ DU PRODUIT : ");
    scanf("%d", &nouveau_produit.quantite);
    fprintf(P_fichier, "%d %s %.2f %d\n",
            nouveau_produit.code_produit, nouveau_produit.nom,
            nouveau_produit.prix, nouveau_produit.quantite);
    printf("PRODUIT AJOUTÉ AVEC SUCCÈS.\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mettreAJourQuantite(int code_produit, int quantite_achetee,FILE*P_fichier) {
    Produit produit;
    if (P_fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier produits.txt.\n");
        return;
    }
    FILE *temp = fopen("temp_produits.txt", "a+");
    if (temp == NULL) {
        printf("Erreur : Impossible de créer un fichier temporaire.\n");
        return;
    }
    while (fscanf(P_fichier, "%d %49s %f %d",
        &produit.code_produit,
        produit.nom,
        &produit.prix,
        &produit.quantite) != EOF) {
        if (produit.code_produit == code_produit) {
            produit.quantite -= quantite_achetee;
        }
        fprintf(temp, "%d %s %.2f %d\n",
            produit.code_produit,
            produit.nom,
            produit.prix,
            produit.quantite);
    }
    P_fichier=temp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ajouterCommande(FILE* P_fichier,FILE* comm_fichier) {
    if (P_fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier produits.txt.\n");
        return;
    }
    afficher_menu_produit(P_fichier);
    Commande commande;
    Produit produit;
    if (comm_fichier == NULL) {
        printf("Erreur d'ouverture du fichier commandes.txt.\n");
        return;
    }
    srand(time(NULL));
    commande.numero_commande = rand();
    printf("LE NUMERO DE VOTRE COMMANDE EST %d , MERCI DE LE MEMORISER POUR PAYER :) \n", commande.numero_commande);
    commande.prix_total = 0;
    printf("DONNER LE CODE DE PRODUIT QUE VOUS VOULEZ ACHETER: ");
    scanf("%d", &commande.code_produit);
    int trouve = 0;
    fseek(P_fichier, 0, SEEK_SET);
    while (fscanf(P_fichier, "%d %s %f %d", &produit.code_produit, produit.nom, &produit.prix, &produit.quantite) != EOF) {
        if (produit.code_produit == commande.code_produit) {
            trouve = 1;
            break;
        }
    }
    if (!trouve) {
        printf("PRODUIT INEXISTANT X| \n");
        return;
    }
    strcpy(commande.nom, produit.nom);
    commande.prix_unite = produit.prix;
    printf("COMBIEN DE PIECES VOULEZ-VOUS ACHETER : ");
    scanf("%d", &commande.quantite);
    if (commande.quantite > produit.quantite) {
        printf("EPUISEMENT DE STOCK X| \n");
        return;
    }
    commande.prix_total += commande.prix_unite * commande.quantite;
    printf("Ecriture de la commande dans le fichier...\n");
    fprintf(comm_fichier, "%d %d %s %.3f %d %.3f\n",
            commande.numero_commande,
            commande.code_produit,
            commande.nom,
            commande.prix_unite,
            commande.quantite,
            commande.prix_total);
    mettreAJourQuantite(commande.code_produit,commande.quantite,P_fichier);
    printf("COMMANDE AJOUTEE AVEC SUCCES !\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficherCommandes(FILE*comm_fichier) {
    Commande commande;
    if (comm_fichier == NULL) {
        printf("Erreur d'ouverture du fichier commandes.txt.\n");
        return;
    }
    printf("\n---- Liste des commandes ----\n");
    printf("+-------------+---------------+---------------------+-----------+-------------+---------------+\n");
    printf("| NUMERO CMD  | CODE PRODUIT  | NOM PRODUIT         | PRIX UNIT | QUANTITE    | PRIX TOTAL    |\n");
    printf("+-------------+---------------+---------------------+-----------+-------------+---------------+\n");
    rewind(comm_fichier);
    int lignes_affichees = 0;
    while (fscanf(comm_fichier, "%d %d %49s %f %d %f",
        &commande.numero_commande,
        &commande.code_produit,
        commande.nom,
        &commande.prix_unite,
        &commande.quantite,
        &commande.prix_total) == 6) {
        printf("| %-11d | %-13d | %-19s | %9.2f | %11d | %13.2f |\n",
            commande.numero_commande,
            commande.code_produit,
            commande.nom,
            commande.prix_unite,
            commande.quantite,
            commande.prix_total);
        lignes_affichees++;
    }
    printf("+-------------+---------------+---------------------+-----------+-------------+---------------+\n");
    if (lignes_affichees == 0) {
        printf("Aucune commande trouvée.\n");
    } else {
        printf("Total des commandes : %d\n", lignes_affichees);
    }
}
