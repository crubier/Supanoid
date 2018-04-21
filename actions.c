#include "supanoid.h"

void action_jouerson(char* chaine)
{
	char nomfichier[LONGCHAINE];
	sprintf(nomfichier,"mondes/%s/sons/%s.wav",repertoire,chaine+1*LONGCHAINE*sizeof(char));
	registerSound(nomfichier);
    playSound(nomfichier);
}

void action_creerobjet(char* chaine)
{
	IDENTIFIANT identifiant;
	identifiant = lireIDENTIFIANT(chaine+1*LONGCHAINE*sizeof(char));
	creercellule(nouvelobjet(),copieridentifiant(&identifiant),NULL,NULL);
}

void action_supprimerobjet(char* chaine)
{
	supprimercellule(lireOBJET(chaine+1*LONGCHAINE*sizeof(char)));
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

void action_executer(char* chaine)
{
	executerfichier(chaine+1*LONGCHAINE*sizeof(char));
}

void action_ecrire(char* chaine)
{
	printf("%s\n",chaine+1*LONGCHAINE*sizeof(char));
}

void action_modifierparametre(char* chaine)
{
	if(strcmp(chaine+1*LONGCHAINE*sizeof(char),"dt")==0)
	{
		DT=lirefloat(chaine+2*LONGCHAINE*sizeof(char));
	}

	if(strcmp(chaine+1*LONGCHAINE*sizeof(char),"sensibilite")==0)
	{
		SENSIBILITE=lirefloat(chaine+2*LONGCHAINE*sizeof(char));
	}

	if(strcmp(chaine+1*LONGCHAINE*sizeof(char),"attraction")==0)
	{
		ATTRACTION=lirefloat(chaine+2*LONGCHAINE*sizeof(char));
	}

	if(strcmp(chaine+1*LONGCHAINE*sizeof(char),"focus")==0)
	{
		if(lireOBJET(chaine+2*LONGCHAINE*sizeof(char))!=NULL)
		{
			focus=lireOBJET(chaine+2*LONGCHAINE*sizeof(char));
		}
		else
		{
			focus=fenetre;
		}
		if(focus==NULL)
		{
			focus=fenetre;
		}
	}
}
