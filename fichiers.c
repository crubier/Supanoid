#include "supanoid.h"

PTROBJET lireobjet(char* type)
{
	PTROBJET pobjet;
	char nom[LONGUEURMAXCHAINE];
    char propriete[LONGUEURMAXCHAINE];
	FILE* fichier;

    pobjet=nouvelobjet();
    (*pobjet).type = type;
    strcpy(nom,"objets/");
    strcat(nom,type);
    strcat(nom,".obj");
	fichier=fopen(nom,"r");

	if (fichier==NULL)
	{
		printf("Impossible d'ouvrir le fichier de description du type d'objet %s \n",type);
		erreur=TRUE;
	}
	else
	{
        printf("\nLecture du fichier de description du type d'objet %s \n",type);
        while(fscanf(fichier," %s =",propriete)!=EOF)
        {
            fseek(fichier,1,SEEK_CUR);
            printf("Ajout propriete %s a l objet %s ( valeur : ",propriete, type );
            if(entrerpropriete(fichier,pobjet,propriete)==FALSE)
            {
                printf("Erreur sur la propriete %s ",propriete);
                erreur=TRUE;
            }             
            printf(" )\n");
        }
    
		fclose(fichier);
	}
	return pobjet;
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
		printf("Impossible d'ouvrir le fichier de description du monde %s !\n",monde);
		erreur=TRUE;
		return FALSE;
	}
	else
	{
        
        printf("\n============================================\n\nLecture du monde %s :\n",monde);
        
        while(fscanf(fichier," %s =",propriete)!=EOF)
        {
            fseek(fichier,1,SEEK_CUR);
            if(strcmp(propriete,"type")==0)
            {
                fscanf(fichier," %s ;",type);
                printf("\n============================================\n\nAjout objet de type %s :\n",type);
                pobjet=lireobjet(type);
                ajoutercellule(pobjet,&originelisteactifs);
                printf("Creation objet de type %s termine ! \n",(*(*dernierecellule(originelisteactifs)).element).type);
            }
            else
            {
                printf("Ajout propriete %s a l objet %s ( valeur : ",propriete, type );
                if(entrerpropriete(fichier,(*dernierecellule(originelisteactifs)).element,propriete)==FALSE)
                {
                    printf("Erreur sur la propriete %s ",propriete);
                    erreur=TRUE;
                }
                printf(" )\n");
            }
        }
        
        printf("\nLecture du monde %s terminee !\n\n============================================\n\n",monde);
		fclose(fichier);
	}
	return TRUE;
}

BOOLEAN entrerpropriete(FILE* fichier, PTROBJET pobjet, char* propriete)
{
    char temp[LONGUEURMAXCHAINE];
    char* temp1;
   
    if(strcmp(propriete,"type")==0)
    {
        fscanf(fichier," %s ;",temp);
        (*pobjet)=(*lireobjet(temp));
        printf("%s",temp);
        return TRUE;
    }
   
    if(strcmp(propriete,"nom")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).nom=temp1;
        printf("%s",temp);
        return TRUE;
    }
    
    if(strcmp(propriete,"identifiant")==0)
    {
        fscanf(fichier," %d ;",&(*pobjet).identifiant);
        printf("%d",(*pobjet).identifiant);
        return TRUE;
    }
    
    if(strcmp(propriete,"position")==0)
    {
        fscanf(fichier," ( %f , %f ) ;",&(*pobjet).position.x,&(*pobjet).position.y);
        indiquer((*pobjet).position);
        return TRUE;
    }
    
    if(strcmp(propriete,"vitesse")==0)
    {
        fscanf(fichier," ( %f , %f ) ;",&(*pobjet).vitesse.x,&(*pobjet).vitesse.y);
        indiquer((*pobjet).vitesse);
        return TRUE;
    }
    
    if(strcmp(propriete,"acceleration")==0)
    {
        fscanf(fichier," ( %f , %f ) ;",&(*pobjet).acceleration.x,&(*pobjet).acceleration.y);
        indiquer((*pobjet).acceleration);
        return TRUE;
    }
    
    if(strcmp(propriete,"forme")==0)
    {
        fscanf(fichier," %s ;",temp);
        (*pobjet).forme=conversionFORME(temp);
        printf("%d",(*pobjet).forme);
        return TRUE;
    }
    
    if(strcmp(propriete,"dimensions")==0)
    {
        fscanf(fichier," ( %f , %f ) ;",&(*pobjet).dimensions.x,&(*pobjet).dimensions.y);
        indiquer((*pobjet).dimensions);
        return TRUE;
    }
       
    if(strcmp(propriete,"masse")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).masse);
        printf("%g",(*pobjet).masse);
        return TRUE;
    }
    
    if(strcmp(propriete,"frottement")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).frottement);
        printf("%g",(*pobjet).frottement);
        return TRUE;
    }
    
    if(strcmp(propriete,"rebondissement")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).rebondissement);
        printf("%g",(*pobjet).rebondissement);
        return TRUE;
    }
    
    if(strcmp(propriete,"solidite")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).solidite);
        printf("%g",(*pobjet).solidite);
        return TRUE;
    }
    
    if(strcmp(propriete,"attraction")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).attraction);
        printf("%g",(*pobjet).attraction);
        return TRUE;
    }
    
    if(strcmp(propriete,"agressivite")==0)
    {
        fscanf(fichier," %f ;",&(*pobjet).agressivite);
        printf("%g",(*pobjet).agressivite);
        return TRUE;
    }
    
    if(strcmp(propriete,"fils_type")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).fils_type=temp1;
        printf("%s",temp);
        return TRUE;
    }
    
    if(strcmp(propriete,"fils_nom")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).fils_nom=temp1;
        printf("%s",temp);
        return TRUE;
    }
    
    if(strcmp(propriete,"fils_identifiant")==0)
    {
        fscanf(fichier," %d ;",&(*pobjet).fils_identifiant);
        printf("%d",(*pobjet).fils_identifiant);
        return TRUE;
    }
    
    
    if(strcmp(propriete,"frere_type")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).frere_type=temp1;
        printf("%s",temp);
        return TRUE;
    }
    
    if(strcmp(propriete,"frere_nom")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).frere_nom=temp1;
        printf("%s",temp);
        return TRUE;
    }
    
    if(strcmp(propriete,"frere_identifiant")==0)
    {
        fscanf(fichier," %d ;",&(*pobjet).frere_identifiant);
        printf("%d",(*pobjet).frere_identifiant);
        return TRUE;
    }
    
    
    if(strcmp(propriete,"graphique")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).graphique=temp1;
        printf("%s",temp);
        return TRUE;
    }
     
    if(strcmp(propriete,"couleur")==0)
    {
        fscanf(fichier," %s ;",temp);
        (*pobjet).couleur=conversionCOLOR(temp);
        printf("%d",(*pobjet).couleur);
        return TRUE;
    }
    
    if(strcmp(propriete,"son_creation")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).son_creation=temp1;
        printf("%s",temp);
        return TRUE;
    }
    
    if(strcmp(propriete,"son_choc")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).son_choc=temp1;
        printf("%s",temp);
        return TRUE;
    }
    
    if(strcmp(propriete,"son_destruction")==0)
    {
        fscanf(fichier," %s ;",temp);
        temp1=malloc(LONGUEURMAXCHAINE*sizeof(char));
        strcpy(temp1,temp);
        (*pobjet).son_destruction=temp1;
        printf("%s",temp);
        return TRUE;
    }
    erreur = TRUE;
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
