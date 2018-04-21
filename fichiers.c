#include "supanoid.h"

PTROBJET lireobjet(char* type)
{
	PTROBJET pobjet;
	char nom[LONGUEURMAXCHAINE];
    char propriete[LONGUEURMAXCHAINE];
	FILE* fichier;

    pobjet=creerobjet(type,0,type,vecteur(0,0),vecteur(0,0),vecteur(0,0),vecteur(0,0),1,1,0,1,NULL,"AUCUN",NOIR,RECTANGLE);
    strcpy(nom,"objets/");
    strcat(nom,type);
    strcat(nom,".obj");
	fichier=fopen(nom,"r");

	if (fichier==NULL)
	{
		printf("Impossible d'ouvrir le fichier de description du type d'objet %s",type);
	}
	else
	{
        while(fscanf(fichier," %s =",propriete)!=EOF && strcmp(propriete,"type")!=0)
        {
            fseek(fichier,1,SEEK_CUR);
            if(entrerpropriete(fichier,pobjet,propriete)==FALSE)printf("Erreur sur la propriete %s \n",propriete);
        }
    
		fclose(fichier);
	}
	return pobjet;
}

BOOLEAN entrerpropriete(FILE* fichier, PTROBJET pobjet, char* propriete)
{
    char temp[LONGUEURMAXCHAINE];
    char* temp1;
   
    if(strcmp(propriete,"identifiant")==0)
    {
        fscanf(fichier," %d ;",&(*pobjet).identifiant);
        return TRUE;
    }
    
    if(strcmp(propriete,"position.x")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).position.x);
        return TRUE;
    }
    if(strcmp(propriete,"position.y")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).position.y);
        return TRUE;
    }
    
    if(strcmp(propriete,"vitesse.x")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).vitesse.x);
        return TRUE;
    }
    if(strcmp(propriete,"vitesse.y")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).vitesse.y);
        return TRUE;
    }
    
    if(strcmp(propriete,"acceleration.x")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).acceleration.x);
        return TRUE;
    }
    if(strcmp(propriete,"acceleration.y")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).acceleration.y);
        return TRUE;
    }
    
    if(strcmp(propriete,"dimensions.x")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).dimensions.x);
        return TRUE;
    }
    if(strcmp(propriete,"dimensions.y")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).dimensions.y);
        return TRUE;
    }
    
    if(strcmp(propriete,"solidite")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).solidite);
        return TRUE;
    }
    
    if(strcmp(propriete,"masse")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).masse);
        return TRUE;
    }
    
    if(strcmp(propriete,"frottement")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).frottement);
        return TRUE;
    }
    
    if(strcmp(propriete,"rebondissement")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).rebondissement);
        return TRUE;
    }
    
    if(strcmp(propriete,"graphique")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).graphique=temp1;
        return TRUE;
    }
    
    if(strcmp(propriete,"nom")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).nom=temp1;
        return TRUE;
    }

    if(strcmp(propriete,"forme")==0)
    {
        fscanf(fichier," %s ;",temp);
        (*pobjet).forme=conversionFORME(temp);
        return TRUE;
    }
    
    if(strcmp(propriete,"couleur")==0)
    {
        fscanf(fichier," %s ;",temp);
        (*pobjet).couleur=conversionCOLOR(temp);
        return TRUE;
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

BOOLEAN liremonde(char* monde)
{
	PTROBJET pobjet;
	CELLULE cellule;
	char nom[LONGUEURMAXCHAINE];
	char type[LONGUEURMAXCHAINE];
    char propriete[LONGUEURMAXCHAINE];
	FILE* fichier;

    strcpy(nom,"mondes/");
    strcat(nom,monde);
    strcat(nom,".niv");
	fichier=fopen(nom,"r");

	if (fichier==NULL)
	{
		printf("Impossible d'ouvrir le fichier de description du monde %s",monde);
		return FALSE;
	}
	else
	{
        
        while(fscanf(fichier," %s =",propriete)!=EOF)
        {
            fseek(fichier,1,SEEK_CUR);
            if(strcmp(propriete,"type")==0)
            {
                fscanf(fichier," %s ;",type);
                printf("Ajout objet de type %s :\n",type);
                decrire(*lireobjet(type));
                pobjet=lireobjet(type);
                ajoutercellule(pobjet);
                printf("Ajout objet de type %s termine ! \n\n",(*(*dernierecellule()).element).type);
            }
            else
            {
                printf("Ajout propriete %s :\n",type);
                if(entrerpropriete(fichier,(*dernierecellule()).element,propriete)==FALSE)printf("Erreur sur la propriete %s \n",propriete);
            }
        }
        
        //objet=creerobjet(type,0,type,vecteur(0,0),vecteur(0,0),vecteur(0,0),vecteur(0,0),1,1,0,1,NULL,"AUCUN",BLANC,CERCLE);

		fclose(fichier);
	}
	return TRUE;
}
