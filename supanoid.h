#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <string.h>

#include "graphic.h"

#define LONGCHAINE 256
#define NBPARAM 32
#define ATTRACTION 0.1
#define VIDE ""

typedef enum {INCONNUE, RECTANGLE, CERCLE, RAQUETTE} FORME;
typedef enum { BLANC, NOIR, ROUGE, BLEU, VERT, JAUNE, CYANFR, GRIS, MAGENTAFR, ORANGEFR, ROSE } COULEUR;

typedef struct coordstruct
{
 		float x;
		float y;
} COORD, *PTRCOORD;

typedef struct identifiantstruct
{
      	char* type;
        char* nom;
  		int numero;
} IDENTIFIANT, *PTRIDENTIFIANT;

typedef struct objetstruct
{

        COORD position;
 		COORD vitesse;
 		COORD acceleration;
 		int couche;

 		FORME forme;
 		COORD dimensions;
 		float masse;
 		float frottement;
 		float rebondissement;
 		float solidite;
 		float attraction;
 		float agressivite;

 		struct identifiantstruct* fils;
 		struct identifiantstruct* frere;

 		char* graphique;
        char* son;
        COULEUR couleur;

 		
} OBJET, *PTROBJET;

typedef struct cellulestruct
{
 		struct objetstruct* element; 
 		struct identifiantstruct* identifiant;
		struct cellulestruct* suivant; 
		struct cellulestruct* precedent;
} CELLULE, *PTRCELLULE;


/*VARIABLES GLOBALES*/
PTRCELLULE origineliste;
PTRCELLULE fenetre;
PTRCELLULE raquette;
char erreur[LONGCHAINE];
int fini;
FILE* journal;
char repertoire[LONGCHAINE];
float DT;
float SENSIBILITE;

/*ACTIONS*/
void action_jouerson(char* chaine);
void action_creerobjet(char* chaine);
void action_modifierpropriete(char* chaine);

/*GEOMETRIE*/
COORD vecteur(float x, float y);
COORD somme(COORD a, COORD b);
COORD oppose(COORD a);
COORD difference(COORD a, COORD b);
COORD inverse(COORD a);
COORD multiplication(COORD a, COORD b);
COORD multiplicationscalaire(COORD a, float k);
float produitscalaire(COORD a, COORD b);
COORD normalisation(COORD a);
float distance(COORD a, COORD b);
float norme(COORD a);
float total(COORD a);
float distanceaxe(COORD a, COORD b, COORD axe);
COORD arrondi(COORD a);

/*GRAPHIQUE*/
void effacer(void);
void dessin(void);
void clavier(void);
void dessiner(PTRCELLULE pcellule);
void decrireLISTE(void);
void decrireCELLULE(PTRCELLULE pcellule);
void decrireLISTEdetail(void);
void initialisation(void);
void cloture(void);
void rapportererreur(void);

/*MANIPULATIONS*/
PTROBJET creerobjet
(
        COORD position,
 		COORD vitesse,
 		COORD acceleration,
 		int couche,

 		FORME forme,
 		COORD dimensions,
 		float masse,
 		float frottement,
 		float rebondissement,
 		float attraction,
 		float solidite,
 		float agressivite,

        PTRIDENTIFIANT fils,		
        PTRIDENTIFIANT frere,
 		
 		char* graphique,
        char* son,
        COULEUR couleur
);
PTROBJET copierobjet(PTROBJET pobjet);
PTROBJET nouvelobjet(void);

PTRIDENTIFIANT creeridentifiant
(
 		char* type,
        char* nom,
        int numero
);
PTRIDENTIFIANT copieridentifiant(PTRIDENTIFIANT pidentifiant);
PTRIDENTIFIANT nouvelidentifiant(void);

PTRCELLULE creercellule
(
    PTROBJET element, 
 	PTRIDENTIFIANT identifiant,
	PTRCELLULE suivant,
	PTRCELLULE precedent
);
PTRCELLULE copiercellule(PTRCELLULE pcellule);
PTRCELLULE nouvellecellule(void);

void liercellules(PTRCELLULE pcellulea, PTRCELLULE pcelluleb);
void verifiercellules(PTRCELLULE pcellulea, PTRCELLULE pcelluleb);
void verifierpointeur(char* p);

PTRCELLULE premierecellule(void);
PTRCELLULE dernierecellule(void);
PTRCELLULE rechercher(PTRIDENTIFIANT pidentifiant);
PTRCELLULE cellulenumero(int i);
int nombrecellules(void);
int compareridentifiants(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb);

char* creerchaine(char* chaine);
char* lireligne(char* lignecommande);

int lireint(char* chaine);
char* ecrireint(int a);

float lirefloat(char* chaine);
char* ecrirefloat(float a);

COORD lireCOORD(char* chaine);
char* ecrireCOORD(COORD a);

FORME lireFORME(char* chaine);
char* ecrireFORME(FORME a);

COULEUR lireCOULEUR(char* chaine);
char* ecrireCOULEUR(COULEUR a);

IDENTIFIANT lireIDENTIFIANT(char* chaine);
char* ecrireIDENTIFIANT(IDENTIFIANT a);

char* ecrireLISTE(void);
PTRCELLULE lireOBJET(char* chaine);
char* ecrireOBJET(OBJET a);

void executercommande(char* lignecommande);
void executerfichier(char* parametres);
void entrerpropriete(PTRCELLULE pcellule, char* propriete, char* valeur);

/*PHYSIQUE*/
void pause(void);
void mouvement(PTROBJET objet);
void mouvements(void);
OBJET positionsuivante(OBJET objet);
void rebond(PTRCELLULE pcellulea, PTRCELLULE pcelluleb);
void gravitation(PTRCELLULE pcellulea, PTRCELLULE pcelluleb);
void frottement(PTRCELLULE pcellule);
void degradation(PTRCELLULE pcellule);
COORD normalecontact(OBJET objeta, OBJET objetb);
COORD positionrelative(OBJET objeta, OBJET objetb);
void interactions(void);
