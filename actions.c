#include "supanoid.h"

void action_jouerson(char* chaine)
{
	registerSound(chaine+1*LONGCHAINE*sizeof(char));
    playSound(chaine+1*LONGCHAINE*sizeof(char));
}

void action_creerobjet(char* chaine)
{
	nouvellecellule();

//	printf("type : \"%s\"\n",chaine+1*LONGCHAINE*sizeof(char));
	(*(*dernierecellule()).identifiant).type=creerchaine(chaine+1*LONGCHAINE*sizeof(char));
//	printf("nom : \"%s\"\n",chaine+2*LONGCHAINE*sizeof(char));
	(*(*dernierecellule()).identifiant).nom=creerchaine(chaine+2*LONGCHAINE*sizeof(char));
//	printf("numero : \"%s\"\n",chaine+3*LONGCHAINE*sizeof(char));
	(*(*dernierecellule()).identifiant).numero=lireint(chaine+3*LONGCHAINE*sizeof(char));

}

void action_modifierpropriete(char* chaine)
{
	entrerpropriete(lireOBJET(chaine+1*LONGCHAINE*sizeof(char)),chaine+2*LONGCHAINE*sizeof(char),chaine+3*LONGCHAINE*sizeof(char));
}
