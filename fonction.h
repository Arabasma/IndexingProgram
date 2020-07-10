#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <time.h>



#define max 102

/**===================================declaration des structures =============================================**/
typedef struct Tbloc
{ char tableau[1024];    // le tableau de caractère
  int num_bloc;         // le numéro du bloc
  int bloc_suiv;        // le numero du bloc suivant dans la liste
} Tbloc;


typedef struct Tbloc Buffer;  // declaration du tampon


typedef struct Entete        // structure de l'entete du fichier en mémoire centrale
{
    int nbbloc;            // le nombre total de blocs du fichier
    int nbenreg;         // le nombre d'enregistrements total du fichier
    int tete;
    int queue;           // le numéro du bloc tete
    int ind_libre;   // l'indice libre dans le bloc de la queue
    time_t date_creation;
    time_t date_modification;

}Entete;

typedef struct LOVC
{
    FILE *fich;
    Entete entete;

}LOVC;



typedef struct index_primaire
{
   long cle;
   long num_bloc;
   long position;
   char efface;
} index_primaire;



typedef struct index_secondaire
{
   char *chaine;
   struct Maillon *liste;

}index_secondaire;



typedef struct index_annee
{
   int an;
   struct Maillon *liste;
}index_annee;


typedef struct Maillon
{long val;
  struct Maillon *next ;}
  Maillon;
//*************************************************************************************************************************//
void Aff_entete (LOVC *f,int i, int val);
void Mis_jour_date (LOVC *f,int i);
int entete(LOVC *f, int i);
void  Date (LOVC *f, int i, time_t t);
LOVC *Ouvrir(char nom_fichier[50], char mode );
void LireDir (LOVC *f,Buffer *Buf, int i );
void EcrireDir ( LOVC *f, Buffer *Buf, int i );
void Fermer(LOVC *fichier);
void videur(char ch[]);
long alea (long a, long b);
void decaler (char Tableau[],int n);
char lettre(long i);
int bissextile (int an);
void matricule (char mat[7], long *cle);
void nom_prenom (char nom[31], char prenom[31]);
void date_naissance(char annee[5], char mois[11], char jour[3]);
void wilaya (char city[26]);
void grp_sg (char g_s[4]);
void grade (char g[26]);
void force_armee (char f[60]);
void region_militaire(char r_m[20]);
void chargement_initial (long N);
void indexer_cle (struct index_primaire tab[],char fich[50]);
void tri_bulles(index_primaire tab[],long taille);
void permuter (index_primaire *a , index_primaire *b);
void save_index (char fichier[20],index_primaire table[],long n);
void charger_index (char fichier[20], index_primaire table[],long n);
void allouer (Maillon **nouveau);
void aff_adr (Maillon *p , Maillon *q);
void aff_val ( Maillon *p , long valeur);
Maillon *suivant (Maillon *p);
Maillon *dernier(Maillon *p);
long valeur(Maillon *p);
void liberer  (Maillon **ancien);
void afficher (Maillon *p);
void initialiser_force (index_secondaire tableau[]);
void initialiser_region (index_secondaire tableau[]);
void initialiser_grade (index_secondaire tableau[]);
void initialiser_annee (index_annee table[]);
int indice(char mot[], index_secondaire tableau[]);
int indice_an (int mot, index_annee tableau[]);
void indexer_force (char fich[50], index_secondaire tab[],index_primaire tableau[]);
void indexer_region (char fich[50], index_secondaire tab[],index_primaire tableau[]);
void indexer_grade (char fich[50], index_secondaire tab[],index_primaire tableau[]);
void indexer_annee (char fich[50], index_annee tab[],index_primaire tableau[]);
void save_index (char fichier[20],index_primaire table[],long n);
void charger_index (char fichier[20], index_primaire table[],long n);
void charger_index (char fichier[20], index_primaire table[],long n);
void save_second (char fichier[20],index_secondaire table[],long n);
void charger_second (char fichier[20], index_secondaire table[],long n);
void save_annee (char fichier[20],index_annee table[],long n);
void charger_annee (char fichier[20], index_annee table[],long n);
void change_region (char nom_fichier[50], index_primaire tab[],long cle, char region_new[25]);
void rechercher_cle (long cle,index_primaire table[],long *ind, int *trouv, long taille);
void supprim_force (index_secondaire table[], index_primaire tab[], char force[], long taille);
void supprim_enreg (long cle, index_primaire table[], long taille);
void change_region (char nom_fichier[50], index_primaire tab[],long cle, char region_new[25]);
void afficher_enreg (char nom_fich[],index_primaire tab[],Maillon *liste);
void region_age (index_annee year[], index_secondaire region[],char reg[], int age1, int age2, char nom_fichier[],index_primaire table[]);
void afficher_categorie (char fich[],index_primaire table[],index_secondaire GR[],int choix);
void epuration (char fich[],index_primaire tab[],long *nb_enreg);
void rechercher_mat (index_primaire table[],long ind , int *trouv);
Maillon *intersection (Maillon *p , Maillon *q);
void menu();
void option(int couleurfont);
void page_1();
void cadre_aff(int l,int L,int x,int y);
void change();
void couverture();
void dessine_menu();
void dessin_tp();
void logo_esi();
void insertion_enreg (char bloc[],long cle,char fich[], index_primaire tab[]);
void Afficher (char nom_fich[50]);




#endif // FONCTION_H_INCLUDED
