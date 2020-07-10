#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"






int main()

{     int i,cpt=0,choix=0;
      long cle;
      int choi;
      char *region_nouv;
      char regio[25], bloc[200], nom[31],prenom[31], gs[4], gr[25], fa[50], annee[5], mois[11],jour[3], city[25];
      char region[25], categorie[30];
      index_primaire table[10000];
      index_primaire rr[1000];
      index_annee year[100];
      index_secondaire reg[20];
      index_secondaire tab_sec[20];
      index_secondaire GR[20];
      Maillon *tete=NULL;
      srand(time(NULL));
     long n,taille,mat;
     int age_p,age_g;

while (choix!=10)
{
    menu();
    scanf("%d",&choix);
    switch (choix)
{
case(1):
      system("cls");
      printf("creation du fichier \n");
      printf("veuillez inroduire le nombre des enregistrements : \n");
       scanf("%lu",&n);
      chargement_initial(n);
      indexer_cle(table,"PERSONNEL-ANP_DZ.bin");
      indexer_annee("PERSONNEL-ANP_DZ.bin",year,table);
      indexer_region("PERSONNEL-ANP_DZ.bin",reg,table);
      system("cls");
      printf("le fichier a ete cree avec succes !\n");
      system("pause");
      break;
case (2):
      system ("cls");
      printf("epuration du fichier \n");
      epuration("PERSONNEL-ANP_DZ.bin",table,&n);
      printf("le fichier a ete epuree avec succes !\n");
      system("pause");
break;
case (3):
 system ("cls");
      printf("insertion d'un nouvel enregistrement \n");
       strcpy(bloc,"#");
      printf("donnez l'enregistrement a inserer : \n");
      printf("le matricule : ");
      scanf("%ld",&cle);
      mat = cle;
      for (i=1 ; i<7 ;i++)
      {
        bloc[7-i]= (cle%10)+48;
        cle = cle/10;
      }

      strcat(bloc,"#");
      printf("le nom : \n");
      scanf("%s",nom);
      strcat(bloc,"#");
      strcat(bloc,nom);
      printf("le prenom : \n");
      scanf("%s",prenom);
      strcat(bloc,prenom);
      strcat(bloc,"#");
      printf("date de naissance : \n");
      printf ("le jour : \n");
      scanf("%s",jour);
      strcat(bloc,jour);
      printf ("mois : \n");
      scanf("%s",mois);
      strcat(bloc,mois);
      printf("annee : \n");
      scanf("%s",annee);
      strcat(bloc,annee);
      strcat(bloc,"#");
      printf("la wilaya de naissance : \n");
      scanf("%s",city);
      strcat(bloc, city);
      strcat(bloc,"#");
      printf("le groupe sanguin : \n");
      scanf("%s",gs);
      strcat(bloc, gs);
      strcat(bloc,"#");
      printf ("le grade :  \n");
      scanf("%s",gr);
      strcat(bloc, gr);
      strcat(bloc,"#");
      printf("la force armee \n");
      scanf("%s",fa);
      strcat(bloc, fa);
      strcat(bloc,"#");
      printf("la region militaire : \n");
      scanf("%s",regio);
      strcat(bloc,regio );
      strcat(bloc,"#");
      insertion_enreg(bloc,mat,"PERSONNEL-ANP_DZ.bin",rr);
       system("cls");
      printf("l'enregistrement a ete insere !\n");
      system("pause");
      break;
case(4):
      system("cls");
      printf("modification d'une region melitaire \n");
      printf("donnez le matricule de l'enregistrement : \n");
      scanf("%ld",cle);
      printf("donnez la nouvelle region : \n");
      scanf("%s",region_nouv);
      change_region ("ANP-PERSONNEL_DZ.bin", table,cle,region_nouv);
      system ("cls");
      printf("la region a ete modifiee !\n");
      system("pause");
break;
case(5):
      system("cls");
      printf("suppression d'un enregistrement \n");
      printf("donnez le matricule : \n");
      scanf("%ld",cle);
      supprim_enreg (cle, table, n);
      system ("cls");
      printf("l'enregistrement a ete supprime \n");
      system("pause");
break;
case(6):
      system("cls");
      printf("suppression de tous les enregistrements relatifs a une force armee \n");
      indexer_force("ANP-PERSONNEL_DZ.bin",tab_sec,table);
      videur(fa);
      printf("donnez la force armee : \n");
      scanf("%s",fa);
     supprim_force ( tab_sec,table,fa,n);
      system ("cls");
      printf("les enregistrements ont ete supprimes !\n");
      system("pause");
      break;

case (7):
     system("cls");
      printf("Affichage de tous les enregistrements relatifs a une region melitaire ayaant un age entre deux valeurs \n");
      printf("donnez la region militaire : \n");
      scanf("%s",region_nouv);
      printf("donnez l'intervalle d'age : \n");
      printf("le plus petit age : \n");
      scanf("%d",age_p);
      printf("le plus grand age : \n");
      scanf("%d",age_g);
      region_age(year,region,region_nouv,age_p,age_g,"PERSONNEL-ANP_DZ.bin",table);
      system("pause");
      break;

case (8):
      system("cls");

      printf("Affichage de tous les enregistrements relatifs a une categorie \n ");
      printf("donnez la categorie : \n");
      scanf("%s",categorie);
      printf("entrez votre choix \n");
      scanf("%d",choi);
      indexer_grade("PERSONNEL-ANP_DZ.bin ",table,GR);
      afficher_categorie ("ANP-PERSONNEL_DZ.bin",table,GR,choi);
      system("pause");
      break;
case (9):
    system("cls");
    afficher_enreg ("ANP-PERSONNEL_DZ.bin",table,tete);

    break;
case(10):
printf("merci d'avoir utiliser notre programme");
    break;
default:
    printf("ce choix n'existe  pas !");




    }

}

    return 0;
}
