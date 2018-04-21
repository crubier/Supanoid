#include "supanoid.h"

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
)

{
    PTROBJET pobjet;
    char* temp;
    
    pobjet=malloc(sizeof(OBJET));
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,type);
    (*pobjet).type=temp;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,nom);
    (*pobjet).nom=temp;
    
    (*pobjet).identifiant=identifiant;

    (*pobjet).position=position;
    (*pobjet).vitesse=vitesse;
    (*pobjet).acceleration=acceleration;
    
    (*pobjet).forme=forme;
    (*pobjet).dimensions=dimensions;
    (*pobjet).masse=masse;
    (*pobjet).frottement=frottement;
    (*pobjet).rebondissement=rebondissement;
    (*pobjet).solidite=solidite;
    (*pobjet).attraction=attraction;
    (*pobjet).agressivite=agressivite;

    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,fils_type);
    (*pobjet).fils_type=temp;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,fils_nom);
    (*pobjet).fils_nom=temp;

    (*pobjet).fils_identifiant=fils_identifiant;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,frere_type);
    (*pobjet).frere_type=temp;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,frere_nom);
    (*pobjet).frere_nom=temp;

    (*pobjet).frere_identifiant=frere_identifiant;

    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,graphique);
    (*pobjet).graphique=temp;
    
    (*pobjet).couleur=couleur;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,son_creation);
    (*pobjet).son_creation=temp;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,son_choc);
    (*pobjet).son_choc=temp;
    
    temp=malloc(LONGUEURMAXCHAINE*sizeof(char));
    verifierpointeur(temp);
    strcpy(temp,son_destruction);
    (*pobjet).son_destruction=temp;
    
    return pobjet;
}

PTROBJET nouvelobjet(void)
{
    PTROBJET res;
    res=creerobjet
    (
  		"INCONNU",
        "INCONNU",
  		0,

        vecteur(0,0),
 		vecteur(0,0),
 		vecteur(0,0),

 		INCONNUE,
 		vecteur(0,0),
 		1,
 		1,
 		1,
 		1,
 		0,
 		0,

 		"INCONNU",
 		"INCONNU",
 		0,
 		
 		"INCONNU",
 		"INCONNU",
 		0,
 		
 		"INCONNU",
        NOIR,
        "INCONNU",
        "INCONNU",
        "INCONNU"
    );
    return res;
}

void verifierpointeur(char* p)
{
    if(p == NULL)
    {
        printf("\nErreur d allocation memoire\n");
        exit (1);
    }
}
