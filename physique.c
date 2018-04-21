#include "supanoid.h"

void mouvement(PTROBJET objet)
{
    (*objet)=positionsuivante((*objet));
}

void mouvements(void)
{
    PTRCELLULE pcellule;
    pcellule=origineliste;
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
    res.acceleration=multiplicationscalaire(res.vitesse,-1*res.frottement);
 	res.vitesse=somme(res.vitesse,res.acceleration);
 	res.position=somme(res.position,res.vitesse);
 	return res;
}

void rebond(PTROBJET objeta, PTROBJET objetb, COORD normale)
{
    
    
    if(norme(normale)!=0)
 	{
        float coef;
        COORD vitessea,vitesseb;
        
        coef=-1/(((*objeta).masse+(*objetb).masse)*norme(normale)*norme(normale));      
  
        vitessea=
        somme
        (
            (*objeta).vitesse,
            multiplicationscalaire
            (    
                normale,
                2*coef*((*objetb).masse)*scalaire(difference((*objeta).vitesse,(*objetb).vitesse),normale)
            )
        );
        
        vitesseb=
        somme
        (
            (*objetb).vitesse,
            multiplicationscalaire
            (    
                normale,
                2*coef*((*objeta).masse)*scalaire(difference((*objetb).vitesse,(*objeta).vitesse),normale)
            )
        );
        
        (*objeta).vitesse=vitessea;
        (*objetb).vitesse=vitesseb;
       
    }  
      
  
}

COORD collision(OBJET objeta, OBJET objetb)
{
 	COORD res,dir;
        
    if(objeta.forme==RECTANGLE || objetb.forme==RECTANGLE)
    {
        if(abs(scalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(1,0)))<abs(scalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0.5,0))) && abs(scalaire(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),vecteur(0,1)))<abs(scalaire(somme(objeta.dimensions,objetb.dimensions),vecteur(0,0.5))))
        {
            dir=inverse(somme(objeta.dimensions,objetb.dimensions));
            
            res=arrondi(multiplicationscalaire(normalisation(multiplication(difference(positionsuivante(objeta).position, positionsuivante(objetb).position),dir)),sqrt(0.5)));

            res=multiplicationscalaire(normalisation(res),(objeta.rebondissement)*(objetb.rebondissement));

        }
        else
        {
            res=vecteur(0,0);
        }
    }
    else
    {
        if(2*distance(somme(objeta.position,objeta.vitesse),somme(objetb.position,objetb.vitesse))<norme(objeta.dimensions)+norme(objetb.dimensions))
        {
            res=difference(positionsuivante(objeta).position,positionsuivante(objetb).position);
          
            res=multiplicationscalaire(normalisation(res),(objeta.rebondissement)*(objetb.rebondissement));

        }
        else
        {
            res=vecteur(0,0);
        }
    }
    
 	return res;
}

void interactions(void)
{
    PTRCELLULE pcellulea;
    PTRCELLULE pcelluleb;
    pcellulea=origineliste;
    while(pcellulea!=NULL)
    {
        pcelluleb=(*pcellulea).suivant;
        while(pcelluleb!=NULL)
        {
            rebond((*pcellulea).element,(*pcelluleb).element,collision(*(*pcellulea).element,*(*pcelluleb).element));
            pcelluleb=(*pcelluleb).suivant;
        }
        pcellulea=(*pcellulea).suivant;
    }
}
