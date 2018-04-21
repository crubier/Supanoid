#include "supanoid.h"

OBJET lireobjet(char* nomobjet)
{
	OBJET objet;
	char nom[LONGUEURMAXCHAINE];
    char valeur[LONGUEURMAXCHAINE];
    char propriete[LONGUEURMAXCHAINE];
	FILE* fichier;

    objet=creerobjet(nom,0,vecteur(0,0),vecteur(0,0),vecteur(0,0),vecteur(0,0),1,1,0,1,NULL,"",BLANC,CERCLE);
    strcpy(nom,"objets/");
    strcat(nom,nomobjet);
    strcat(nom,".obj");
	fichier=fopen(nom,"r");

	if (fichier==NULL)
	{
		printf("Impossible d'ouvrir le fichier de description de l'objet %s",nomobjet);
	}
	else
	{
        while(fscanf(fichier," %s =",propriete)!=EOF)
        {
            fseek(fichier,1,SEEK_CUR);
            entrerpropriete(fichier,&objet,propriete);
        }
    
		fclose(fichier);
	}
	return objet;
}

BOOLEAN entrerpropriete(FILE* fichier, PTROBJET objet, char* propriete)
{
    char temp[LONGUEURMAXCHAINE];
    char* temp1;
   
    if(strcmp(propriete,"identifiant")==0)
    {
        fscanf(fichier," %d ;",&(*objet).identifiant);
    }
    
    if(strcmp(propriete,"position.x")==0)
    {
        fscanf(fichier," %f ;",&(*objet).position.x);
    }
    if(strcmp(propriete,"position.y")==0)
    {
        fscanf(fichier," %f ;",&(*objet).position.y);
    }
    
    if(strcmp(propriete,"vitesse.x")==0)
    {
        fscanf(fichier," %f ;",&(*objet).vitesse.x);
    }
    if(strcmp(propriete,"vitesse.y")==0)
    {
        fscanf(fichier," %f ;",&(*objet).vitesse.y);
    }
    
    if(strcmp(propriete,"acceleration.x")==0)
    {
        fscanf(fichier," %f ;",&(*objet).acceleration.x);
    }
    if(strcmp(propriete,"acceleration.y")==0)
    {
        fscanf(fichier," %f ;",&(*objet).acceleration.y);
    }
    
    if(strcmp(propriete,"dimensions.x")==0)
    {
        fscanf(fichier," %f ;",&(*objet).dimensions.x);
    }
    if(strcmp(propriete,"dimensions.y")==0)
    {
        fscanf(fichier," %f ;",&(*objet).dimensions.y);
    }
    
    if(strcmp(propriete,"solidite")==0)
    {
        fscanf(fichier," %f ;",&(*objet).solidite);
    }
    
    if(strcmp(propriete,"masse")==0)
    {
        fscanf(fichier," %f ;",&(*objet).masse);
    }
    
    if(strcmp(propriete,"frottement")==0)
    {
        fscanf(fichier," %f ;",&(*objet).frottement);
    }
    
    if(strcmp(propriete,"rebondissement")==0)
    {
        fscanf(fichier," %f ;",&(*objet).rebondissement);
    }
    
    if(strcmp(propriete,"graphique")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        strcpy((*objet).graphique,temp);
    }

    if(strcmp(propriete,"forme")==0)
    {
        fscanf(fichier," %s ;",temp);
        (*objet).forme=conversionFORME(temp);
    }
    
    if(strcmp(propriete,"couleur")==0)
    {
        fscanf(fichier," %s ;",temp);
        (*objet).couleur=conversionCOLOR(temp);
    }

    return FALSE;    
}

int conversionFORME(char* forme)
{
    if(strcmp(forme,"CERCLE")==0)return CERCLE;
    if(strcmp(forme,"RECTANGLE")==0)return RECTANGLE;
    return INCONNUE;
}

int conversionCOLOR(char* couleur)
{
    if(strcmp(couleur,"BLANC")==0)return BLANC;
    if(strcmp(couleur,"NOIR")==0)return NOIR;
    if(strcmp(couleur,"ROUGE")==0)return ROUGE;
    if(strcmp(couleur,"BLEU")==0)return BLEU;
    if(strcmp(couleur,"VERT")==0)return VERT;
    if(strcmp(couleur,"JAUNE")==0)return JAUNE;
    if(strcmp(couleur,"CYAN")==0)return CYAN;
    if(strcmp(couleur,"GRIS")==0)return GRIS;
    if(strcmp(couleur,"MAGENTA")==0)return MAGENTA;
    if(strcmp(couleur,"ORANGE")==0)return ORANGE;
    if(strcmp(couleur,"ROSE")==0)return ROSE;
    return BLANC;
}
