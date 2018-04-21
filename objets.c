#include "supanoid.h"

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
)

{
    PTROBJET pobjet;
    char* temp;
    
    pobjet=malloc(sizeof(OBJET));
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    strcpy(temp,nom);
    (*pobjet).nom=temp;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    strcpy(temp,graphique);
    (*pobjet).graphique=temp;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    strcpy(temp,type);
    (*pobjet).type=temp;
    
    (*pobjet).contenu=contenu;
    (*pobjet).position=position;
    (*pobjet).vitesse=vitesse;
    (*pobjet).acceleration=acceleration;
    (*pobjet).dimensions=dimensions;
    (*pobjet).masse=masse;
    (*pobjet).solidite=solidite;
    (*pobjet).rebondissement=rebondissement;
    (*pobjet).frottement=frottement;
    (*pobjet).forme=forme;
    (*pobjet).identifiant=identifiant;
    (*pobjet).couleur=couleur;
    
    return pobjet;
}
