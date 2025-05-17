#ifndef BIBLIO_H
#define BIBLIO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NOM 50
#define PASSWORD "1234"
//////////////////////////////////////////////////////////////
//STRUCTURES
typedef struct {
    int id_caissier;
    char nom[MAX_NOM];
} Caissier;
typedef struct {
    int code_produit;
    char nom[MAX_NOM];
    float prix;
    int quantite;
}Produit;

typedef struct {
    int numero_commande;
    int code_produit;
    char nom[MAX_NOM];
    float prix_unite;
    int quantite;
    float prix_total;
} Commande;
typedef struct {
    int id_lavage;
    char type[20];
    float prix;
    int statut;
    char immatriculation[20];
    int etat_recup;
    time_t datedeb;
    time_t datefin;
} Lavage;
typedef struct {
    int id_transaction;
    char type[MAX_NOM];
    float prix_litre;
    float quantite;
    float montant_total;
} Carburant;
////////////////////////////////////////////////////////////
//FRONT
void afficher_menu_user();
void afficher_menu_client();
void afficher_menu_gerant();
void afficher_menu_lavage();
void afficher_menu_carburant();
void afficher_menu_produit(FILE*);
void afficher_menu_caissier();
void creerFichierServices(FILE**fp,FILE**fi,FILE**fc,FILE**fcaiss,FILE**fcomm);
/////////////////////////////////////////////////////////////
//GERA
int verify_manager();
void ajouter_caissier(FILE*);
void afficher_caissier(FILE*);
///////////////////////////////////////////////////////////////
//CAISSIER
int verify_caissier(FILE*);
void traitement_paiment(float m,float argent);
void calacul(int service,FILE*,FILE*,FILE*);
//LAVAGE
////////////////////////////////////////////////////////////////
void ajouter_lavage(char ch[10],int x,FILE*);
void afficher_lavages(FILE*);
int recuperer_vehicule(char c[10],FILE*);
///////////////////////////////////////////////////////////////
//PRODUIT
void ajouterProduit(FILE*);
void ajouterCommande(FILE*,FILE*);
void afficherCommandes(FILE*);
void mettreAJourQuantite(int code_produit, int quantite_achetee,FILE*);
///////////////////////////////////////////////////////////////////////////////
//CARBURANT
void ajouter_transaction_carburant(int choix,FILE*);
void afficher_transactions_carburant(FILE*);

#endif
