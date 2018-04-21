#include "supanoid.h"

void effacer(void)
{
    clearRect(0, 0, (int)fenetre.dimensions.x, (int)fenetre.dimensions.y);
}

void dessin(void)
{
    PTRCELLULE pcellule;
    pcellule=premierecellule(originelisteactifs);
    while(pcellule!=NULL)
    {
        dessiner((*(*pcellule).element));
        pcellule=(*pcellule).suivant;
    }
}

void dessiner(OBJET objet)
{
    FILE* fichier;
   	char nom[LONGUEURMAXCHAINE];
   	
    setForegroundColor(objet.couleur);
    if(strcmp(objet.graphique,"INCONNU")!=0)/*si le fichier n'existe pas, rien ne sera affiché, les formes seront affichée sulement si graphique = AUCUN*/
    {
        strcpy(nom,"images/");
        strcat(nom,objet.graphique);
        drawImage(nom, objet.position.x-0.5*objet.dimensions.x, objet.position.y-0.5*objet.dimensions.y);
    }
    else
    {
        if(objet.forme==RECTANGLE)
        {
            drawRect(objet.position.x-0.5*objet.dimensions.x,objet.position.y-0.5*objet.dimensions.y, objet.dimensions.x, objet.dimensions.y);
        }
    
        if(objet.forme==CERCLE) 
        {
            drawOval(objet.position.x-0.5*objet.dimensions.x,objet.position.y-0.5*objet.dimensions.y, objet.dimensions.x, objet.dimensions.y);
        }
    }
}

void initialisationgraphiques(void)
{
    start((int)fenetre.dimensions.x, (int)fenetre.dimensions.y);
    registerKeyPressed(VK_LEFT);       
    registerKeyPressed(VK_RIGHT);     
    registerKeyPressed(VK_UP);       
    registerKeyPressed(VK_DOWN); 
    registerKeyPressed(VK_F1); 
    registerKeyPressed(VK_F2); 
    registerKeyPressed(VK_F3); 
    registerKeyPressed(VK_F4); 
    registerKeyPressed(VK_P);
    registerKeyPressed(VK_Q);
    registerSound("sons/b.wav");
    DT=0.002;

    setBackgroundColor(fenetre.couleur);        
    clearRect(0, 0, (int)fenetre.dimensions.x, (int)fenetre.dimensions.y);      
}

void indiquer(COORD a)
{
    printf("( %g , %g )",a.x,a.y);   
}

void decrire(OBJET a)
{
    printf("\n============================================\n\n");
    printf("Nom            = %s \n",a.nom);
    printf("Identifiant    = %d\n",a.identifiant);
    printf("\n");
    printf("Position       = ");indiquer(a.position);printf("\n");
    printf("Vitesse        = ");indiquer(a.vitesse);printf("\n");
    printf("Acceleration   = ");indiquer(a.acceleration);printf("\n");
    printf("\n");
    printf("Dimensions     = ");indiquer(a.dimensions);printf("\n");
    printf("Solidite       = %f\n",a.solidite);
    printf("Masse          = %f\n",a.masse);
    printf("Frottement     = %f\n",a.frottement);
    printf("Rebondissement = %f\n",a.rebondissement);
    printf("\n");
    printf("Graphique      = %s \n",a.graphique);
    printf("Forme          = %d \n",a.forme);
    printf("\n============================================\n\n");
}

void identifier(OBJET a)
{
    printf("\n============================================\n\n");
    printf("Type           = %s \n",a.type);
    printf("Nom            = %s \n",a.nom);
    printf("Identifiant    = %d\n",a.identifiant);
    printf("\n============================================\n\n");
}

void jouerson(char* son)
{
    playSound(son);
}

