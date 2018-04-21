#include "supanoid.h"

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
)
{
    PTROBJET adresse;
    char* temp;
    
    adresse=malloc(sizeof(OBJET));
    
    temp=malloc(100*sizeof(char));
    strcpy(temp,nom);
    (*adresse).nom=temp;
    
    temp=malloc(100*sizeof(char));
    strcpy(temp,graphique);
    (*adresse).graphique=temp;
    
    (*adresse).contenu=contenu;
    (*adresse).position=position;
    (*adresse).vitesse=vitesse;
    (*adresse).acceleration=acceleration;
    (*adresse).dimensions=dimensions;
    (*adresse).masse=masse;
    (*adresse).solidite=solidite;
    (*adresse).rebondissement=rebondissement;
    (*adresse).frottement=frottement;
    (*adresse).forme=forme;
    (*adresse).identifiant=identifiant;
    
    return *adresse;
}
