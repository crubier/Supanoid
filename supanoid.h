#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "graphic.h"
#include "key.h"

typedef enum {RECTANGLE, CERCLE} FORME;

typedef struct coordstruct
{
 		float x;
		float y;
} COORD, *PTRCOORD;

typedef struct objetstruct
{
        char* nom;
        COORD position;
 		COORD vitesse;
 		COORD acceleration;
 		COORD dimensions;
 		char* graphique;
 		struct objetstruct* contenu;
 		float solidite;
 		float masse;
 		float frottement;
 		float rebondissement;
 		int identifiant;
 		FORME forme;
 		
} OBJET, *PTROBJET;

typedef struct cellulestruct
{
 		OBJET element; 
		struct cellulestruct* suivant; 
		struct cellulestruct* precedent;
} CELLULE, *PTRCELLULE;


/*PHYSIQUE*/
void mouvement(PTROBJET objet);
OBJET positionsuivante(OBJET objet);
void rebond(PTROBJET objeta, PTROBJET objetb, COORD normale);
COORD collision(OBJET objeta, OBJET objetb);

/*GRAPHIQUES*/
void dessiner(OBJET objet);
void effacer(OBJET objet);
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
OBJET creerobjet
(
    char* nom,
   	int identifiant,
    COORD position,
 	COORD vitesse,
 	COORD acceleration,
 	COORD dimensions,
 	char* graphique,
 	PTROBJET contenu,
 	float solidite,
 	float masse,
 	float frottement,
 	float rebondissement,
 	FORME forme
);
