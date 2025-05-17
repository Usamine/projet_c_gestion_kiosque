#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "biblio__1.h"

void afficher_menu_user() {
    printf("\n--- WELCOME TO BENZIN STATION ---\n");
    printf("1. GERANT\n");
    printf("2. CAISSIER\n");
    printf("3. CLIENT\n");
    printf("0. Quitter\n");
    printf("PRECIZER VOTRE STATUT : ");
}
///////////////////////////////////////////////////////////
void afficher_menu_gerant() {
    printf("\n--- WELCOME TO BENZIN STATION ---\n");
    printf("1. AJOUTER UN CAISSIER\n");
    printf("2. AFFICHER CAISSIERS\n");
    printf("3. AJOUTER PRODUIT\n");
    printf("4. AFFICHER MENU PRODUIT\n");
    printf("0. Quitter\n");
    printf("PRECIZER VOTRE SERVICE SOUHAITE : ");
}
/////////////////////////////////////////////////////////////////
void afficher_menu_caissier() {
    printf("\n--- WELCOME TO BENZIN STATION ---\n");
    printf("1. PAIMENT LAVAGE\n");
    printf("2. PAIMENT CARBURANT\n");
    printf("3. PAIMENT PRODUIT\n");
    printf("4. AFFICHER COMMANDE\n");
    printf("5. AFFICHER TRANSACTION CARBURANT\n");
    printf("6. AFFICHER LAVAGE\n");
    printf("0. Quitter\n");
    printf("PRECIZER VOTRE SERVICE SOUHAITE : ");
}
/////////////////////////////////////////////////////////////////
void afficher_menu_client() {
    printf("\n--- WELCOME TO BENZIN STATION ---\n");
    printf("1. LAVAGE\n");
    printf("2. CARBURANT\n");
    printf("3. PRODUIT\n");
    printf("0. Quitter\n");
    printf("PRECIZER VOTRE SERVICE SOUHAITE : ");
}
//////////////////////////////////////////////////////////////////
void afficher_menu_lavage(){
    printf("\n---SERVICE LAVAGE---\n");
    printf("1. LAVAGE EXTERIEUR\n");
    printf("2. LAVAGE INTERIEUR\n");
    printf("3. LAVAGE COMPLET\n");
    printf("4. RECUPERATION DE VOITURE\n");
    printf("PRECISER VOTRE CHOIX : ");
}
///////////////////////////////////////////////////////////////////////
void afficher_menu_carburant(){
    printf("\n---SERVICE REMPLISSAGE CARBURANT---\n");
    printf("1. ESSENCE SANS PLOMB\n");
    printf("2. GASOIL50\n");
    printf("3. GASOIL\n");
    printf("4. GPL\n");
    printf("5. MAZOUT\n");
    printf("PRECISER VOTRE CHOIX : ");
}
///////////////////////////////////////////////////////////////////////////
void afficher_menu_produit(FILE* P_fichier) {
    Produit produit;
    if (P_fichier == NULL) {
        printf("Erreur d'ouverture du fichier produits.txt.\n");
        return;
    }

    printf("\n----- LISTE DES PRODUITS -----\n");
    printf("+-----------------+-------------------------+------------+-----------+\n");
    printf("| CODE_PRODUIT    | NOM                     | PRIX       | QUANTITE  |\n");
    printf("+-----------------+-------------------------+------------+-----------+\n");
    fseek(P_fichier, 0, SEEK_SET);
    while (fscanf(P_fichier, "%d %s %f %d", &produit.code_produit, produit.nom, &produit.prix, &produit.quantite) == 4) {
        printf("| %-15d | %-23s | %-10.2f | %-9d |\n",
               produit.code_produit, produit.nom, produit.prix, produit.quantite);
    }

    printf("+-----------------+-------------------------+------------+-----------+\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////
void creerFichierServices(FILE**fp,FILE**fi,FILE**fc,FILE **fcaiss,FILE **fcomm)
{
    *fp=fopen("lavages.txt","a+");
    if( !*fp) exit(-1);
    *fi=fopen("transactions.txt","a+");
    if ( !*fi) exit(-1);
    *fc = fopen("produits.txt", "a+");
    if(!*fc) exit(-1);
    *fcomm = fopen("commandes.txt", "a+");
    if(!*fcomm) exit(-1);
    *fcaiss = fopen("caissiers.txt", "a+");
    if(!*fcaiss) exit(-1);
}
