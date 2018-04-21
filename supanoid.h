#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "graphic.h"
#include "key.h"

#define LONGUEURMAXCHAINE 100
#define ATTRACTION 0.1
#define SENSIBILITE 0.2

typedef enum {INCONNUE, RECTANGLE, CERCLE} FORME;

typedef struct coordstruct
{
 		float x;
		float y;
} COORD, *PTRCOORD;

typedef struct objetstruct
{
  		char* type;
        char* nom;
  		int identifiant;

        COORD position;
 		COORD vitesse;
 		COORD acceleration;

 		FORME forme;
 		COORD dimensions;
 		float masse;
 		float frottement;
 		float rebondissement;
 		float solidite;
 		float attraction;
 		float agressivite;

 		char* fils_type;
 		char* fils_nom;
 		int fils_identifiant;
 		
 		char* frere_type;
 		char* frere_nom;
 		int frere_identifiant;
 		
 		char* graphique;
        COULEUR couleur;
        char* son_creation;
        char* son_choc;
        char* son_destruction;

 		
} OBJET, *PTROBJET;

typedef struct cellulestruct
{
 		struct objetstruct* element; 
		struct cellulestruct* suivant; 
		struct cellulestruct* precedent;
} CELLULE, *PTRCELLULE;


/*VARIABLES GLOBALES*/
OBJET fenetre;
OBJET fenetrepause;
PTRCELLULE originelisteactifs;
PTRCELLULE originelisteinactifs;
BOOLEAN erreur;
float DT;

/*PHYSIQUE*/
void pause(void);
void mouvement(PTROBJET objet);
void mouvements(void);
OBJET positionsuivante(OBJET objet);
void rebond(PTROBJET objeta, PTROBJET objetb);
void gravitation(PTROBJET objeta, PTROBJET objetb);
void frottement(PTROBJET objet);
void disparition(PTRCELLULE pcellule);
COORD normalecontact(OBJET objeta, OBJET objetb);
COORD positionrelative(OBJET objeta, OBJET objetb);
void interactions(void);

/*GRAPHIQUES*/
void effacer(void);
void dessin(void);
void dessiner(OBJET objet);
void initialisationgraphiques(void);
void indiquer(COORD a);
void decrire(OBJET a);
void identifier(OBJET a);
void jouerson(char* son);

/* GEOMETRIE*/
COORD vecteur(float x, float y);
COORD somme(COORD a, COORD b);
COORD oppose(COORD a);
COORD difference(COORD a, COORD b);
COORD inverse(COORD a);
COORD multiplication(COORD a, COORD b);
COORD multiplicationscalaire(COORD a, float k);
float produitscalaire(COORD a, COORD b);
float total(COORD a);
COORD normalisation(COORD a);
float distance(COORD a, COORD b);
float norme(COORD a);
float distanceaxe(COORD a, COORD b, COORD axe);
COORD arrondi(COORD a);

/*OBJETS*/
PTROBJET creerobjet
(
  		char* type,
        char* nom,
  		int identifiant,

        COORD position,
 		COORD vitesse,
 		COORD acceleration,

 		FORME forme,
 		COORD dimensions,
 		float masse,
 		float frottement,
 		float rebondissement,
 		float solidite,
 		float attraction,
 		float agressivite,

 		char* fils_type,
 		char* fils_nom,
 		int fils_identifiant,
 		
 		char* frere_type,
 		char* frere_nom,
 		int frere_identifiant,
 		
 		char* graphique,
        COULEUR couleur,
        char* son_creation,
        char* son_choc,
        char* son_destruction
);
PTROBJET nouvelobjet(void);
void verifierpointeur(char* p);

/*LISTES*/
PTRCELLULE creercellule(PTROBJET pobjet);
PTRCELLULE premierecellule(PTRCELLULE origineliste);
PTRCELLULE dernierecellule(PTRCELLULE origineliste);
void ajoutercellule(PTROBJET pobjet, PTRCELLULE* porigineliste);
void supprimercellule(PTRCELLULE pcellule, PTRCELLULE* porigineliste);
void deplacercellule(PTRCELLULE pcellule, PTRCELLULE* poriginelistea, PTRCELLULE* poriginelisteb);
BOOLEAN liercellules(PTRCELLULE cellulea, PTRCELLULE celluleb);
BOOLEAN verifiercellules(PTRCELLULE cellulea, PTRCELLULE celluleb);
PTRCELLULE rechercher(char* type, char* nom, int identifiant, PTRCELLULE origineliste);
PTRCELLULE elementnumero(int i);

/*FICHIERS*/
PTROBJET lireobjet(char* type);
BOOLEAN liremonde(char* monde);
BOOLEAN entrerpropriete(FILE* fichier, PTROBJET pobjet, char* propriete);
int conversionFORME(char* forme);
int conversionCOLOR(char* couleur);
