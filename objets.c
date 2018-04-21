#include "supanoid.h"



OBJET creerobjet
(
        char* nom,
  		int identifiant,

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
        COLOR couleur,
 		FORME forme
)
{
    PTROBJET objet;
    char* temp;
    
    objet=malloc(sizeof(OBJET));
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    strcpy(temp,nom);
    (*objet).nom=temp;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    strcpy(temp,graphique);
    (*objet).graphique=temp;
    
    (*objet).contenu=contenu;
    (*objet).position=position;
    (*objet).vitesse=vitesse;
    (*objet).acceleration=acceleration;
    (*objet).dimensions=dimensions;
    (*objet).masse=masse;
    (*objet).solidite=solidite;
    (*objet).rebondissement=rebondissement;
    (*objet).frottement=frottement;
    (*objet).forme=forme;
    (*objet).identifiant=identifiant;
    (*objet).couleur=couleur;
    
    return *objet;
}
