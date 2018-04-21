#include "supanoid.h"

void effacer(OBJET objet)
{
    clearRect(0, 0, (int)taillefenetre.x, (int)taillefenetre.y);
}

void dessiner(OBJET objet)
{
    FILE* fichier;
    setForegroundColor(objet.couleur);
    if(strcmp(objet.graphique,"aucun")!=0)/*si le fichier n'existe pas, rien ne sera affiché*/
    {
        drawImage(objet.graphique, objet.position.x-0.5*objet.dimensions.x, objet.position.y-0.5*objet.dimensions.y);
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

void initialisationgraphiques()
{
    taillefenetre=vecteur(800,800);
    start((int)ceil(taillefenetre.x), (int)ceil(taillefenetre.y));
    registerKeyPressed(VK_LEFT);       
    registerKeyPressed(VK_RIGHT);     
    registerKeyPressed(VK_UP);       
    registerKeyPressed(VK_DOWN); 
    registerKeyPressed(VK_F1); 
    registerKeyPressed(VK_F2); 
    

    setBackgroundColor(BLACK);        
    clearRect(0, 0, 800, 800);      
}

void indiquer(COORD a)
{
    printf("( %f , %f )\n",a.x,a.y);   
}

void decrire(OBJET a)
{
    printf("\n");
    printf("Nom            : %s \n",a.nom);
    printf("Identifiant    : %d\n",a.identifiant);
    printf("\n");
    printf("Position       : ");indiquer(a.position);
    printf("Vitesse        : ");indiquer(a.vitesse);
    printf("Acceleration   : ");indiquer(a.acceleration);
    printf("\n");
    printf("Dimensions     : ");indiquer(a.dimensions);
    printf("Solidite       : %f\n",a.solidite);
    printf("Masse          : %f\n",a.masse);
    printf("Frottement     : %f\n",a.frottement);
    printf("Rebondissement : %f\n",a.rebondissement);
    printf("\n");
    printf("Graphique      : %s \n",a.graphique);
    printf("Forme          : %d\n",a.forme);
    if(a.contenu==NULL)
    {printf("Contenu        : %s\n","Aucun");}
    else
    {printf("Contenu        : %s\n",(*a.contenu).nom);}
    printf("\n==============================\n");
}

