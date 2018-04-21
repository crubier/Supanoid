#include "supanoid.h"

/* Manipulation des objets                  */

PTROBJET creerobjet
(
        COORD position,
 		COORD vitesse,
 		COORD acceleration,
 		int couche,

 		FORME forme,
 		COORD dimensions,
 		float masse,
 		float frottement,
 		float rebondissement,
 		float attraction,
 		float solidite,
 		float agressivite,

        PTRIDENTIFIANT fils,		
        PTRIDENTIFIANT frere,
 		
 		char* graphique,
        char* son,
        COULEUR couleur
)

{
    PTROBJET pobjet;
    char* temp;
    
    pobjet=malloc(sizeof(OBJET));

	if(pobjet==NULL)return NULL;
    
    (*pobjet).position=position;
    (*pobjet).vitesse=vitesse;
    (*pobjet).acceleration=acceleration;
    (*pobjet).couche=couche;
    
    (*pobjet).forme=forme;
    (*pobjet).dimensions=dimensions;
    (*pobjet).masse=masse;
    (*pobjet).frottement=frottement;
    (*pobjet).rebondissement=rebondissement;
    (*pobjet).solidite=solidite;
    (*pobjet).attraction=attraction;
    (*pobjet).agressivite=agressivite;

    (*pobjet).fils=copieridentifiant(fils);
    (*pobjet).frere=copieridentifiant(frere);

    (*pobjet).graphique=creerchaine(son);
    
    (*pobjet).son=creerchaine(son);

    (*pobjet).couleur=couleur;
    
    return pobjet;
}

PTROBJET copierobjet(PTROBJET pobjet)
{
    return creerobjet
    (
        (*pobjet).position,
 		(*pobjet).vitesse,
 		(*pobjet).acceleration,
 		(*pobjet).couche,

 		(*pobjet).forme,
 		(*pobjet).dimensions,
 		(*pobjet).masse,
 		(*pobjet).frottement,
 		(*pobjet).rebondissement,
 		(*pobjet).attraction,
 		(*pobjet).solidite,
 		(*pobjet).agressivite,

        (*pobjet).fils,	
        (*pobjet).frere,
 		
 		(*pobjet).graphique,
        (*pobjet).son,
        (*pobjet).couleur
    
    );
}

PTROBJET nouvelobjet(void)
{
    return creerobjet
    (
        vecteur(0,0),
 		vecteur(0,0),
 		vecteur(0,0),
 		1,

 		INCONNUE,
 		vecteur(0,0),
 		1,
 		0,
 		1,
 		0,
 		1000000,
 		0,

        nouvelidentifiant(),
        nouvelidentifiant(),
 		
 		"INCONNU",
        "INCONNU",
        NOIR
    );
}

/* Manipulation des identifiants            */

PTRIDENTIFIANT creeridentifiant
(
 		char* type,
        char* nom,
        int numero
)

{
    PTRIDENTIFIANT pidentifiant;
      
    pidentifiant=malloc(sizeof(IDENTIFIANT));
    
	if(pidentifiant==NULL)return NULL;

    (*pidentifiant).type=creerchaine(type);
    
    (*pidentifiant).nom=creerchaine(nom);

    (*pidentifiant).numero=numero;
    
    return pidentifiant;
}

PTRIDENTIFIANT copieridentifiant(PTRIDENTIFIANT pidentifiant)
{
    return creeridentifiant
    (
 		(*pidentifiant).type,
        (*pidentifiant).nom,
        (*pidentifiant).numero
    );
}

PTRIDENTIFIANT nouvelidentifiant(void)
{
    return creeridentifiant
    (
 		"INCONNU",
        "INCONNU",
        0
    );
}

/* Manipulation des cellules                */

PTRCELLULE creercellule
(
    PTROBJET element, 
 	PTRIDENTIFIANT identifiant,
	PTRCELLULE suivant,
	PTRCELLULE precedent
)
{
    PTRCELLULE pcellule;
    pcellule=malloc(sizeof(CELLULE));
    
	if(pcellule==NULL)return NULL;

    (*pcellule).element=element;
    (*pcellule).identifiant=identifiant;
    (*pcellule).suivant=suivant;
    (*pcellule).precedent=precedent;
    
    if(origineliste==NULL)
    {
        origineliste=pcellule;
    }
    else
    {
        liercellules(dernierecellule(),pcellule);
    }
    return pcellule;
}

PTRCELLULE copiercellule(PTRCELLULE pcellule)
{
    return creercellule
    (
 		copierobjet((*pcellule).element),
        copieridentifiant((*pcellule).identifiant),
        NULL,
        NULL
    );
}

PTRCELLULE nouvellecellule(void)
{
    return creercellule
    (
 		nouvelobjet(),
        nouvelidentifiant(),
        NULL,
        NULL
    );
}

void liercellules(PTRCELLULE pcellulea, PTRCELLULE pcelluleb)
{
    (*pcellulea).suivant=pcelluleb;
    (*pcelluleb).precedent=pcellulea;
	verifiercellules(pcellulea,pcelluleb);
}

void verifiercellules(PTRCELLULE pcellulea, PTRCELLULE pcelluleb)
{
    if(
    ((*pcellulea).suivant==pcelluleb) && ((*pcelluleb).precedent==pcellulea) ||
    ((*pcellulea).precedent==pcelluleb) && ((*pcelluleb).suivant==pcellulea) ||    
    ((*pcellulea).suivant!=pcelluleb) && ((*pcelluleb).precedent!=pcellulea) ||
    ((*pcellulea).precedent!=pcelluleb) && ((*pcelluleb).suivant!=pcellulea)  
    )return;
    fprintf(journal,"Probleme de liaison de la liste au niveau des cellules %s et %s",(*(*pcellulea).identifiant).nom,(*(*pcelluleb).identifiant).nom);
}

void verifierpointeur(char* p)
{
    if(p == NULL)
    {
        sprintf(erreur,"Allocation memoire");
        exit (1);
    }
}


/* recherche etc */




PTRCELLULE rechercher(PTRIDENTIFIANT pidentifiant)
{
    PTRCELLULE pcellule;
    pcellule=premierecellule();

	printf("Recherche de %s :\n",ecrireIDENTIFIANT(*pidentifiant));
    while(pcellule!=NULL)
    {
		printf("      %s ",ecrireIDENTIFIANT(*(*pcellule).identifiant));
        if(compareridentifiants(pidentifiant,(*pcellule).identifiant)==0)
        {
			printf("OK\n");
            return pcellule;
        }
        pcellule=(*pcellule).suivant;
		printf("NON\n");
    }
	printf("NON trouve\n");
    return NULL;
}

PTRCELLULE cellulenumero(int i)
{
    PTRCELLULE pcellule;
    int j;
	if(origineliste!=NULL)
	{
		pcellule=origineliste;
	}
	else
	{
		return NULL;
	}
	
	if(i>nombrecellules() || i<1)
	{
		return;
	}

	while((*pcellule).precedent!=NULL)
	{
		pcellule=(*pcellule).precedent;
	}

	j=0;
    while(j<i-1 && (*pcellule).suivant!=NULL)
	{
		pcellule=(*pcellule).suivant;
		j++;
	}
    return pcellule;
}

int nombrecellules(void)
{
	PTRCELLULE pcellule;
    int i;

	i=0;

	if(origineliste!=NULL)
	{
		pcellule=origineliste;
	}
	else
	{
		return 0;
	}
	
	while((*pcellule).precedent!=NULL)
	{
		pcellule=(*pcellule).precedent;
	}


	while(pcellule!=NULL)
	{
		i++;
		pcellule=(*pcellule).suivant;

	}
    return i;
}

PTRCELLULE premierecellule(void)
{
    return cellulenumero(1);
}

PTRCELLULE dernierecellule(void)
{
    return cellulenumero(nombrecellules());
}



int compareridentifiants(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb)
{
    if(((*pidentifianta).numero-(*pidentifiantb).numero)==0)
    {
        if(strcmp((*pidentifianta).nom,(*pidentifiantb).nom)==0)
        {
            return strcmp((*pidentifianta).type,(*pidentifiantb).type);
        }
        else
        {
            return strcmp((*pidentifianta).nom,(*pidentifiantb).nom);
        } 
    }
    else
    {        
        return((*pidentifianta).numero - (*pidentifiantb).numero);
    }
}



/*chaines de caractere*/

char* creerchaine(char* chaine)
{
    char* res;
    res=malloc((strlen(chaine)+2)*sizeof(char));
    strcpy(res,chaine);
    return res;
}

char* lireligne(char* lignecommande)
{
    char* arguments;
    char* ligne;
	char temp[LONGCHAINE];
	int i,imax;
	BOOLEAN fini;

	ligne=creerchaine(lignecommande);
	arguments=malloc(LONGCHAINE*NBPARAM*sizeof(char));

    sscanf(ligne," %[^][,; ]s ",arguments);
	
	if(strstr(ligne,"[")!=NULL)					// On verifie que la ligne est valide, avec [ et ]
	{
		if(strstr(ligne,"]")!=NULL)
		{
			ligne=strstr(ligne,"[")+1;
			(*strstr(ligne,"]"))='\0';
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}


	i=1;
	fini=FALSE;
	while(fini==FALSE)
	{		
		if(sscanf(ligne," %[^][,; ]s  ",temp)!=EOF)
		{
			strcpy(arguments+LONGCHAINE*i*sizeof(char),temp);
			i++;
			if(strstr(ligne,",")!=NULL)
			{
				ligne=strstr(ligne,",")+sizeof(char);
			}
			else
			{
				fini=TRUE;				
			}			
		}
		else
		{
			fini=TRUE;
		}
	}
	imax=i-1;
	fprintf(journal,"%s[",arguments);
	for(i=1;i<=imax-1;i++)
	{
		ligne=arguments+LONGCHAINE*i*sizeof(char);
		fprintf(journal,"%s,",ligne);
	}
	ligne=arguments+LONGCHAINE*i*sizeof(char);
	fprintf(journal,"%s];\n",ligne);

	return(arguments);

}

///////// lecture chaines

int lireint(char* chaine)
{
	int res;
	sscanf(chaine,"%d",&res);
	return res;
}

char* ecrireint(int a)
{
	char res[LONGCHAINE];
	sprintf(res,"%d",a);	
	return creerchaine(res);
}

float lirefloat(char* chaine)
{
	float res;
	sscanf(chaine,"%f",&res);
	return res;
}

char* ecrirefloat(float a)
{
	char res[LONGCHAINE];
	sprintf(res,"%g",a);	
	return creerchaine(res);
}

COORD lireCOORD(char* chaine)
{
	COORD res;
	sscanf(chaine,"(%f:%f)",&(res.x),&(res.y));
	return res;
}

char* ecrireCOORD(COORD a)
{
	char res[LONGCHAINE];
	sprintf(res,"(%g:%g)",a.x,a.y);	
	return creerchaine(res);
}

FORME lireFORME(char* chaine)
{
    if(strcmp(chaine,"CERCLE")==0)return CERCLE;
    if(strcmp(chaine,"RECTANGLE")==0)return RECTANGLE;
    if(strcmp(chaine,"RAQUETTE")==0)return RAQUETTE;
    return INCONNUE;
}

char* ecrireFORME(FORME a)
{
	char res[LONGCHAINE];
	sprintf(res,"INCONNUE");
    if(a==CERCLE)sprintf(res,"CERCLE");
    if(a==RECTANGLE)sprintf(res,"RECTANGLE");
    if(a==RAQUETTE)sprintf(res,"RAQUETTE");
    return creerchaine(res);
}

COULEUR lireCOULEUR(char* chaine)
{
    if(strcmp(chaine,"BLANC")==0)return BLANC;
    if(strcmp(chaine,"NOIR")==0)return NOIR;
    if(strcmp(chaine,"ROUGE")==0)return ROUGE;
    if(strcmp(chaine,"BLEU")==0)return BLEU;
    if(strcmp(chaine,"VERT")==0)return VERT;
    if(strcmp(chaine,"JAUNE")==0)return JAUNE;
    if(strcmp(chaine,"CYAN")==0)return CYAN;
    if(strcmp(chaine,"GRIS")==0)return GRIS;
    if(strcmp(chaine,"MAGENTA")==0)return MAGENTA;
    if(strcmp(chaine,"ORANGE")==0)return ORANGE;
    if(strcmp(chaine,"ROSE")==0)return ROSE;
    return NOIR;
}

char* ecrireCOULEUR(COULEUR a)
{
	char res[LONGCHAINE];
	sprintf(res,"NOIR");
    if(a==BLANC)sprintf(res,"BLANC");
    if(a==NOIR)sprintf(res,"NOIR");
    if(a==ROUGE)sprintf(res,"ROUGE");
    if(a==BLEU)sprintf(res,"BLEU");
    if(a==VERT)sprintf(res,"VERT");
    if(a==JAUNE)sprintf(res,"JAUNE");
    if(a==CYAN)sprintf(res,"CYAN");
    if(a==GRIS)sprintf(res,"GRIS");
    if(a==MAGENTA)sprintf(res,"MAGENTA");
    if(a==ORANGE)sprintf(res,"ORANGE");
    if(a==ROSE)sprintf(res,"ROSE");
    return creerchaine(res);
}

IDENTIFIANT lireIDENTIFIANT(char* chaine)
{
	IDENTIFIANT res;
	res=*nouvelidentifiant();
	
    if(strcmp(chaine,"dernierobjet")==0)return *(*dernierecellule()).identifiant;
	if(strcmp(chaine,"premierobjet")==0)return *(*premierecellule()).identifiant;
	if(sscanf(chaine,"(%[^:]s:%s[^:]:%d)",&res.type,&res.nom,&res.numero)!=EOF)
	{
		return res;			//si on trouve l'objet on le retourne
	}
	
	return res;
}

char* ecrireIDENTIFIANT(IDENTIFIANT a)
{
	char res[LONGCHAINE];
	sprintf(res,"(%s:%s:%d)",a.type,a.nom,a.numero);
	return creerchaine(res); 
}

char* ecrireOBJET(OBJET a)
{
	char res[20*LONGCHAINE];
	char temp[LONGCHAINE];

	strcpy(res,VIDE);

    sprintf(temp,"Position         : %s \n",ecrireCOORD(a.position));
	strcat(res,temp);
 	sprintf(temp,"Vitesse          : %s \n",ecrireCOORD(a.vitesse));
	strcat(res,temp);
 	sprintf(temp,"Acceleration     : %s \n",ecrireCOORD(a.acceleration));
	strcat(res,temp);
 	sprintf(temp,"Couche           : %s \n",ecrireint(a.couche));
	strcat(res,temp);
	sprintf(temp,"Forme            : %s \n",ecrireFORME(a.forme));
	strcat(res,temp);
	sprintf(temp,"Dimensions       : %s \n",ecrireCOORD(a.dimensions));
	strcat(res,temp);
	sprintf(temp,"Masse            : %s \n",ecrirefloat(a.masse));
	strcat(res,temp);
	sprintf(temp,"Frottement       : %s \n",ecrirefloat(a.frottement));
	strcat(res,temp);
	sprintf(temp,"Rebondissement   : %s \n",ecrirefloat(a.rebondissement));
	strcat(res,temp);
	sprintf(temp,"Solidite         : %s \n",ecrirefloat(a.solidite));
	strcat(res,temp);
	sprintf(temp,"Attraction       : %s \n",ecrirefloat(a.attraction));
	strcat(res,temp);
	sprintf(temp,"Agressivite      : %s \n",ecrirefloat(a.agressivite));
	strcat(res,temp);
	sprintf(temp,"Fils             : %s \n",ecrireIDENTIFIANT(*a.fils));
	strcat(res,temp);
	sprintf(temp,"Frere            : %s \n",ecrireIDENTIFIANT(*a.frere));
	strcat(res,temp);
	sprintf(temp,"Graphique        : %s \n",(a.graphique));
	strcat(res,temp);
    sprintf(temp,"Son              : %s \n",(a.son));
	strcat(res,temp);
    sprintf(temp,"Couleur          : %s \n",ecrireCOULEUR(a.couleur));
	strcat(res,temp);

	return creerchaine(res); 
}

char* ecrireLISTE(void)
{
	char res[10*LONGCHAINE];
	char temp[10*LONGCHAINE];
	int i;
	
	strcpy(temp,VIDE);
	for(i=1;i<nombrecellules();i++)
	{
		strcat(temp,ecrireIDENTIFIANT(*(*cellulenumero(i)).identifiant));
		strcat(temp,",");
	}
	strcat(temp,ecrireIDENTIFIANT(*(*dernierecellule()).identifiant));
	sprintf(res,"{%s}",temp);
	return creerchaine(res);
}

PTRCELLULE lireOBJET(char* chaine)
{
	IDENTIFIANT identifiant;

	identifiant=lireIDENTIFIANT(chaine);
	
	return rechercher(&identifiant);
}

///////////////////

void executercommande(char* lignecommande)
{
	char* parametres;
	char nomfichier[LONGCHAINE];
	parametres=lireligne(lignecommande);

	if(parametres==NULL)return;	

	if(strcmp(parametres,"creerobjet")==0)
	{
		action_creerobjet(parametres);
		return;
	}

	if(strcmp(parametres,"modifierpropriete")==0)
	{
		action_modifierpropriete(parametres);
		return;
	}

	if(strcmp(parametres,"jouerson")==0)
	{
		action_jouerson(parametres);
		return;
	}
	
	sprintf(nomfichier,"actions/%s",parametres);
	executerfichier(creerchaine(nomfichier));
	
}


void executerfichier(char* parametres)
{
	FILE* fichier;
	char lignecommande[LONGCHAINE];
	char nomfichier[LONGCHAINE]; 
	char* res=NULL;

	sprintf(nomfichier,"%s/%s.supanoid",repertoire,parametres);

	printf("Ouverture fichier %s\n",nomfichier);
	fichier=fopen(nomfichier,"r");
	if(fichier==NULL)
	{
		printf("erreur ouverture\n");
		return;
	}
	do
	{
		strcpy(lignecommande,VIDE);
		res=fgets(lignecommande,LONGCHAINE,fichier);		
		executercommande(lignecommande);
	}while(res!=NULL);

	printf("Fermeture fichier %s\n",nomfichier);
	fclose(fichier);	
	printf("Ok\n");
	decrireLISTE();
}



void entrerpropriete(PTRCELLULE pcellule, char* propriete, char* valeur)
{
    PTROBJET pobjet;

    pobjet = (*pcellule).element;

    if(strcmp(propriete,"position")==0)
    {
        (*pobjet).position=lireCOORD(valeur);
        return ;
    }
    
    if(strcmp(propriete,"vitesse")==0)
    {
        (*pobjet).vitesse=lireCOORD(valeur);
        return ;
    }
    
    if(strcmp(propriete,"acceleration")==0)
    {
        (*pobjet).acceleration=lireCOORD(valeur);
        return ;
    }
    
    if(strcmp(propriete,"couche")==0)
    {
        (*pobjet).couche=lireint(valeur);
        return ;
    }
    
    if(strcmp(propriete,"forme")==0)
    {
        (*pobjet).forme=lireFORME(valeur);
        return ;
    }
    
    if(strcmp(propriete,"dimensions")==0)
    {
        (*pobjet).dimensions=lireCOORD(valeur);
        return ;
    }
       
    if(strcmp(propriete,"masse")==0)
    {
        (*pobjet).masse=lirefloat(valeur);
        return ;
    }
    
    if(strcmp(propriete,"frottement")==0)
    {
        (*pobjet).frottement=lirefloat(valeur);
        return ;
    }
    
    if(strcmp(propriete,"rebondissement")==0)
    {
        (*pobjet).rebondissement=lirefloat(valeur);
        return ;
    }
    
    if(strcmp(propriete,"solidite")==0)
    {
        (*pobjet).solidite=lirefloat(valeur);
        return ;
    }
    
    if(strcmp(propriete,"attraction")==0)
    {
        (*pobjet).attraction=lirefloat(valeur);
        return ;
    }
    
    if(strcmp(propriete,"agressivite")==0)
    {
        (*pobjet).agressivite=lirefloat(valeur);
        return ;
    }
    
      
    if(strcmp(propriete,"graphique")==0)
    {
        (*pobjet).graphique=creerchaine(valeur);
        return ;
    }
     
  	if(strcmp(propriete,"son")==0)
    {
        (*pobjet).son=creerchaine(valeur);
        return ;
    }

    if(strcmp(propriete,"couleur")==0)
    {
        (*pobjet).couleur=lireCOULEUR(valeur);
        return ;
    }
        
    sprintf(erreur,"Impossible de modifier la propriete %s",propriete);
    return ;
}


