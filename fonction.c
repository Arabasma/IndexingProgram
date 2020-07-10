#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fonction.h"
 time_t t;


/**=====================================affichage=====================================================**/




void menu()
{

    printf("1.  Creation du fichier \n");
    printf("2.  Epuration du fichier \n");
    printf("3.  Insertion d'un nouvel enregistrement \n");
    printf("4.  Modification de la region melitaire \n");
    printf("5.  Suppression d'un enregistrement \n"),
    printf("6.  Suppresion de tous les enregistrements relatif a une force armee \n");
    printf("7.  Affichage de tous les enregistrements relatifs a une region militaire \n");
    printf("8.  Affichage de tous les enregistrements relatifs a une categorie  \n");
    printf("9.  Affichage de l'entete et les trois premiers bloc \n");
    printf("10. Quitter le programme \n");


    printf("votre choix : ");



}
void Afficher (char nom_fich[50])
{ LOVC *f = Ouvrir(nom_fich,'A');
  Buffer *Buf = malloc(sizeof(Buffer));
  int i,cpt=1;
  char *m=NULL;
  char delimiteurs[]="#";
  printf("nombre de bloc %d\n\n",entete(f,1));
 for (i=0; i<3;i++)
 {  cpt=1;
    LireDir(f,Buf,i+1);

        m = strtok(Buf->tableau,delimiteurs);
        printf("champ %d :  %s \n",cpt,m);

         while (m!= NULL)
         { cpt++;
           m = strtok(NULL,delimiteurs);
           printf("champ %d :  %s \n",cpt,m); }
           system("pause");


 }
}

/**=====================================MACHINE ABSTRAITE  FICHIER=====================================**/
void Aff_entete (LOVC *f,int i, int val)
{
  switch (i)
  {
    case 1 :
    {
      f->entete.nbbloc = val ;
    }break;

    case 2 :
    {
     f->entete.nbenreg = val ;
    }break;

    case 3 :
    {
     f->entete.tete = val ;
    } break;

    case 4 :
    {
     f->entete.queue = val ;
    }break;

    case 5 :
    {
     f->entete.ind_libre = val;
    } break;

  };
}

 void Mis_jour_date (LOVC *f,int i)
 { time_t t= time(NULL);
  switch (i)
  {
   case 1 :
   {
     f->entete.date_creation = t;
   } break;

   case 2 :
   {
     f->entete.date_modification = t;
   }break;

  };
}

 int entete(LOVC *f, int i)
 {
  int val;
  switch (i)
  {
   case 1 :
   {
     val = f->entete.nbbloc  ;
   }
   break;
   case 2 :
   {
     val= f->entete.nbenreg ;
   }
   break;
   case 3 :
   {
     val = f->entete.tete ;
   }
   break;
   case 4 :
   {
     val = f->entete.queue ;
   }
   case 5 :
   {
     val = f->entete.ind_libre ;
   }
  };
  return val;
 }




 LOVC *Ouvrir(char nom_fichier[50], char mode ) //ouvrir un fichier en mode binaire
 {   LOVC *f = malloc (sizeof(LOVC));

    if (mode == 'n' || mode == 'N')  //fichier nouveau
    {
     f->fich = fopen(nom_fichier,"wb+");
     Aff_entete(f,1,0);
     Aff_entete(f,2,0);
     Aff_entete(f,3,1);
     Aff_entete(f,4,0);
     Aff_entete(f,5,0);
     Mis_jour_date(f,1);
     fwrite (&(f->entete),sizeof(Entete),1,f->fich);
    }
    if  (mode =='a' || mode == 'A') //fichier déjà existant
    {
     f->fich = fopen(nom_fichier,"rb+");
     fread (&(f->entete), sizeof(Entete),1,f->fich);
    }
   return f;
  }

void  Date (LOVC *f, int i, time_t t)
 {

  switch (i)
  {
   case 1 :
   {
    t= f->entete.date_creation ;
   }
   break;
   case 2 :
   {
    t= f->entete.date_modification ;
   }
   break;
  };

 }


void LireDir (LOVC *f,Buffer *Buf, int i )
 {
    fseek (f->fich,sizeof(Entete)+sizeof(Buf->tableau)*(i-1),SEEK_SET);
    fread (Buf->tableau, sizeof(Buf->tableau),1,f->fich);

 }


void EcrireDir ( LOVC *f, Buffer *Buf, int i )
 {
    fseek (f->fich,sizeof(Entete)+sizeof(Buf->tableau)*(i-1),SEEK_SET);
    fwrite (Buf->tableau,sizeof(Buf->tableau),1,f->fich);

 }


 void Fermer(LOVC *fichier)  // procedure de fermeture du fichier
{
    rewind(fichier->fich);// repositionnement du curseur en debut de fichier

    fwrite(&(fichier->entete),sizeof(Entete),1,fichier->fich); // sauvegarde de la dernière version de l'entete de la strucuture L7OVC
                                                                //dans le fichier
    rewind(fichier->fich);// repositionnement du curseur en debut de fichier
    fclose(fichier->fich);// fermeture du fichier
    //free(fichier);

}


/**================================= MACHINE ABSTRAITE LLC==========================================**/


void allouer (Maillon **nouveau)
   { *nouveau = (Maillon*)malloc(sizeof(Maillon)); }


void aff_adr (Maillon *p , Maillon *q)
         { p->next = q ;}


void aff_val ( Maillon *p , long valeur)
         { p->val = valeur ;}


Maillon *suivant (Maillon *p)
         { return p->next ;}


Maillon *dernier(Maillon *p)
{
  Maillon  *q;
  int trouve=0;
  q =p;
   while ( trouve == 0)
     {
         if ( suivant(q) == NULL) { trouve = 1;}
         else { q = suivant(q);
         }
     }
    return q;
}


long valeur(Maillon *p)
     { return p->val ;}


void liberer  (Maillon **ancien)
{    free(*ancien);
     *ancien= NULL ;}


void afficher (Maillon *p)
{  while (p!= NULL)
    { printf ("cle  %ld \n", valeur(p));
      p = suivant(p) ;
    }
}

/**=================================FONCTION CHARGEMENT=============================================**/

void videur(char ch[]) //vider une chaine de caractère
{
  int i;
  for (i=0 ;i<strlen(ch); i++)
   {
     ch[i]= '\0';
   }
}


long alea (long a, long b) // retourne un nombre aléatoire entre b et a

{
  long i;
  i = ( rand()%(b-a) )+a;
  return i;
}

void decaler (char Tableau[],int n) // décaler les elements du tableau de n case vers la droite
{ char tab[200];
  int i;
  strcpy(tab,Tableau);

    for (i=0; i<strlen(Tableau); i++)
    {
        Tableau[i+n]= tab[i];
    }

}


char lettre(long i) //fais la correspondance entre la lettre et un nombre entre 1 26
{
    char tableau_car[26] ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return tableau_car[i-1];
}


int bissextile (int an) //verifier si c'est une année bisextile
{
  if  ((an%4 ==0) && ((an%100!=0) || (an%400==0)) ) {return 1;}
  else {return 0;}
}


void matricule (char mat[7], long *cle) //generer le matricule de manière aleatoire
{
  long num;
  int i;
  num = alea(111111,999999);
  *cle=num;
  videur(mat);
  for (i=0; i<6;i++)
  {
    mat[5-i]= (num%10)+48;
    num = num/10;
  }
}

void nom_prenom (char nom[31], char prenom[31]) // generer le nom et prenom
{ long taille_nom, taille_prenom;
  int i;
  long car;
  taille_nom = alea(4,30);
  taille_prenom = alea (4,30);
  videur(nom);
  for (i=0 ;i<taille_nom ; i++)
  {
    car = alea(1,26);
    nom[i]= lettre(car);
  }
   nom[i]='\0';
   videur(prenom);
   for(i=0 ;i<taille_prenom ;i++)
   {
     car = alea(1,26);
     prenom[i] = lettre(car);
   }
   prenom[i]='\0';
}

void date_naissance(char annee[5], char mois[11], char jour[3]) //generer date de naissance
{ long year , month , day ;
  char *tableau_mois[12] = {"janvier","fevrier", "mars", "avril", "mai", "juin", "juillet","aout","septembre", "octobre", "novembre", "decembre"};
  int i;

  year = alea(1940,1999);
  month = alea (1,12);
  videur(mois);
  strcpy(mois,tableau_mois[month-1]);
  videur(annee);
  for (i=0 ; i<4 ;i++)
  {  if ((year%10)==0 ) {annee[3-i] = 48 ;}
    else { annee[3-i]= (year%10) +48 ; }
    year = year/10;
  }
  annee[i]='\0';

  if ( (month%2==1 && month<8) || (month%2==0 && month >7) )
   {
     day = alea(1,31) ;
   }
   else
   { if ( month == 2)
      { if ( bissextile (year)==1) {day = alea(1,29);}
        else { day = alea (1,28);}
      }
     else
      {
       day = alea(1,30);
      }
   }

    videur(jour);
    jour[0]= (day/10)+48;
    jour[1]= (day%10)+48;
    jour[2]= '\0';

}




void wilaya (char city[26]) // generer wilaya
{
  long num;
  char *tableau_wilaya[48]={"Adrar","Chlef","Laghouat","Oum El-Bouaghi","Batna","Béjaïa","Biskra","Béchar","Blida","Bouira","Tamanrasset","Tébessa","Tlemcen","Tiaret","Tizi-Ouzou","Alger","Djelfa","Jijel","Sétif","Saida","Skikda","Sidi Bel Abbes","Annaba","Guelma","Constantine","Médéa","Mostaganem","MSila","Mascara","Ouargla","Oran","El-Bayadh","Illizi","Bordj-Bourréridj","Boumerdès","El-Taref","Tindouf","Tissemsilt","El Oued","Khenchela","Souk Ahras","Tipaza","Mila","Ain Defla","Naâma","Ain Témouchent","Ghardaïa","Relizane"};
  num = alea(1,48);
  videur(city);
  strcpy(city,tableau_wilaya[num-1]);
}



void grp_sg (char g_s[4]) // generer groupe sanguin
{ long num;
  char *tableau_grpsang[8]={"O+","A+","B+","O-","A-","AB+","B-","AB-"};
  num = alea(1,8);
  videur(g_s);
  strcpy(g_s,tableau_grpsang[num-1]);
  g_s[3]='\0';
}



void grade (char g[26]) // generer grade militaire
{ long num ;
  char *tableau_grade[17] = {"Général de corps d’armée","Général-Major","Général","Colonel","Lieutenant-colonel","Commandant", "Capitaine","Lieutenant","Sous-lieutenant"," Aspirant", "Adjudant-chef","Adjudant","Sergent chef","Sergent","Caporal-chef","Caporal","Djoundi"};
  num = alea(1,17);
  videur(g);
  strcpy(g,tableau_grade[num-1]);
  g[strlen(g)]='\0';
}




void force_armee (char f[60]) // generer force armée
{ long num;
  char *tableau_force_armee[8] = {"Armée de terre","Armée de l’air","Marine nationale", "Défense aérienne du territoire","Gendarmerie nationale","Garde républicaine","Département du renseignement et de la sécurité","Santé militaire"};
  num = alea(1,8);
  videur(f);
  strcpy(f,tableau_force_armee[num-1]);
  f[strlen(f)]='\0';
}




void region_militaire(char r_m[20]) // generer région militaire armée
{ long num;
  char *tableau_region[6]={"1RM-Blida","2RM-Oran","3RM-Béchar","4RM-Ouargla","5RM-Constantine","6RM-Tamenrasset"};
  num = alea(1,6);
  videur(r_m);
  strcpy(r_m,tableau_region[num-1]);

}

void chargement_initial (long N) //creation du fichier avec des enregistrement dont les elements sont generés de manière aléatoires
{ LOVC *fichier = NULL;
  Buffer *Buf = malloc(sizeof(Buffer));
  char CLE[7]="*" ,NOM[31]="*",PRE[31]="*",AN[5]="*" ,MO[11]="*",JO[3]="*" ,j[2]="*" ,CI[26]="*",G_S[4]="*",GR[26]="*",F_A[60]="*",R_M[20]="*";
  char bloc[300]="*";
  char tableau[1024];
  videur(tableau);
  long mat;
  int cpt=0,l=0,k=0, compt=0,taille,u=0;
  long i;
  int num_bloc=1 , suiv=2;
  videur(j);
  fichier = Ouvrir("PERSONNEL-ANP_DZ.bin", 'N');
  videur(Buf->tableau);

  for (i=0; i<N ;i++)
   {  videur(bloc);
     matricule(CLE,&mat); nom_prenom(NOM,PRE); date_naissance(AN,MO,JO); wilaya(CI); grp_sg(G_S); grade(GR); force_armee(F_A); region_militaire(R_M);
     strcat(bloc,"#");
     strcat(bloc,CLE);strcat(bloc,"#");
     strcat(bloc,NOM);strcat(bloc,"#");
     strcat(bloc,PRE);strcat(bloc,"#");
     if(JO[0]==48){j[0]=JO[1]; j[1]='\0';strcat(bloc,j);}
     else {strcat(bloc,JO);}
     strcat(bloc,MO);strcat(bloc,AN);strcat(bloc,"#");
     strcat(bloc,CI);strcat(bloc,"#");
     strcat(bloc,G_S);strcat(bloc,"#");
     strcat(bloc,GR);strcat(bloc,"#");
     strcat(bloc,F_A);strcat(bloc,"#");
     strcat(bloc,R_M);strcat(bloc,"#");
     taille = strlen(bloc);
     l = cpt;
     decaler (bloc,3);
     for (k=0; k<3; k++)
     {
       bloc[k]= (taille%10)+48;
       taille =taille/10;
     }
     cpt=l;
     k=0;
     while ( (l<1024) && (k<strlen(bloc)))
     {
        Buf->tableau[l]= bloc[k];
        l++;
        k++;
     }
     cpt=l;
     compt =k;
     if (cpt >= 1024)
     { Buf->num_bloc = num_bloc;
       if (i==N) {Buf->bloc_suiv = -1;}
       else {Buf->bloc_suiv =suiv ;}
       EcrireDir(fichier,Buf,num_bloc);
       videur(Buf->tableau);
       num_bloc++;
       suiv++;
       cpt=0;
     }
     if (k >= strlen(bloc)) {k=0;}
     else
     { l=cpt;
      videur(Buf->tableau);
      strcpy(Buf->tableau,tableau);
      for (k=compt ;k<strlen(bloc);k++)
         {
           Buf->tableau[l]= bloc[k];
           l++;
         }
      compt=k;
      for (u = compt; u<1024; u++)
      {
        Buf->tableau[u]='\0';
      }
       k=0;
       compt =0;
       cpt=l;
     }
  }

  if (l<= 1024)
  {
     Buf->num_bloc = num_bloc;
     Buf->bloc_suiv = -1;
     EcrireDir(fichier,Buf,num_bloc);
     videur(Buf->tableau);
     suiv++;
  }
   Aff_entete(fichier,1,num_bloc);
   Aff_entete(fichier,2,N);
   Aff_entete(fichier,3,1);
   Aff_entete(fichier,4,num_bloc);
   Aff_entete(fichier,5,l);
   Mis_jour_date(fichier,1);
   Mis_jour_date(fichier,2);
  Fermer(fichier);
}

/**====================================FONCTION INDEXATION CLE =====================================**/

void indexer_cle (struct index_primaire tab[],char fich[50]) //creer un idex selon les clées
{ long mat=0,bloc=0;
  long i=1 ,puissance=100000 ,l=0 ;
  int taille=0,j=0, power=1 ,repeter=0,cpt=0, compt=0;  //pos=0, ind=0,
  LOVC *fichier = NULL;
  Buffer *Buf = malloc(sizeof(Buffer));
  fichier = Ouvrir(fich, 'A');

  LireDir(fichier,Buf,i);
  while ( l < entete(fichier,2) )

 {
    puissance= 100000;
    mat=0;
    power=1;
    taille =0;
    repeter=0;
    if (j>1023 ) {j= j-1024; i++; LireDir(fichier,Buf,i);}
   while (repeter<3)
    {  if (j<1024) { taille = taille + (Buf->tableau[j]-48)*power;}
      else {j=0;
            i++;
            videur(Buf->tableau);
            LireDir(fichier,Buf,i);
            taille = taille + (Buf->tableau[j]-48)*power;
           }
      j++;
      power=power*10;
      repeter++;
    }
    repeter=0;
    if (j > 1023)
        {   j=0;
            i++;
            videur(Buf->tableau);
            LireDir(fichier,Buf,i);
          }
    cpt = j;
    bloc = i;
    compt = cpt;
    tab[l].position = compt;
    j = j+1;
    while (repeter<6)
    { if (j < 1024) {mat = mat + (Buf->tableau[j]-48)*puissance;}
      else  {   j=0; cpt=0; taille = taille-(repeter+1);
                i++;
                videur(Buf->tableau);
                LireDir(fichier,Buf,i);
                mat = mat + (Buf->tableau[j]-48)*puissance;
            }

      puissance = puissance/10;
      j++;
      repeter++;
    }
    tab[l].efface = 'f';
    tab[l].cle = mat;
    tab[l].num_bloc = bloc;

    l++;
    j = cpt + taille;

  }
  Fermer(fichier);
}

void tri_bulles(index_primaire tab[],long taille) // trie bulle pour index
{  long i;
    int tab_en_ordre = 0;

while( tab_en_ordre == 0)
    {
        tab_en_ordre = 1 ;
        for( i=0 ; i < taille-1 ; i++)
        {
            if(tab[i].cle > tab[i+1].cle)
            {
                permuter(&tab[i],&tab[i+1]);
                tab_en_ordre = 0;
            }
        }
        taille--;
    }
}


void permuter (index_primaire *a , index_primaire *b) // permutation de deux elements d'unn index
{ struct index_primaire*sauv = malloc(sizeof(index_primaire));
   sauv->cle = a->cle;
   sauv->num_bloc = a->num_bloc;
   sauv->position= a->position;
   sauv->efface = a->efface;
   a->cle =   b->cle;
   a->num_bloc= b->num_bloc;
   a->position= b->position;
   a->efface= b->efface;
   b->cle =  sauv->cle;
   b->num_bloc= sauv->num_bloc;
   b->position= sauv->position;
   b->efface= sauv->efface;
}



/**==========================================FONCTION INDEXATION SECONDAIRE========================================**/
                                 /**===============PARTIE INITIALISATION===============**/
void initialiser_force (index_secondaire tableau[]) //initialiser l'index secondaire de la force armée
{
  tableau[0].chaine= "Armée de terre" ;
  tableau[1].chaine= "Armée de l’air";
  tableau[2].chaine= "Marine nationale";
  tableau[3].chaine= "Défense aérienne du territoire";
  tableau[4].chaine= "Gendarmerie nationale" ;
  tableau[5].chaine= "Garde républicaine";
  tableau[6].chaine= "Département du renseignement et de la sécurité";
  tableau[7].chaine= "Santé militaire";
  int i ;
  for (i=0 ; i<8 ; i++)
  {
    tableau[i].liste=NULL;
  }
}


void initialiser_region (index_secondaire tableau[]) //initialiser l'index secondaire de la region
{
  tableau[0].chaine= "1RM-Blida" ;
  tableau[1].chaine= "2RM-Oran";
  tableau[2].chaine= "3RM-Béchar";
  tableau[3].chaine= "4RM-Ouargla";
  tableau[4].chaine= "5RM-Constantine" ;
  tableau[5].chaine= "6RM-Tamenrasset";

  int i ;
  for (i=0 ; i<6 ; i++)
  {
    tableau[i].liste=NULL;
  }
}




void initialiser_grade (index_secondaire tableau[])//initialiser l'index secondaire du grade
{
  tableau[0].chaine= "Général de corps d’armée" ;
  tableau[1].chaine= "Général-Major";
  tableau[2].chaine= "Général";
  tableau[3].chaine= "Colonel";
  tableau[4].chaine= "Lieutenant-colonel" ;
  tableau[5].chaine= "Commandant";
  tableau[6].chaine= "Capitaine" ;
  tableau[7].chaine= "Lieutenant";
  tableau[8].chaine= "Sous-lieutenant";
  tableau[9].chaine= " Aspirant";
  tableau[10].chaine= "Adjudant-chef" ;
  tableau[11].chaine= "Adjudant";
  tableau[12].chaine= "Sergent chef" ;
  tableau[13].chaine= "Sergent";
  tableau[14].chaine= "Caporal-chef";
  tableau[15].chaine= "Caporal";
  tableau[16].chaine= "Djoundi";

  int i ;
  for (i=0 ; i<17 ; i++)
  {
    tableau[i].liste=NULL;
  }
}



void initialiser_annee (index_annee table[]) //initialiser l'index secondaire de l'annee
{ int i,j=0;
  for (i=1940; i<2000 ; i++)
   {
     table[j].an = i;
     table[j].liste = NULL;
     j++;
   }
}


                    /**=========================RECUPERTAION INDICE D'INDEX===========================**/
int indice(char mot[], index_secondaire tableau[]) //recherche dans un index secondaire
{ int i=0 , trouv =0;
   while (trouv == 0)
   {
    if (strcmp(tableau[i].chaine,mot) ==0) {trouv =1;}
     i++;

   }

  return i;
}


int indice_an (int mot, index_annee tableau[]) //recherche dans un index annee
{ int i=0 , trouv =0;
   while (trouv == 0)
   {
    if (tableau[i].an == mot) {trouv =1;}
     i++;

   }

  return i;
}




/**=======================================FONCTIONS D'INDEXATION============================**/



void indexer_force (char fich[50], index_secondaire tab[],index_primaire tableau[]) //indexer le fichier et crer index force
{ int i, trouv=0,k=0, ind=0;
long l,bloc,cle;
 struct Maillon  *p, *q,*ma ;
  LOVC *fichier = NULL;
  char force[60];
  Buffer *Buf = malloc(sizeof(Buffer));
  fichier = Ouvrir(fich, 'A');
  initialiser_force(tab);
  for (l=0; l<entete(fichier,2);l++)
  { trouv=0;
    bloc = tableau[l].num_bloc;
    i = tableau[l].position;
    cle = tableau[l].cle;
    LireDir(fichier,Buf,bloc);
    while (trouv != 8)
    {
      if (Buf->tableau[i]== '#') {trouv++;}
      i++;
      if (i> 1023) {i=0;
                    videur(Buf->tableau);
                    LireDir(fichier,Buf,bloc+1);}
    }
    videur(force);
    k=0;
    while (Buf->tableau[i]!= '#')
    {

       if (i> 1023) { i=-1;
                      videur(Buf->tableau);
                      LireDir(fichier,Buf,bloc+1);
                    }
      else {force[k]= Buf->tableau[i]; k++;}
       i++;

     }
     while (k<60)
     {
         force[k]='\0';
         k++;
     }

     ind = indice(force,tab)-1;
     ma = tab[ind].liste;
     if ( ma  == NULL  ) { allouer (&p);
                           aff_val(p,cle);
                           aff_adr(p,NULL);
                           tab[ind].liste=p ;}

     else {  allouer (&q);
            aff_val (q,cle);
            aff_adr(q,NULL);
            p=dernier(tab[ind].liste);
            aff_adr(p,q);
           }
  }

Fermer(fichier);
}




void indexer_region (char fich[50], index_secondaire tab[],index_primaire tableau[]) //indexer le fichier et crer index region
{ int i, trouv=0,k=0, ind=0;
long l,bloc,cle;
 struct Maillon  *p, *q,*ma ;
  LOVC *fichier = NULL;
  char region[20];
  Buffer *Buf = malloc(sizeof(Buffer));
  fichier = Ouvrir(fich, 'A');
  initialiser_region(tab);
  for (l=0; l<entete(fichier,2);l++)
  { trouv=0;
    bloc = tableau[l].num_bloc;
    i = tableau[l].position;
    cle = tableau[l].cle;
    LireDir(fichier,Buf,bloc);
    while (trouv != 9)
    {
      if (Buf->tableau[i]== '#') {trouv++;}
      i++;
      if (i> 1023) {i=0;
                    videur(Buf->tableau);
                    LireDir(fichier,Buf,bloc+1);}
    }
    videur(region);
    k=0;
    while (Buf->tableau[i]!= '#')
    {
       if (i> 1023) { i=-1;
                      videur(Buf->tableau);
                      LireDir(fichier,Buf,bloc+1);
                    }
       else { region[k]= Buf->tableau[i];k++;}
       i++;

     }
     while (k<20)
     {
         region[k]='\0';
         k++;
     }
     ind = indice(region,tab)-1;
     ma = tab[ind].liste;
     if ( ma  == NULL  ) { allouer (&p);
                           aff_val(p,cle);
                           aff_adr(p,NULL);
                           tab[ind].liste=p ;}

     else {  allouer (&q);
            aff_val (q,cle);
            aff_adr(q,NULL);
            p=dernier(tab[ind].liste);
            aff_adr(p,q);
           }
  }

Fermer(fichier);
}


void indexer_grade (char fich[50], index_secondaire tab[],index_primaire tableau[]) //indexer le fichier et crer index grade
{ int i, trouv=0,k=0, ind=0;
long l,bloc,cle;
 struct Maillon  *p, *q,*ma ;
  LOVC *fichier = NULL;
  char grade[25];
  Buffer *Buf = malloc(sizeof(Buffer));
  fichier = Ouvrir(fich, 'A');
  initialiser_grade(tab);
  for (l=0; l<entete(fichier,2);l++)
  { trouv=0;
    bloc = tableau[l].num_bloc;
    i = tableau[l].position;
    cle = tableau[l].cle;

    LireDir(fichier,Buf,bloc);
    while (trouv != 7)
    {
      if (Buf->tableau[i]== '#') {trouv++;}
      i++;
      if (i> 1023) {i=0;
                    videur(Buf->tableau);
                    LireDir(fichier,Buf,bloc+1);}
    }
    videur(grade);
    k=0;
    while (Buf->tableau[i]!= '#')
    {

       if (i> 1023) { i=-1;
                      videur(Buf->tableau);
                      LireDir(fichier,Buf,bloc+1);
                    }
       else { grade[k]= Buf->tableau[i];k++;}


       i++;

     }
     while (k<25)
     {
         grade[k]='\0';
         k++;
     }

     ind = indice(grade,tab)-1;
     ma = tab[ind].liste;
     if ( ma  == NULL  ) {  allouer (&p);
                            aff_val(p,cle);
                            aff_adr(p,NULL);
                            tab[ind].liste=p ;
                         }

     else {  allouer (&q);
             aff_val (q,cle);
             aff_adr(q,NULL);
             p=dernier(tab[ind].liste);
             aff_adr(p,q);
           }
  }

Fermer(fichier);
}



void indexer_annee (char fich[50], index_annee tab[],index_primaire tableau[]) //indexer le fichier et crer index annee
{ int i, trouv=0,k=0, ind=0, h=0;
long l,bloc,cle;
int year=0, puissance, cpt;
 struct Maillon  *p, *q,*ma ;
  LOVC *fichier = NULL;
  char anne[25];
  initialiser_annee(tab);
  Buffer *Buf = malloc(sizeof(Buffer));
  fichier = Ouvrir(fich, 'A');
  for (l=0; l<entete(fichier,2);l++)
  { trouv=0;
    puissance = 1000;
    bloc = tableau[l].num_bloc;
    i = tableau[l].position;
    cle = tableau[l].cle;
    //j=i;
    LireDir(fichier,Buf,bloc);
    while (trouv != 4)
    {
      if (Buf->tableau[i]== '#') {trouv++;}
      i++;
      if (i> 1023) {i=0;
                    videur(Buf->tableau);
                    LireDir(fichier,Buf,bloc+1);}
    }
    videur(anne);
    k=0;
    while (Buf->tableau[i]!= '#')
    {

       if (i> 1023) { i=-1;
                      videur(Buf->tableau);
                      LireDir(fichier,Buf,bloc+1);
                    }
       else { anne[k]= Buf->tableau[i];k++;}
       i++;

     }

     while (k<25)
     {
         anne[k]='\0';
         k++;
     }

     ind = strlen(anne) - 4;
     year = 0;
    for (h=ind ; h<ind+4; h++)
    {
        year = year + (anne[h]-48)*puissance;
        puissance = puissance/10;
    }
    cpt = indice_an(year,tab)-1;
     ma = tab[cpt].liste;
     if ( ma  == NULL  ) {  allouer (&p);
                            aff_val(p,cle);
                            aff_adr(p,NULL);
                            tab[cpt].liste=p ;
                         }

     else {  allouer (&q);
             aff_val (q,cle);
             aff_adr(q,NULL);
             p=dernier(tab[cpt].liste);
             aff_adr(p,q);
           }
  }

Fermer(fichier);
}

/**==================================SAUVEGARDE ET CHARGEMENT D'INDEX A PARTIR DE FICHIERS=============================**/
void save_index (char fichier[20],index_primaire table[],long n) //sauvegarder index primaire dans un fichier
{
  FILE *f=NULL;
  f= fopen(fichier,"wb+");

    fwrite (table,sizeof(index_primaire),n,f);
    fclose(f);

 }

void charger_index (char fichier[20], index_primaire table[],long n) // charger index primaire à partir d'un fichier
{
  FILE *f=NULL;
     f= fopen(fichier,"rb+");
     fread (table,sizeof(index_primaire),n,f);
     fclose(f);

 }

void save_second (char fichier[20],index_secondaire table[],long n) //sauvegarder index secondaire dans un fichier
{
  FILE *f=NULL;
  f= fopen(fichier,"wb+");

    fwrite (table,sizeof(index_secondaire),n,f);
    fclose(f);

 }

void charger_second (char fichier[20], index_secondaire table[],long n) // charger index secondaire à partir d'un fichier
{
  FILE *f=NULL;
     f= fopen(fichier,"rb+");
     fread (table,sizeof(index_secondaire),n,f);
     fclose(f);

 }


 void save_annee (char fichier[20],index_annee table[],long n)  //sauvegarder index annee dans un fichier
{
  FILE *f=NULL;
  f= fopen(fichier,"wb+");

    fwrite (table,sizeof(index_annee),n,f);
    fclose(f);

 }

void charger_annee (char fichier[20], index_annee table[],long n) // charger index annee à partir d'un fichier
{
  FILE *f=NULL;
     f= fopen(fichier,"rb+");
     fread (table,sizeof(index_annee),n,f);
     fclose(f);

 }

/**=====================MODIFICATION DE LA REGION D'UN ENREGISTREMENT===================**/
void rechercher_cle (long cle, index_primaire table[],long *ind , int *trouv , long taille) //rechercher cle dans index
 {
    long BI = 0 ;
    long M ;
    long  BS = taille -1 ;
     M = ( BI + BS) / 2 ;
     *trouv = 0;
      while ((BI <= BS) && (*trouv==0))
   {
        if ( table[M].cle == cle ) {*trouv = 1 ; *ind= M ;}
     else
     { if (table[M].cle < cle ) { BI = M +1;}
       else { BS = M -1;} }
      M = ( BI + BS) / 2 ;
   }
      if (*trouv==0) { *ind = BI ;}
}

void change_region (char nom_fichier[50], index_primaire tab[],long cle, char region_new[25]) //changer region d'un enregistrement
{ LOVC *fichier1 = NULL, *fichier2=NULL;
  Buffer *Buf1 = malloc(sizeof(Buffer));
  Buffer *Buf = malloc(sizeof(Buffer));
  char bloc[300]="*";
  long ind,bloc_index;
  int cpt=0,l=0,k=0, compt=0,taille,u=0, trouv=0,pos_buf,repeter,h=0;
  long i;
  int num_bloc=1 , suiv=2;
  cpt = rename(nom_fichier,"copie.bin");
  fichier2 = Ouvrir("copie.bin",'A');
  videur(Buf1->tableau);
  videur(Buf->tableau);
  rechercher_cle(cle,tab,&ind,&trouv,entete(fichier2,2));
  if (trouv==0) {printf("cet enregistrement n'existe pas dans le fichier");}
  else
  { fichier1 = Ouvrir(nom_fichier, 'N');
   for (i=0; i<entete(fichier2,2) ;i++)
    { videur(bloc);
      bloc_index = tab[i].num_bloc;
      repeter = 0;
      taille = 0;
      pos_buf = tab[i].position;
      LireDir(fichier2,Buf,bloc_index);
      k=0;
      if (cle ==tab[i].cle)
        { repeter = 0;
          videur(bloc);
         while (repeter != 9 )
          {
              if (pos_buf>1023) { pos_buf=0;
                                 videur(Buf->tableau);
                                 LireDir(fichier2,Buf,bloc_index+1);
                               }
             if (Buf->tableau[pos_buf]== '#') {repeter++;}
             bloc[k]= Buf->tableau[pos_buf];
                  k++;
                  pos_buf++;

          }
          h=0;

          while (h < strlen(region_new))
          {
            bloc[k]= region_new[h];
            k++;
            h++;
          }

          h=k;
          while (h < 300)
          { bloc[h]='\0';
            h++; }
            strcat(bloc,"#");
          taille = strlen(bloc);
          decaler (bloc,3);
       for (k=0; k<3; k++)
         {
           bloc[k]= (taille%10)+48;
           taille =taille/10;
         }

        }
     else
     {   repeter = 0;
         taille = 0;
     videur(bloc);
     pos_buf = tab[i].position;
          while (repeter != 10 )
          {
              if (pos_buf>1023) { pos_buf=0;
                                 videur(Buf->tableau);
                                 LireDir(fichier2,Buf,bloc_index+1);
                               }
             if (Buf->tableau[pos_buf]== '#') {repeter++;}
             bloc[k]= Buf->tableau[pos_buf];
                  k++;
                  pos_buf++;

          }

            h = k;
         while (h < 300)
          { bloc[h]='\0';
            h++; }

          taille=strlen(bloc);
          decaler (bloc,3);
       for (k=0; k<3; k++)
         {
           bloc[k]= (taille%10)+48;
           taille =taille/10;
         }

     }
       cpt=l;
       k=0;
     while ( (l<1024) && (k<strlen(bloc)))
     {
        Buf1->tableau[l]= bloc[k];
        l++;
        k++;
     }
     cpt=l;
     compt =k;
     if (l >= 1024)
     { Buf1->num_bloc = num_bloc;
       if (i==entete(fichier2,2)) {Buf1->bloc_suiv = -1;}
       else {Buf1->bloc_suiv =suiv ;}
       EcrireDir(fichier1,Buf1,num_bloc);
       videur(Buf1->tableau);
       num_bloc++;
       suiv++;
       cpt=0;l=0;
     }
     if (k >= strlen(bloc)) {k=0;}
     else
     { l=cpt;
      videur(Buf1->tableau);
      for (k=compt ;k<strlen(bloc);k++)
         {
           Buf1->tableau[l]= bloc[k];
           l++;
         }
      compt=k;
      for (u = compt; u<1024; u++)
      {
        Buf1->tableau[u]='\0';
      }
       k=0;
       compt =0;
       cpt=l;
     }
  }

  if (l<= 1024)
  {
     Buf->num_bloc = num_bloc;
     Buf->bloc_suiv = -1;
     EcrireDir(fichier1,Buf1,num_bloc);
     videur(Buf1->tableau);
     suiv++;
  }

   Aff_entete(fichier1,1,num_bloc);
   Aff_entete(fichier1,2,entete(fichier2,2));
   Aff_entete(fichier1,3,1);
   Aff_entete(fichier1,4,num_bloc);
   Aff_entete(fichier1,5,l);
   Mis_jour_date(fichier1,2);
  Fermer(fichier1);
  }
  Fermer(fichier2);
   remove("copie.bin");
}
void supprim_enreg (long cle, index_primaire table[], long taille)  //supprimer un enregistrement
{   long i;
    int found;
   rechercher_cle(cle,table,&i,&found,taille);
   if (found==0) {printf("Cet enregistrement n'existe pas dans le fichier \n");}
   else {table[i].efface = 'v';}
}

void supprim_force (index_secondaire table[], index_primaire tab[], char force[], long taille)
{ int trouv=0;
  long i=0, cle;
  Maillon *p;
  while (trouv == 0)
  {
    if (strcmp(table[i].chaine,force)==0) {trouv = 1;}
    else {i++;}
  }

  p=table[i].liste;
  while ( p != NULL)
  { cle = valeur(p);
    supprim_enreg(cle,tab,taille);
  }
  table[i].liste = NULL;
}

void afficher_enreg (char nom_fich[],index_primaire tab[],Maillon *liste)
{ Maillon *p=NULL;
  LOVC *f=NULL;
  Buffer *Buf=malloc(sizeof(Buffer));
  f= Ouvrir(nom_fich,'A');
  long cpt=0,ind=0;
  char bloc[200];
  int  pos_buf=0, bloc_index=0, trouv=0 ,k=0,repeter;
  p= liste;

  while (p!=NULL)
  { rechercher_cle(valeur(p),tab,&ind, &trouv,entete(f,2));
    pos_buf = tab[ind].position;
    bloc_index = tab[ind].num_bloc;
    videur(bloc);
    k=0;
    cpt++;
    if (tab[ind].efface == 'f')
    {LireDir(f,Buf,bloc_index);
     repeter = 0;
    while (repeter != 10 )
          {
              if (pos_buf>1023) { pos_buf=0;
                                 videur(Buf->tableau);
                                 LireDir(f,Buf,bloc_index+1);
                               }
             if (Buf->tableau[pos_buf]== '#') {repeter++;}
             bloc[k]= Buf->tableau[pos_buf];
                  k++;
                  pos_buf++;

          }
         while (k < 200)
          { bloc[k]='\0';
            k++; }
         printf("enregistrement numero %ld : %s\n",cpt,bloc);

    }
    p=suivant(p);

  }
 Fermer(f);
}


void region_age (index_annee year[], index_secondaire region[],char reg[], int age1, int age2, char nom_fichier[],index_primaire table[])
{ int year1=0, year2=0, trouv=0;
   long i=0;
  Maillon *p=NULL, *q=NULL, *fin=NULL;
   year1 = 2017-age1;
   year2 = 2017-age2;

   if ( year1 > 1999 || year1 <1940 || year2 > 1999 || year2<1940) {printf("il n'existe pas de personne ayant un age entre %d et %d\n",age1,age2);}
 else
 {
    while (trouv == 0)
     {
       if (strcmp(region[i].chaine,reg)==0) {trouv = 1;}
       else {i++;}
     }
     p = region[i].liste;
   for(i= year2-1940 ; i<=year1-1940; i++)
   {
      q = year[i].liste;
     if (fin==NULL) { fin = intersection(p,q); }
     else {aff_adr(dernier(fin),intersection(p,q));}
   }
   system("cls");

   printf("voila tous les enregistrements relatif a la region %s dont l'age est entre %d et %d :",reg,age1,age2);
   afficher_enreg(nom_fichier,table,fin);
  }
}

void afficher_categorie (char fich[],index_primaire table[],index_secondaire GR[],int choix)
{
  switch (choix)
 { case 1 :
   { afficher_enreg(fich,table,GR[0].liste);
     afficher_enreg(fich,table,GR[1].liste);
     afficher_enreg(fich,table,GR[2].liste);
   } break;
  case 2 :
   { afficher_enreg(fich,table,GR[3].liste);
     afficher_enreg(fich,table,GR[4].liste);
     afficher_enreg(fich,table,GR[5].liste);
   }  break;
  case 3 :
   { afficher_enreg(fich,table,GR[6].liste);
     afficher_enreg(fich,table,GR[7].liste);
     afficher_enreg(fich,table,GR[8].liste);
     afficher_enreg(fich,table,GR[9].liste);
   } break;
   case 4 :
   { afficher_enreg(fich,table,GR[10].liste);
     afficher_enreg(fich,table,GR[11].liste);
     afficher_enreg(fich,table,GR[12].liste);
     afficher_enreg(fich,table,GR[13].liste);
   } break;
   case 5 :
   { afficher_enreg(fich,table,GR[14].liste);
     afficher_enreg(fich,table,GR[15].liste);
     afficher_enreg(fich,table,GR[16].liste);
   } break;
 };
}


void epuration (char fich[],index_primaire tab[],long *nb_enreg)
{ LOVC *fichier1 = NULL, *fichier2=NULL;
  Buffer *Buf1 = malloc(sizeof(Buffer));
  Buffer *Buf = malloc(sizeof(Buffer));
  char bloc[300]="*";
  long i,bloc_index,nomb_enreg=0;
  int cpt=0,l=0,k=0, compt=0,taille,u=0, trouv=0,pos_buf,repeter;
  int num_bloc=1 , suiv=2;
  rename(fich,"copie1.bin");
  fichier1 = Ouvrir(fich,'N');
  fichier2 = Ouvrir("copie1.bin",'A');
  videur(Buf1->tableau);
  videur(Buf->tableau);
  for (i=0 ; i<entete(fichier2,2);i++)
  { pos_buf = tab[i].position;
    bloc_index =tab[i].num_bloc;
    rechercher_mat(tab,i,&trouv);
    if (trouv==0)
    {  nomb_enreg++; taille = 0;
        repeter = 0;
        k=0;
        videur(bloc);
        LireDir(fichier2,Buf,bloc_index);
          while (repeter != 10 )
           {
              if (pos_buf>1023) {  pos_buf=0;
                                   videur(Buf->tableau);
                                   LireDir(fichier2,Buf,bloc_index+1);
                                }
              if (Buf->tableau[pos_buf]== '#') {repeter++;}
              bloc[k]= Buf->tableau[pos_buf];
              k++;
              pos_buf++;

            }

          while (k < 300)
           {  bloc[k]='\0';
             k++; }

        taille=strlen(bloc);
        decaler (bloc,3);
         for (k=0; k<3; k++)
          {
            bloc[k]= (taille%10)+48;
            taille =taille/10;
          }

       cpt=l;
       k=0;
     while ( (l<1024) && (k<strlen(bloc)))
     {
        Buf1->tableau[l]= bloc[k];
        l++;
        k++;
     }
     cpt=l;
     compt =k;
     if (l >= 1024)
     { Buf1->num_bloc = num_bloc;
       if (i==entete(fichier2,2)) {Buf1->bloc_suiv = -1;}
       else {Buf1->bloc_suiv =suiv ;}
       EcrireDir(fichier1,Buf1,num_bloc);
       videur(Buf1->tableau);
       num_bloc++;
       suiv++;
       cpt=0;l=0;
     }
     if (k >= strlen(bloc)) {k=0;}
     else
     { l=cpt;
      videur(Buf1->tableau);
      for (k=compt ;k<strlen(bloc);k++)
         {
           Buf1->tableau[l]= bloc[k];
           l++;
         }
      compt=k;
      for (u = compt; u<1024; u++)
      {
        Buf1->tableau[u]='\0';
      }
       k=0;
       compt =0;
       cpt=l;
     }
  }
  }
  if (l<= 1024)
  {
     Buf->num_bloc = num_bloc;
     Buf->bloc_suiv = -1;
     EcrireDir(fichier1,Buf1,num_bloc);
     videur(Buf1->tableau);
     suiv++;
  }

   Aff_entete(fichier1,1,num_bloc);
   Aff_entete(fichier1,2,nomb_enreg);
   Aff_entete(fichier1,3,1);
   Aff_entete(fichier1,4,num_bloc);
   Aff_entete(fichier1,5,l);
   Mis_jour_date(fichier1,2);
  Fermer(fichier1);
  *nb_enreg = nomb_enreg;
  Fermer(fichier2);
  remove("copie1.bin");

}

void rechercher_mat (index_primaire table[],long ind , int *trouv) //rechercher matricule
{  long i=0;
   int found=0;
   while (found==0 && i<ind)
   {
       if(table[i].cle == table[ind].cle) {found=1;}
       else {i++;}
    }

   *trouv = found;
}


Maillon *intersection (Maillon *p , Maillon *q)
{ Maillon *k=NULL, *l=NULL , *pi=NULL , *qi=NULL, *fi=NULL;
  k= p;

  while (k!=NULL)
 { l= q;
   while ((l!=NULL) )
   { if ( valeur(k)== valeur(l))
     {
         if (fi==NULL)
           { allouer(&pi);
             aff_val(pi,valeur(l));
             aff_adr(pi,NULL);
             fi = pi;
           }
        else
          { allouer(&qi);
            aff_val (qi,valeur(l));
            aff_adr(pi,qi);
            pi=qi;
          }
     }
     l= suivant(l);
   }
   k = suivant(k);

 }

if (pi != NULL) {aff_adr(pi,NULL);}
 return fi;
}



/**================================================insertion===============================================**/
void insertion_enreg (char bloc[],long cle,char fich[], index_primaire tab[]) //inserer enregistrement dans fich
{ LOVC *f=NULL;
  Buffer *Buf = malloc(sizeof(Buffer));
  long ind=0;
  int trouv, pos,num_bloc,k=0,taille;
  f = Ouvrir(fich,'A');
  rechercher_cle(cle,tab,&ind,&trouv,entete(f,2));
  if (trouv==1) {printf("cet enregistrement existe deja \n");}
  else {
          num_bloc =entete(f,1);;
          LireDir(f,Buf,num_bloc);
          pos = entete(f,5);
          taille= strlen(bloc);
          decaler(bloc,3);
          for (k=0 ;k<3 ;k++)
          {
            bloc[k] = (taille%10)+48;
            taille = taille/10;
          }
         k=0;
          while (k<strlen(bloc))
           { if (pos>1023) { pos =0;
                             num_bloc++;
                             EcrireDir(f,Buf,num_bloc);
                           }
              Buf->tableau[pos] = bloc[k];
              k++;
              pos++;
           }
           if (pos<=1024) {EcrireDir(f,Buf,num_bloc);}
             Aff_entete(f,1,num_bloc);
             Aff_entete(f,2,entete(f,2)+1);
             Aff_entete(f,3,1);
             Aff_entete(f,4,num_bloc);
             Aff_entete(f,5,pos);
             Mis_jour_date(f,2);
        }
}


