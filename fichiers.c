#include <stdio.h>
#include <strings.h>
#define MAX 100

int ouvrir()
{
	int i;
	char nomfichin[MAX], nomfichout[MAX];
	char	temp[MAX];
	FILE *fichin,*fichout;

	printf("Donner le nom du fichier d'entree : \n");
	scanf("%s",nomfichin);
	fichin=fopen(nomfichin,"r");
	if (fichin==NULL)
	{
		printf("Impossible d'ouvrir le fichier d'entree");
		exit(0);
	}
	else
	{
		strcpy(nomfichout,nomfichin);
		strcat(nomfichout,".out");
		fichout=fopen(nomfichout,"w");
		if (fichout==NULL)
		{
			printf("Impossible d'ouvrir le fichier de sortie");
			exit(0);
		}
		else
		{
			strcpy(temp,"");
			i=0;
			do
			{
				fprintf(fichout,"%d : ",i);
				fputs(temp,fichout);
				i++;
			}while (fgets(temp,MAX,fichin)!=0);
			fclose(fichout);
		}
		fclose(fichin);	
	}
	return(0);
}
