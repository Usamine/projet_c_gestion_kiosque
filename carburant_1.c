#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "biblio__1.h"

void ajouter_transaction_carburant(int choix_carburant,FILE*C_fichier) {
    if (C_fichier == NULL) {
        printf("Erreur d'ouverture du fichier transactions.txt.\n");
        return;
    }
    Carburant nouvelle_transaction;
    srand(time(NULL));
    nouvelle_transaction.id_transaction= rand();
    printf("VOICI L ID DE VOTRE TRANSACTION %d. MERCI DE LA MEMORISER POUR LE PAIMENT\n.",nouvelle_transaction.id_transaction);
    printf("DONNER VOTRE QUANTITEE: ");
    scanf("%f",&nouvelle_transaction.quantite);
    switch(choix_carburant) {
        case 1: nouvelle_transaction.prix_litre = 2.350;strcpy(nouvelle_transaction.type,"EssenceSansPlomb") ; break;
        case 2: nouvelle_transaction.prix_litre = 2.220;strcpy(nouvelle_transaction.type,"Gazoil50"); break;
        case 3: nouvelle_transaction.prix_litre = 1.950;strcpy(nouvelle_transaction.type,"Gazoil") ; break;
        case 4: nouvelle_transaction.prix_litre = 0.870;strcpy(nouvelle_transaction.type ,"GPL"); break;
        case 5: nouvelle_transaction.prix_litre = 1.950;strcpy(nouvelle_transaction.type ,"Mazout") ; break;
    }
    nouvelle_transaction.montant_total = nouvelle_transaction.quantite * nouvelle_transaction.prix_litre;
    fprintf(C_fichier, "%d %s %f %f %f\n",
               nouvelle_transaction.id_transaction, nouvelle_transaction.type,
               nouvelle_transaction.quantite, nouvelle_transaction.prix_litre,
               nouvelle_transaction.montant_total);
    printf("TRANSACTION AJOUTÉ AVEC SUCCÈS.\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void afficher_transactions_carburant(FILE* C_fichier) {
    Carburant carburant;
    if (C_fichier == NULL) {
        printf("Erreur d'ouverture du fichier transactions.txt.\n");
        return;
    }
    printf("\n----- LISTE DES TRANSACTIONS DE CARBURANT -----\n");
    printf("+-----------------+-------------------------+-----------+------------+----------------+\n");
    printf("| ID_TRANSACTION  | TYPE                   | QUANTITE  | PRIX/LITRE | MONTANT TOTAL  |\n");
    printf("+-----------------+-------------------------+-----------+------------+----------------+\n");
    fseek(C_fichier, 0, SEEK_SET);
    while (fscanf(C_fichier, "%d %s %f %f %f",
                  &carburant.id_transaction, carburant.type,
                  &carburant.quantite, &carburant.prix_litre,
                  &carburant.montant_total) != EOF) {
        printf("| %-15d | %-23s | %-9.3f | %-10.3f | %-14.3f |\n",
               carburant.id_transaction, carburant.type,
               carburant.quantite, carburant.prix_litre,
               carburant.montant_total);
    }

    printf("+-----------------+-------------------------+-----------+------------+----------------+\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////


