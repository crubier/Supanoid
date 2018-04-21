#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "graphic.h"
#include "key.h"

#define LONGUEURMAXCHAINE 100
#define DT 0.002

typedef enum {RECTANGLE, CERCLE, INCONNUE} FORME;

typedef struct coordstruct
{
 		float x;
		float y;
} COORD, *PTRCOORD;

typedef struct objetstruct
{
        char* nom;
  		int identifiant;
  		char* type;

        COORD position;
 		COORD vitesse;
 		COORD acceleration;

 		COORD dimensions;
 		float solidite;
 		float masse;
 		float frottement;
 		float rebondissement;

 		struct objetstruct* contenu;
 		char* graphique;
        COULEUR couleur;
 		FORME forme;
 		
} OBJET, *PTROBJET;

typedef struct cellulestruct
{
 		struct objetstruct* element; 
		struct cellulestruct* suivant; 
		struct cellulestruct* precedent;
} CELLULE, *PTRCELLULE;


/*VARIABLES GLOBALES*/
OBJET fenetre;
PTRCELLULE origineliste;


/*PHYSIQUE*/
void mouvement(PTROBJET objet);
void mouvements(void);
OBJET positionsuivante(OBJET objet);
void rebond(PTROBJET objeta, PTROBJET objetb, COORD normale);
COORD collision(OBJET objeta, OBJET objetb);
void interactions(void);

/*GRAPHIQUES*/
void effacer(void);
void dessin(void);
void dessiner(OBJET objet);
void initialisationgraphiques(void);
void indiquer(COORD a);
void decrire(OBJET a);

/* GEOMETRIE*/
COORD vecteur(float x, float y);
COORD somme(COORD a, COORD b);
COORD oppose(COORD a);
COORD difference(COORD a, COORD b);
COORD inverse(COORD a);
COORD multiplication(COORD a, COORD b);
COORD multiplicationscalaire(COORD a, float k);
float scalaire(COORD a, COORD b);
COORD normalisation(COORD a);
float distance(COORD a, COORD b);
float norme(COORD a);
float distanceaxe(COORD a, COORD b, COORD axe);
COORD arrondi(COORD a);

/*OBJETS*/
PTROBJET creerobjet
(
        char* nom,
  		int identifiant,
  		char* type,

        COORD position,
 		COORD vitesse,
 		COORD acceleration,

 		COORD dimensions,
 		float solidite,
 		float masse,
 		float frottement,
 		float rebondissement,

 		PTROBJET contenu,
 		char* graphique,
        COULEUR couleur,
 		FORME forme
);


/*LISTES*/
PTRCELLULE creercellule(PTROBJET pobjet);
PTRCELLULE dernierecellule(void);
BOOLEAN ajoutercellule(PTROBJET pobjet);
BOOLEAN liercellules(PTRCELLULE cellulea, PTRCELLULE celluleb);
BOOLEAN verifiercellules(PTRCELLULE cellulea, PTRCELLULE celluleb);
PTRCELLULE rechercher(char* nom, int identifiant);
PTRCELLULE elementnumero(int i);

/*FICHIERS*/
BOOLEAN entrerpropriete(FILE* fichier, PTROBJET objet, char* propriete);
PTROBJET lireobjet(char* type);
int conversionFORME(char* forme);
int conversionCOLOR(char* couleur);
BOOLEAN liremonde(char* monde);

