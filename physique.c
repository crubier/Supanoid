#include "supanoid.h"

void pause(void)
{
    int fini=0;
    dessiner(fenetrepause);
    paint(); 
    while (fini<100) 
    {
        fini++;
        getLastKeyPressed();
        sleepAWhile(1000*DT);
    }
    fini=0;
    while (!fini)
    {
        switch (getLastKeyPressed())
        { 
            case VK_Q:
                fini=1;
                break;
        }
        sleepAWhile( (long) 1000 * DT );

    }
    return ;
}

void mouvement(PTROBJET objet)
{
    (*objet)=positionsuivante((*objet));
    (*objet).acceleration=vecteur(0,0);
}

void mouvements(void)
{
    PTRCELLULE pcellule;
    pcellule=originelisteactifs;
    while(pcellule!=NULL)
    {
        mouvement((*pcellule).element);
        pcellule=(*pcellule).suivant;
        
    }
}


OBJET positionsuivante(OBJET objet)
{
    OBJET res;
    res=objet;
 	res.vitesse=somme(res.vitesse,res.acceleration);
 	res.position=somme(res.position,res.vitesse);
 	return res;
}

void rebond(PTROBJET objeta, PTROBJET objetb)
{
    
    COORD normale;
    
    normale=normalecontact(*objeta,*objetb);
    
  
    if(norme(normale)!=0)
 	{
        float coef;
                   //Voir le fichier maths.nb
        coef=((*objeta).rebondissement*(*objetb).rebondissement)/(((*objeta).masse+(*objetb).masse)*norme(normale)*norme(normale));      
  
        //printf("Rebond %s - %s valeur %g\n",(*objeta).nom,(*objetb).nom,coef);

        (*objeta).acceleration=somme((*objeta).acceleration,
            multiplicationscalaire
            (    
                normale,
                -2*coef*((*objetb).masse)*produitscalaire(difference((*objeta).acceleration,(*objetb).acceleration),normale)
            ));
            
        (*objetb).acceleration=somme((*objetb).acceleration,
            multiplicationscalaire
            (    
                normale,
                -2*coef*((*objeta).masse)*produitscalaire(difference((*objetb).acceleration,(*objeta).acceleration),normale)
            ));


        
        (*objeta).acceleration=somme((*objeta).acceleration,
            multiplicationscalaire
            (    
                normale,
                -2*coef*((*objetb).masse)*produitscalaire(difference((*objeta).vitesse,(*objetb).vitesse),normale)
            ));

        
        (*objetb).acceleration=somme((*objetb).acceleration,
            multiplicationscalaire
            (    
                normale,
                -2*coef*((*objeta).masse)*produitscalaire(difference((*objetb).vitesse,(*objeta).vitesse),normale)
            ));
            
        (*objeta).solidite-=(*objetb).agressivite;
        (*objetb).solidite-=(*objeta).agressivite;
        
        
       
    }     
  
}

void gravitation(PTROBJET objeta, PTROBJET objetb)
{
    COORD posrel;
    float coef;
    COORD vitessea,vitesseb;
    
    posrel=positionrelative(*objeta,*objetb);
    coef= ATTRACTION * ((*objeta).attraction) * ((*objetb).attraction)  * pow(norme(posrel),-2);
    
    //F=GmM/r^2
    
    //printf("Attraction %s - %s valeur %g\n",(*objeta).nom,(*objetb).nom,coef);
    
    (*objeta).acceleration=somme((*objeta).acceleration,
    multiplicationscalaire(posrel,-1*coef/(*objeta).masse));
    
    (*objetb).acceleration=somme((*objetb).acceleration,
    multiplicationscalaire(posrel,1*coef/(*objetb).masse));     
  
}

void frottement(PTROBJET objet)
{
        (*objet).acceleration=somme((*objet).acceleration,multiplicationscalaire(positionsuivante(*objet).vitesse,-1*(*objet).frottement));
}

void disparition(PTROBJET objet)
{
    
}

COORD normalecontact(OBJET objeta, OBJET objetb)
{
 	COORD res;
    COORD dir;
        
    if(objeta.forme==RECTANGLE || objetb.forme==RECTANGLE)
    {

        if(abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(1,0)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0.5,0))) && abs(produitscalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(0,1)))<abs(produitscalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0,0.5))))
        {
            dir=inverse(somme(objeta.dimensions,objetb.dimensions));
            
            res=arrondi(multiplicationscalaire(normalisation(multiplication(difference(objeta.position, objetb.position),dir)),sqrt(0.5)));

            res=normalisation(res);

        }
        else
        {

            res=vecteur(0,0);
        }
    }
    else
    {
        if(sqrt(8.)*distance(positionsuivante(objeta).position,positionsuivante(objetb).position)<(norme(objeta.dimensions)+norme(objetb.dimensions)))
        {
            res=difference(positionsuivante(objeta).position,positionsuivante(objetb).position);
          
            res=normalisation(res);
        }
        else
        {
            res=vecteur(0,0);
        }
    }
    if(norme(res)!=0)
    {printf("Normale : ");indiquer(res);printf(" Norme : %g \n",norme(res));}
    
 	return res;
}

COORD positionrelative(OBJET objeta, OBJET objetb)
{
    COORD res;
    res=difference(positionsuivante(objeta).position,positionsuivante(objetb).position);
    //printf("Position relative : ");indiquer(res);printf("\n");
    return res;
}

void interactions(void)
{
    PTRCELLULE pcellulea;
    PTRCELLULE pcelluleb;
    pcellulea=originelisteactifs;
    while(pcellulea!=NULL)
    {
        //indiquer((*(*pcellulea).element).acceleration);printf("\n");


        pcelluleb=(*pcellulea).suivant;
        while(pcelluleb!=NULL)
        {
            //printf("Interaction %s - %s \n",(*(*pcellulea).element).nom,(*(*pcelluleb).element).nom);
            
            //interactions possibles à 2 objets
            gravitation((*pcellulea).element,(*pcelluleb).element); 
            rebond((*pcellulea).element,(*pcelluleb).element);
  

            pcelluleb=(*pcelluleb).suivant;
        }
        //indiquer((*(*pcellulea).element).acceleration);printf("\n");


        //interactions possible à 1 objet 
        frottement((*pcellulea).element);
        disparition((*pcellulea).element);
        
        pcellulea=(*pcellulea).suivant;
    }
}
