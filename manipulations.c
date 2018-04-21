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

 		char* graphique,
        char* texte,
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

    (*pobjet).graphique=creerchaine(graphique);
    
    (*pobjet).texte=creerchaine(texte);

    (*pobjet).couleur=couleur;
    
    return pobjet;
}

PTROBJET copierobjet(PTROBJET pobjet)
{
	if(pobjet==NULL)return NULL;
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

 		(*pobjet).graphique,
        (*pobjet).texte,
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
	if(pidentifiant==NULL)return NULL;
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
	if(pcellule==NULL)return NULL;
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

/////////////////

void supprimercellule(PTRCELLULE pcellule)
{
	if(pcellule==NULL)
	{
		return;
	}

	if((*pcellule).suivant!=NULL && (*pcellule).precedent!=NULL)
	{
		(*(*pcellule).suivant).precedent=(*pcellule).precedent;
		(*(*pcellule).precedent).suivant=(*pcellule).suivant;
	}
	else
	{
		if((*pcellule).precedent==NULL)
		{
			(*(*pcellule).suivant).precedent=NULL;
		}
		if((*pcellule).suivant==NULL)
		{
			(*(*pcellule).precedent).suivant=NULL;
		}
	}

	if(pcellule==origineliste)
	{
		if((*pcellule).suivant!=NULL || (*pcellule).precedent!=NULL)	
		{
			if((*pcellule).precedent!=NULL)
			{
				origineliste=(*pcellule).precedent;
			}
			else
			{
				origineliste=(*pcellule).suivant;
			}
		}
		else
		{
			origineliste=NULL;
		}
	}
	
	(*pcellule).precedent=NULL;
	(*pcellule).suivant=NULL;
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
        exit (1);
    }
}


/* recherche etc */




PTRCELLULE rechercher(PTRIDENTIFIANT pidentifiant)
{
    return recherchertypenomnumero(pidentifiant, cellulenumero(1),1);
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
		return NULL;
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

PTRIDENTIFIANT prochainidentifiant(PTRIDENTIFIANT pidentifiantdepart)
{
	PTRCELLULE pcellule;
	PTRIDENTIFIANT pidentifiant;

	pcellule=premierecellule();
	pidentifiant=copieridentifiant(pidentifiantdepart);

	while(pcellule!=NULL)
	{
		if((*pcellule).suivant==NULL)break;
		pcellule=recherchertypenom(pidentifiant,(*pcellule).suivant,1);
		if(pcellule==NULL)
		{
			break;
		}
		else
		{
			if((*(*pcellule).identifiant).numero > (*pidentifiant).numero)
			{
				(*pidentifiant).numero=(*(*pcellule).identifiant).numero;
			}
		}
	}

	(*pidentifiant).numero++;
	return copieridentifiant(pidentifiant);
}	

PTRCELLULE recherchertype(PTRIDENTIFIANT pidentifiant, PTRCELLULE pi, int sens)
{
    PTRCELLULE pcellule;
    pcellule=pi;

	if(pcellule==NULL)return NULL;

    while(pcellule!=NULL)
    {
        if(compareridentifiantstype(pidentifiant,(*pcellule).identifiant)==0)
        {
            return pcellule;
        }
        if(sens>=0)
		{
			pcellule=(*pcellule).suivant;
		}
		else
		{
			pcellule=(*pcellule).precedent;
		}
    }

    return NULL;
}

PTRCELLULE recherchertypenom(PTRIDENTIFIANT pidentifiant, PTRCELLULE pi, int sens)
{
    PTRCELLULE pcellule;
    pcellule=pi;

	if(pcellule==NULL)return NULL;

    while(pcellule!=NULL)
    {
        if(compareridentifiantstypenom(pidentifiant,(*pcellule).identifiant)==0)
        {
            return pcellule;
        }
        if(sens>=0)
		{
			pcellule=(*pcellule).suivant;
		}
		else
		{
			pcellule=(*pcellule).precedent;
		}
    }

    return NULL;
}

PTRCELLULE recherchertypenomnumero(PTRIDENTIFIANT pidentifiant, PTRCELLULE pi, int sens)
{
    PTRCELLULE pcellule;
    pcellule=pi;

	if(pcellule==NULL)return NULL;

    while(pcellule!=NULL)
    {
        if(compareridentifiantstypenomnumero(pidentifiant,(*pcellule).identifiant)==0)
        {
            return pcellule;
        }
        if(sens>=0)
		{
			pcellule=(*pcellule).suivant;
		}
		else
		{
			pcellule=(*pcellule).precedent;
		}
    }
    return NULL;
}

int compareridentifiantstype(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb)
{
	return strcmp((*pidentifianta).type,(*pidentifiantb).type);
}

int compareridentifiantstypenom(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb)
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

int compareridentifiantstypenomnumero(PTRIDENTIFIANT pidentifianta,PTRIDENTIFIANT pidentifiantb)
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
	PTRIDENTIFIANT pres;
	char type[LONGCHAINE];
	char nom[LONGCHAINE];
	int numero;
	char* temp;

	temp=creerchaine(chaine);

	if(sscanf(temp,"( %[^:]s : %[^:]s : %d )",type,nom,&numero)!=EOF)
	{
		temp=strstr(temp,"(")+sizeof(char);
		sscanf(temp," %[^:]s ",type);
		temp=strstr(temp,":")+sizeof(char);
		sscanf(temp," %[^:]s ",nom);
		temp=strstr(temp,":")+sizeof(char);
		sscanf(temp," %d )",&numero);
		pres=creeridentifiant(type,nom,numero);
	}
	return *pres;
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
	sprintf(temp,"Graphique        : %s \n",(a.graphique));
	strcat(res,temp);
    sprintf(temp,"Texte            : %s \n",(a.texte));
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


char* lireligne(char* lignecommande)
{
    char* arguments;
    char* ligne;
	char* debut;
	char* vraidebut;
	char* fin;
	char* vraifin;
	char* temp;
	int i,imax,nbcrochets;
	BOOLEAN fini;

	i=0;
	imax =NBPARAM;
	ligne=creerchaine(lignecommande);
	arguments=malloc(LONGCHAINE*NBPARAM*sizeof(char));
	fini=FALSE;
	

//Initialisation
	for(debut=arguments;debut<(arguments+LONGCHAINE*NBPARAM*sizeof(char));debut+=sizeof(char))
	{
		*debut='\0';
	}

	if(strstr(ligne,";")!=NULL)(*strstr(ligne,";"))='\0';
	if(strstr(ligne,"\n")!=NULL)(*strstr(ligne,"\n"))='\0';
	if(strlen(ligne)<1)return arguments;
	if(strstr(ligne,"[")==NULL || strstr(ligne,"]")==NULL) return arguments;


//Placement nom commande

	debut=ligne;
	vraidebut=debut;
	while(*debut==' ')debut+=sizeof(char);
	fin=debut;
	while(*fin!='[')fin+=sizeof(char);
	fin-=sizeof(char);
	vraifin=fin;
	if(fin<debut)return arguments;
	while(*fin==' ')fin-=sizeof(char);
	fin+=sizeof(char);
	for(temp=debut;temp!=fin;temp+=sizeof(char))
	{
		*(arguments+(temp-debut))=*temp;
	}

//Placement arguments
	while(fini==FALSE)
	{
		i++;
		debut=vraifin+2*sizeof(char);
		vraidebut=debut;
		while(*debut==' ')debut+=sizeof(char);
		fin=debut;
		nbcrochets=0;
		while( (*fin!=','|| nbcrochets!=0) && (*fin!=']' || nbcrochets!=0))
		{
			if(*fin=='[')nbcrochets++;
			if(*fin==']')nbcrochets--;			
			fin+=sizeof(char);
		}
		if(*fin==']')fini=TRUE;
		fin-=sizeof(char);
		vraifin=fin;
		if(fin<debut)break;
		while(*fin==' ')fin-=sizeof(char);
		fin+=sizeof(char);
		for(temp=debut;temp!=fin;temp+=sizeof(char))
		{
			*(arguments+i*LONGCHAINE*sizeof(char)+(temp-debut))=*temp;
		}
	}

	imax=i+1;

//Affichage
	printf("%s[",arguments);
	for(i=1;i<imax-1;i++)
	{
		ligne=arguments+LONGCHAINE*i*sizeof(char);
		printf("%s,",ligne);

	}
	ligne=arguments+LONGCHAINE*i*sizeof(char);
	printf("%s];\n",ligne);

//Retour

	return(arguments);

}


char* executercommande(char* lignecommande)
{
	char* parametres;
	char nomfichier[LONGCHAINE];
	char res[LONGCHAINE];
	int i;

	strcpy(res,VIDE);

	parametres=lireligne(lignecommande);

	if(parametres==NULL)return;	

	for(i=1;i<NBPARAM;i++)
	{
		if(strstr(parametres + i*LONGCHAINE*sizeof(char),"[")!=NULL && strstr(parametres + i*LONGCHAINE*sizeof(char),"]")!=NULL)
		{
			//printf("Sous commande : %s\n",parametres + i*LONGCHAINE*sizeof(char));
			strncpy(parametres + i*LONGCHAINE*sizeof(char),executercommande(parametres + i*LONGCHAINE*sizeof(char)),LONGCHAINE);
		}
	}	

// Actions

	if(strcmp(parametres,"creerobjet")==0)
	{
		action_creerobjet(parametres);
		return creerchaine(res);
	}

	if(strcmp(parametres,"supprimerobjet")==0)
	{
		action_supprimerobjet(parametres);
		return creerchaine(res);
	}

	if(strcmp(parametres,"modifierpropriete")==0)
	{
		action_modifierpropriete(parametres);
		return creerchaine(res);
	}

	if(strcmp(parametres,"jouerson")==0)
	{
		action_jouerson(parametres);
		return creerchaine(res);
	}
	
	if(strcmp(parametres,"initialiser")==0)
	{
		action_initialiser(parametres);
		return creerchaine(res);
	}

	if(strcmp(parametres,"affichernoms")==0)
	{
		action_affichernoms(parametres);
		return creerchaine(res);
	}

	if(strcmp(parametres,"cachernoms")==0)
	{
		action_cachernoms(parametres);
		return creerchaine(res);
	}
	
	if(strcmp(parametres,"executer")==0)
	{
		action_executer(parametres);
		return creerchaine(res);
	}

	if(strcmp(parametres,"ecrire")==0)
	{
		action_ecrire(parametres);
		return creerchaine(res);
	}

//Reperage;

	if(strcmp(parametres,"dernierobjet")==0)
	{
		return ecrireIDENTIFIANT(*(*dernierecellule()).identifiant);
	}

	if(strcmp(parametres,"premierobjet")==0)
	{
		return ecrireIDENTIFIANT(*(*premierecellule()).identifiant);
	}

	if(strcmp(parametres,"prochainobjet")==0)
	{
		IDENTIFIANT identifiant;
		identifiant=lireIDENTIFIANT(parametres + 1*LONGCHAINE*sizeof(char));
		return ecrireIDENTIFIANT(*prochainidentifiant(&identifiant));
	}

	if(strcmp(parametres,"objetnumero")==0)
	{
		return ecrireIDENTIFIANT(*(*cellulenumero(lireint(parametres + 1*LONGCHAINE*sizeof(char)))).identifiant);
	}

	if(strcmp(parametres,"identifiant_type")==0)
	{
		return creerchaine((*(*lireOBJET(parametres + 1*LONGCHAINE*sizeof(char))).identifiant).type);
	}

	if(strcmp(parametres,"identifiant_nom")==0)
	{
		return creerchaine((*(*lireOBJET(parametres + 1*LONGCHAINE*sizeof(char))).identifiant).nom);
	}

	if(strcmp(parametres,"identifiant_numero")==0)
	{
		return ecrireint((*(*lireOBJET(parametres + 1*LONGCHAINE*sizeof(char))).identifiant).numero);
	}

// Operations mathematiques

	if(strcmp(parametres,"vecteur_somme")==0)
	{
		return ecrireCOORD(somme(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_difference")==0)
	{
		return ecrireCOORD(difference(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_oppose")==0)
	{
		return ecrireCOORD(oppose(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_produitscalaire")==0)
	{
		return ecrirefloat(produitscalaire(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_multiplicationscalaire")==0)
	{
		return ecrireCOORD(multiplicationscalaire(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lirefloat(parametres + 2*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_multiplication")==0)
	{
		return ecrireCOORD(multiplication(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_inverse")==0)
	{
		return ecrireCOORD(multiplication(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_normalisation")==0)
	{
		return ecrireCOORD(normalisation(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_distance")==0)
	{
		return ecrirefloat(distance(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_norme")==0)
	{
		return ecrirefloat(norme(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"vecteur_total")==0)
	{
		return ecrirefloat(total(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"somme")==0)
	{
		return ecrirefloat(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))+lirefloat(parametres + 2*LONGCHAINE*sizeof(char)));
	}

	if(strcmp(parametres,"difference")==0)
	{
		return ecrirefloat(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))-lirefloat(parametres + 2*LONGCHAINE*sizeof(char)));
	}

	if(strcmp(parametres,"oppose")==0)
	{
		return ecrirefloat(-lirefloat(parametres + 1*LONGCHAINE*sizeof(char)));
	}

	if(strcmp(parametres,"multiplication")==0)
	{
		return ecrirefloat(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))*lirefloat(parametres + 2*LONGCHAINE*sizeof(char)));
	}

	if(strcmp(parametres,"inverse")==0)
	{
		return ecrirefloat(1/lirefloat(parametres + 1*LONGCHAINE*sizeof(char)));
	}

	if(strcmp(parametres,"module")==0)
	{
		return ecrirefloat(fabs(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))));
	}

	if(strcmp(parametres,"puissance")==0)
	{
		return ecrirefloat(pow(lirefloat(parametres + 1*LONGCHAINE*sizeof(char)),lirefloat(parametres + 2*LONGCHAINE*sizeof(char))));
	}

//recherche

	if(strlen(parametres)>0)
	{
		sprintf(nomfichier,"actions/%s",parametres);
		return executerfichier(creerchaine(nomfichier));
	}
	return VIDE;
	
}


char* executerfichier(char* parametres)
{
	FILE* fichier;
	char lignecommande[LONGCHAINE];
	char nomfichier[LONGCHAINE]; 
	char* res=NULL;
	char* temp=NULL;

	sprintf(nomfichier,"%s/%s.supanoid",repertoire,parametres);

	fprintf(journal,"Ouverture fichier %s\n",nomfichier);
	fichier=fopen(nomfichier,"r");
	if(fichier==NULL)
	{
		fprintf(journal,"Erreur\n");
		return res;
	}
	do
	{
		strcpy(lignecommande,VIDE);
		res=fgets(lignecommande,LONGCHAINE,fichier);

		executercommande(lignecommande);

	}while(res!=NULL);

	fclose(fichier);	
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
     
  	if(strcmp(propriete,"texte")==0)
    {
        (*pobjet).texte=creerchaine(valeur);
        return ;
    }

    if(strcmp(propriete,"couleur")==0)
    {
        (*pobjet).couleur=lireCOULEUR(valeur);
        return ;
    }
        
    return ;
}


