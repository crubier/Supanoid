#include "supanoid.h"

void action_jouerson(char* chaine)
{
	char nomfichier[LONGCHAINE];
	sprintf(nomfichier,"%s/sons/%s.wav",repertoire,chaine+1*LONGCHAINE*sizeof(char));
	registerSound(nomfichier);
    playSound(nomfichier);
}

void action_creerobjet(char* chaine)
{
	nouvellecellule();

	(*(*dernierecellule()).identifiant).type=creerchaine(chaine+1*LONGCHAINE*sizeof(char));
	(*(*dernierecellule()).identifiant).nom=creerchaine(chaine+2*LONGCHAINE*sizeof(char));
	(*(*dernierecellule()).identifiant).numero=lireint(chaine+3*LONGCHAINE*sizeof(char));

}

void action_modifierpropriete(char* chaine)
{
	entrerpropriete(lireOBJET(chaine+1*LONGCHAINE*sizeof(char)),chaine+2*LONGCHAINE*sizeof(char),chaine+3*LONGCHAINE*sizeof(char));
}

void action_initialiser(char* chaine)
{
	cloture();
	origineliste=NULL;
	executerfichier("monde");
    initialisation();
}

void action_affichernoms(char* chaine)
{
	int i;
	int couche;

	couche=lireint(chaine+1*LONGCHAINE*sizeof(char));

	for(i=1;i<=nombrecellules();i++)
	{
		if(((*(*cellulenumero(i)).element).couche & couche) !=0)
		(*(*cellulenumero(i)).element).texte=ecrireIDENTIFIANT(*(*cellulenumero(i)).identifiant);
	}
}

void action_cachernoms(char* chaine)
{
	int i;
	int couche;
	
	couche=lireint(chaine+1*LONGCHAINE*sizeof(char));

	for(i=1;i<=nombrecellules();i++)
	{
		if(((*(*cellulenumero(i)).element).couche & couche) !=0)
		(*(*cellulenumero(i)).element).texte=creerchaine("INCONNU");
	}
}
