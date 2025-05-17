#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "biblio__1.h"

int main(){
    int choix_user,choix_client,chservice,choix_lavage,choix_carburant,num,rec;
    float argent,o;
    char matricule[10],name[10];
    FILE *L_fichier,*C_fichier,*P_fichier,*CAISS_fichier,*comm_fichier;
    do{
        creerFichierServices(&L_fichier,&C_fichier,&P_fichier,&CAISS_fichier,&comm_fichier);
        afficher_menu_user();
        scanf("%d",&choix_user);
        switch(choix_user){
            case 1:
                 if (verify_manager()==1) {
                    int chg;
                    afficher_menu_gerant();
                    scanf("%d",&chg);
                    switch(chg){
                    case 0:
                        printf("AU REVOIR !\n");
                        break;
                    case 1:
                        printf("DONNER LE NOMBRE DE CAISSIER A AJOUTER: ");
                        scanf("%d",&rec);
                        for(int i=0;i<rec;i++){
                        printf("CAISSIER %d\n",i+1)  ;
                        ajouter_caissier(CAISS_fichier);}
                        break;
                    case 2 :
                        afficher_caissier(CAISS_fichier);
                        break;
                    case 3:
                        printf("DONNER LE NOMBRE DES PRODUITS A AJOUTER: ");
                        scanf("%d",&rec);
                        for(int i=0;i<rec;i++){
                        printf("PRODUIT %d",i+1);
                        ajouterProduit(P_fichier);}
                        break;
                    case 4:
                        afficher_menu_produit(P_fichier);
                        break;
                    default :
                        printf("ERRREUR!\n");
                        break;
                    }}
                break;
            case 2:
                if(verify_caissier(CAISS_fichier)==1){
                afficher_menu_caissier();
                scanf("%d",&chservice);
                switch(chservice){
                case 0:
                    printf("Au REVOIR :) \n");
                    break;
                case 1:
                case 2:
                case 3:
                    printf("VEILLEZ INSERER LE MONTANT : ");
                    scanf("%f", &argent);
                    calcul(argent,chservice,L_fichier,C_fichier,comm_fichier);
                    break;
                case 4:
                    afficherCommandes(comm_fichier);
                    break;
                case 5:
                    afficher_transactions_carburant(C_fichier);
                    break;
                case 6:
                    afficher_lavages(L_fichier);
                    break;
                default :
                    printf("ERRREUR!\n");
                    break;}}
                break;
            case 3:
                afficher_menu_client();
                scanf("%d",&choix_client);
                switch(choix_client){
                case 1:
                    afficher_menu_lavage();
                    scanf("%d",&choix_lavage);
                    printf("DONNER LA MATRICULE DE VOTRE VEHICULE:");
                    scanf("%s",matricule);
                    if(choix_lavage==4){
                        rec=recuperer_vehicule(matricule,L_fichier);
                        switch(rec){
                        case 0:
                            printf("VEHICULE NON TROUVEE DANS LES ENREGISTREMENTS!\n ");
                            printf("PEUT ETRE QUE VOUS AVEZ MIS UNE MATRICULE FAUSSE\n");
                            break;
                        case 1:
                            printf("MERCI DE NOUS VISITER PLUS TARD\n");
                            break;
                        case 2:
                            printf("VOTRE VOITURE EST PRETE,VOUS POUVEZ LA RECUPERER :) \n");
                            break;
                        case 4:
                            printf("VOUS AVEZ DEJA RECUPERE VOTRE VOITURE !\n");
                            break;
                        default:
                            printf("ERREUR");
                            break;}
                    }
                    else{
                            ajouter_lavage(matricule,choix_lavage,L_fichier);
                            printf("MERCI DE PASSER A LA CAISSE!");}
                    break;
                case 2:
                    afficher_menu_carburant();
                    scanf("%d",&choix_carburant);
                    ajouter_transaction_carburant(choix_carburant,C_fichier);
                    break;
                case 3:
                    ajouterCommande(P_fichier,comm_fichier);
                    break;
                }
                break;
            case 0:
                printf("FERMETURE DE PROGRAMME. Au REVOIR :) \n");
                break;
            default:
                printf("CHOIX INVALIDE. MERCI de REFAIRE VOTRE CHOIX.\n");
    }
    fclose(L_fichier);fclose(C_fichier);fclose(P_fichier);fclose(CAISS_fichier);fclose(comm_fichier);
    }while(choix_user!=0);
    return 0;
}
