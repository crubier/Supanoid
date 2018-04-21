#include "supanoid.h"

char* lireligne(char* lignecommande)
{
    char* arguments;
    char* ligne;
	char* debut;
	char* vraidebut;
	char* fin;
	char* vraifin;
	char* temp;
	int i,nbcrochets;
	BOOLEAN fini;

	fini=FALSE;
	ligne=creerchaine(lignecommande);
	arguments=malloc(LONGCHAINE*(NBPARAM+1)*sizeof(char));
	for(temp=arguments;temp<(arguments+LONGCHAINE*NBPARAM*sizeof(char));temp+=sizeof(char))
	{
		*temp='\0';
	}

	if(strlen(ligne)<1)
	{
		strncpy(arguments,ligne,LONGCHAINE);
		return arguments;
	}
	if(strstr(ligne,"[")==NULL || strstr(ligne,"]")==NULL) //si pas de crochets, pas de commande
	{
		strncpy(arguments,ligne,LONGCHAINE);
		return arguments;
	}

//Initialisation


	
	temp=ligne;
	nbcrochets=0;
	while((*temp!=';' || nbcrochets!=0) && *temp!='\0')
	{
			if(*temp=='[')nbcrochets++;
			if(*temp==']')nbcrochets--;			
			temp+=sizeof(char);
			if(*temp=='\n') (*temp)=' ';
	}
	*temp='\0';
	if(nbcrochets!=0)
	{
		strncpy(arguments,ligne,LONGCHAINE);
		return arguments;
	}

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

	i=0;
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

//Retour

	return(arguments);

}

void executerargument(char* arguments, char* argumentsfichierparent, int a, int b)
{
	int i;
	if(b<a)return;
	if(a<0)a=0;
	if(b>=NBPARAM)b=NBPARAM;
	for(i=a;i<=b;i++)
	{
		strncpy(arguments + i*LONGCHAINE*sizeof(char),executercommande(arguments + i*LONGCHAINE*sizeof(char),argumentsfichierparent),LONGCHAINE);
	}
}

char* executerfichier(char* parametres)
{
	FILE* fichier;
	char lignecommande[LONGCHAINE];
	char nomfichier[LONGCHAINE]; 
	char* res=NULL;
	char* temp=NULL;

	sprintf(nomfichier,"mondes/%s/%s.supanoid",repertoire,parametres);
	fichier=fopen(nomfichier,"r");
	if(fichier==NULL)
	{
		return NULL;
	}
	

	fprintf(journal,"Ouverture fichier %s\n",nomfichier);	
	do
	{
		strcpy(lignecommande,VIDE);
		res=fgets(lignecommande,LONGCHAINE,fichier);

		executercommande(lignecommande,parametres);

	}while(res!=NULL);
	fclose(fichier);
	return("Fichier %s lu \n",nomfichier);

}

char* executercommande(char* lignecommande,char* argumentsfichierparent)
{
	char* parametres;
	char* res;
	int i;

	res=creerchaine(VIDE);

	parametres=lireligne(lignecommande);

	if(parametres==NULL)return res;

	if(strcmp(parametres,lignecommande)==0)
	{
		if(modefonctionnement>=1)
		{
			printf("%s",parametres);
			printf("\n",parametres);
		}
	
		res=creerchaine(lignecommande);
	}
	else
	{

		if(modefonctionnement>=1)
		{
			printf("%s[",parametres);
			i=1;
			while(i<NBPARAM-1 && *(parametres+LONGCHAINE*(i+1)*sizeof(char))!='\0')
			{
				printf("%s,",parametres+LONGCHAINE*i*sizeof(char));
				i++;
			}
			printf("%s];\n",parametres+LONGCHAINE*i*sizeof(char));
		}

	// Passage de parametres
	
		if(strcmp(parametres,"argument")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= creerchaine(argumentsfichierparent + lireint(parametres + 1*LONGCHAINE*sizeof(char))*LONGCHAINE*sizeof(char));
		}
		
	// Actions
	
		if(strcmp(parametres,"creerobjet")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			action_creerobjet(parametres);
			res=creerchaine("creerobjet");
		}
	
		if(strcmp(parametres,"supprimerobjet")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			action_supprimerobjet(parametres);
			res=creerchaine("supprimerobjet");
		}
	
		if(strcmp(parametres,"modifierpropriete")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,3);
			action_modifierpropriete(parametres);
			res=creerchaine("modifierpropriete");
		}
	
		if(strcmp(parametres,"propriete")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= afficherpropriete(lireOBJET(parametres+1*LONGCHAINE*sizeof(char)),parametres+2*LONGCHAINE*sizeof(char));
		}
	
		if(strcmp(parametres,"modifierparametre")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			action_modifierparametre(parametres);
			res=creerchaine("modifierparametre");
		}
	
		if(strcmp(parametres,"parametre")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= afficherparametre(parametres);
		}
	
		if(strcmp(parametres,"jouer")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			action_jouer(parametres);
			res=creerchaine("jouer");
		}

		if(strcmp(parametres,"charger")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			action_charger(parametres);
			res=creerchaine("charger");
		}
		
		if(strcmp(parametres,"initialiser")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,0);
			action_initialiser(parametres);
			res=creerchaine("initialiser");
		}
	
		if(strcmp(parametres,"affichernoms")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,0);
			action_affichernoms(parametres);
			res=creerchaine("affichernoms");
		}
	
		if(strcmp(parametres,"cachernoms")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,0);
			action_cachernoms(parametres);
			res=creerchaine("cachernoms");
		}
		
		if(strcmp(parametres,"executer")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			action_executer(parametres);
			res=creerchaine("executer");
		}
	
		if(strcmp(parametres,"imprimer")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			action_ecrire(parametres);
			res=creerchaine("imprimer");
		}

		if(strcmp(parametres,"aleatoire")==0)
		{
			float r;
			executerargument(parametres,argumentsfichierparent,1,2);
			action_ecrire(parametres);
			r=
				lirefloat(parametres + 1*LONGCHAINE*sizeof(char)) + 
				(
					((float)rand()/RAND_MAX)*
					(lirefloat(parametres + 2*LONGCHAINE*sizeof(char))-lirefloat(parametres + 1*LONGCHAINE*sizeof(char)))
					
				 );
			res=ecrirefloat(r);
			printf("Aleatoire : %s\n",res);

		}

	//Reperage
	
		if(strcmp(parametres,"dernierobjet")==0)
		{
			res= ecrireIDENTIFIANT(*(*dernierecellule()).identifiant);
		}
	
		if(strcmp(parametres,"premierobjet")==0)
		{
			res= ecrireIDENTIFIANT(*(*premierecellule()).identifiant);
		}
	
		if(strcmp(parametres,"dernierobjettype")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			IDENTIFIANT identifiant;
			identifiant = lireIDENTIFIANT(parametres + 1*LONGCHAINE*sizeof(char));
			if(recherchertype(&identifiant,dernierecellule(),-1)!=NULL)
			{
				res= ecrireIDENTIFIANT(*(*recherchertype(&identifiant,dernierecellule(),-1)).identifiant);
			}
			else
			{
				res=creerchaine( VIDE );
			}
		}
	
		if(strcmp(parametres,"premierobjettype")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			IDENTIFIANT identifiant;
			identifiant = lireIDENTIFIANT(parametres + 1*LONGCHAINE*sizeof(char));
			if(recherchertype(&identifiant,premierecellule(),1)!=NULL)
			{
				res= ecrireIDENTIFIANT(*(*recherchertype(&identifiant,premierecellule(),1)).identifiant);
			}
			else
			{
				res=creerchaine( VIDE );
			}
		}
	
		if(strcmp(parametres,"dernierobjettypenom")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			IDENTIFIANT identifiant;
			identifiant = lireIDENTIFIANT(parametres + 1*LONGCHAINE*sizeof(char));
			if(recherchertypenom(&identifiant,dernierecellule(),-1)!=NULL)
			{
				res= ecrireIDENTIFIANT(*(*recherchertypenom(&identifiant,dernierecellule(),-1)).identifiant);
			}
			else
			{
				res=creerchaine( VIDE );
			}
		}
	
		if(strcmp(parametres,"premierobjettypenom")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			IDENTIFIANT identifiant;
			identifiant = lireIDENTIFIANT(parametres + 1*LONGCHAINE*sizeof(char));
			if(recherchertypenom(&identifiant,premierecellule(),1)!=NULL)
			{
				res= ecrireIDENTIFIANT(*(*recherchertypenom(&identifiant,premierecellule(),1)).identifiant);
			}
			else
			{
				res=creerchaine( VIDE );
			}
		}
	
		if(strcmp(parametres,"prochainobjet")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			IDENTIFIANT identifiant;
			identifiant=lireIDENTIFIANT(parametres + 1*LONGCHAINE*sizeof(char));
			res= ecrireIDENTIFIANT(*prochainidentifiant(&identifiant));
		}
	
		if(strcmp(parametres,"objetnumero")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrireIDENTIFIANT(*(*cellulenumero(lireint(parametres + 1*LONGCHAINE*sizeof(char)))).identifiant);
		}
	
		if(strcmp(parametres,"nombreobjets")==0)
		{
			res= ecrireint(nombrecellules());
		}
	
	// identifiants
	
		if(strcmp(parametres,"identifiant_type")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= creerchaine(lireIDENTIFIANT(parametres + 1*LONGCHAINE*sizeof(char)).type);
		}
	
		if(strcmp(parametres,"identifiant_nom")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= creerchaine(lireIDENTIFIANT(parametres + 1*LONGCHAINE*sizeof(char)).nom);
		}
	
		if(strcmp(parametres,"identifiant_numero")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrireint(lireIDENTIFIANT(parametres + 1*LONGCHAINE*sizeof(char)).numero);
		}
	
	// Operations mathematiques
	
		if(strcmp(parametres,"vecteur_somme")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrireCOORD(somme(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_difference")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrireCOORD(difference(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_oppose")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrireCOORD(oppose(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_produitscalaire")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrirefloat(produitscalaire(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_multiplicationscalaire")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrireCOORD(multiplicationscalaire(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lirefloat(parametres + 2*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_multiplication")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrireCOORD(multiplication(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_inverse")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrireCOORD(multiplication(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_normalisation")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrireCOORD(normalisation(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_distance")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrirefloat(distance(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_norme")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrirefloat(norme(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_total")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrirefloat(total(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char))));
		}

		if(strcmp(parametres,"vecteur")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrireCOORD(vecteur(lirefloat(parametres + 1*LONGCHAINE*sizeof(char)),lirefloat(parametres + 2*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"vecteur_egalite")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			if(fabs(distance(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char)))) < EPSILON )
			{
				res=ecrireint(0);
			}
			else
			{
				res=ecrirefloat(distance(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)),lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
			}
		}
	
		if(strcmp(parametres,"vecteur_inferiorite")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			if(norme(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)))<norme(lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))))
			{
				res=ecrireint(0);
			}
			else
			{
				res=ecrirefloat(norme(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)))-norme(lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
			}
		}
	
		if(strcmp(parametres,"vecteur_superiorite")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			if(norme(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)))>norme(lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))))
			{
				res=ecrireint(0);
			}
			else
			{
				res=ecrirefloat(norme(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)))-norme(lireCOORD(parametres + 2*LONGCHAINE*sizeof(char))));
			}
		}
	
		if(strcmp(parametres,"vecteur_x")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res=ecrirefloat(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)).x);
		}
	
	
		if(strcmp(parametres,"vecteur_y")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res=ecrirefloat(lireCOORD(parametres + 1*LONGCHAINE*sizeof(char)).y);
		}
	
		if(strcmp(parametres,"reel_somme")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrirefloat(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))+lirefloat(parametres + 2*LONGCHAINE*sizeof(char)));
		}
	
		if(strcmp(parametres,"reel_difference")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrirefloat(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))-lirefloat(parametres + 2*LONGCHAINE*sizeof(char)));
		}
	
		if(strcmp(parametres,"reel_oppose")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrirefloat(-lirefloat(parametres + 1*LONGCHAINE*sizeof(char)));
		}
	
		if(strcmp(parametres,"reel_multiplication")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrirefloat(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))*lirefloat(parametres + 2*LONGCHAINE*sizeof(char)));
		}
	
		if(strcmp(parametres,"reel_inverse")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrirefloat(1/lirefloat(parametres + 1*LONGCHAINE*sizeof(char)));
		}
	
		if(strcmp(parametres,"reel_module")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			res= ecrirefloat(fabs(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"reel_exposant")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrirefloat(pow(lirefloat(parametres + 1*LONGCHAINE*sizeof(char)),lirefloat(parametres + 2*LONGCHAINE*sizeof(char))));
		}
	
		if(strcmp(parametres,"reel_egalite")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			if(fabs(lirefloat(parametres + 1*LONGCHAINE*sizeof(char)) - lirefloat(parametres + 2*LONGCHAINE*sizeof(char))) < EPSILON)
			{
				res=ecrireint(0);
			}
			else
			{
				res=ecrirefloat(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))-lirefloat(parametres + 2*LONGCHAINE*sizeof(char)));
			}
		}
	
		if(strcmp(parametres,"reel_inferiorite")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			if(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))<lirefloat(parametres + 2*LONGCHAINE*sizeof(char)))
			{
				res=ecrireint(0);
			}
			else
			{
				res=ecrirefloat(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))-lirefloat(parametres + 2*LONGCHAINE*sizeof(char)));
			}
		}
	
		if(strcmp(parametres,"reel_superiorite")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			if(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))>lirefloat(parametres + 2*LONGCHAINE*sizeof(char)))
			{
				res=ecrireint(0);
			}
			else
			{
				res=ecrirefloat(lirefloat(parametres + 1*LONGCHAINE*sizeof(char))-lirefloat(parametres + 2*LONGCHAINE*sizeof(char)));
			}
		}

		if(strcmp(parametres,"reel_inclusion")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,3);
			if(lirefloat(parametres + 1*LONGCHAINE*sizeof(char)) > lirefloat(parametres + 2*LONGCHAINE*sizeof(char)) && lirefloat(parametres + 1*LONGCHAINE*sizeof(char)) < lirefloat(parametres + 3*LONGCHAINE*sizeof(char)))
			{
				res=ecrireint(0);
			}
			else
			{
				res=ecrireint(1);
			}
		}
	
	
	//chaines
	
		if(strcmp(parametres,"chaine_concatener")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= creerchaine(strcat(parametres + 1*LONGCHAINE*sizeof(char),parametres + 2*LONGCHAINE*sizeof(char)));
		}
	
	
		if(strcmp(parametres,"egalite")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,2);
			res= ecrireint(strcmp(parametres + 1*LONGCHAINE*sizeof(char),parametres + 2*LONGCHAINE*sizeof(char)));
		}
	
	
		if(strcmp(parametres,"si")==0)
		{
			executerargument(parametres,argumentsfichierparent,1,1);
			if(strcmp(parametres + 1*LONGCHAINE*sizeof(char),"0")==0 || strcmp(parametres + 1*LONGCHAINE*sizeof(char),"0.")==0)
			{
				executerargument(parametres,argumentsfichierparent,2,2);
				res= creerchaine(parametres + 2*LONGCHAINE*sizeof(char));
			}
			else
			{
				executerargument(parametres,argumentsfichierparent,3,3);
				res= creerchaine(parametres + 3*LONGCHAINE*sizeof(char));			
			}
		}
	
		if(strcmp(parametres,"quitter")==0)
		{
			res=creerchaine("quitter");
			fini=1;
		}  
	
		if(strcmp(parametres,"pause")==0)
		{
			action_jouer(parametres);
			res=creerchaine("pause");
			system("pause");
		}

		if(strcmp(parametres,"decrireliste")==0)
		{
			decrireLISTEdetail();
			res=creerchaine("decrireliste");
		}
	//recherche
	
		if(strcmp(res,VIDE)==0 && strlen(parametres)>0 )
		{
			executerargument(parametres,argumentsfichierparent,1,NBPARAM);
			res= executerfichier(parametres);
		}
	
		if(res==NULL)
		{
			res=creerchaine(parametres);
		}
	}

if(modefonctionnement>=1)
{
		printf(">> %s\n",res);
}
if(modefonctionnement>=2)
{
	system("pause");
}

	return res;
}


void demanderparametres(int argc, char *argv[])
{
	char nomjournal[LONGCHAINE];

	if(argc>1)
	{
		strcpy(repertoire,argv[1]);
	}
	else
	{
		printf("Monde ? ");
		scanf("%s",repertoire);
		printf("\n");
	}
	
	sprintf(nomjournal,"mondes/%s/journal.supanoid",repertoire);
	journal=fopen(nomjournal,"w+");

	if(journal==NULL)
	{
		printf("Ouverture impossible de mondes/%s !\n",repertoire);
		system("pause");
		exit(3);
	}
	printf("Ouverture de mondes/%s !\n",repertoire);
}


