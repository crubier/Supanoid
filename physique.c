#include "supanoid.h"

void mouvement(PTROBJET objet)
{
    (*objet)=positionsuivante((*objet));
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
      
      /*float nx, ny, nn;
 	 float Ma, Mb, M;
 	 float Va0x, Va0y, Vb0x, Vb0y;
 	 float Va1x, Va1y, Vb1x, Vb1y;
 	 float DV0x, DV0y;
 	 float temp;
 	 
 	 Ma=(*objeta).masse; 
	 Mb=(*objetb).masse;
	 Va0x=(*objeta).vitesse.x;
  	 Va0y=(*objeta).vitesse.y;
  	 Vb0x=(*objetb).vitesse.x;
	 Vb0y=(*objetb).vitesse.y;
	 DV0x=Va0x-Vb0x;
 	 DV0y=Va0y-Vb0y;
 	 nx=normale.x;
	 ny=normale.y;
	 nn=sqrt(pow(nx,2) + pow(ny,2));
 	 M=Ma+Mb;
 	 
	   	 
 	 if(nn!=0)
 	 {
 		nn=1/nn;

	 	 Va1x=(1/M);
	 	 Va1y=(1/M);
	 	 Vb1x=(1/M);
	 	 Vb1y=(1/M);

	 	 temp=Ma*Va0x-Mb*(2*nx*nx*DV0x*nn+2*nx*ny*DV0y*nn-Va0x);
		 Va1x=Va1x*temp;
	
		 temp=Ma*Va0y-Mb*(2*nx*ny*DV0x*nn+2*ny*ny*DV0y*nn-Va0y);
		 Va1y=Va1y*temp;
		 
 	 	 temp=Mb*Vb0x-Ma*(2*nx*nx*DV0x*nn+2*nx*ny*DV0y*nn-Vb0x);
		 Vb1x=-Vb1x*temp;
		 
		 temp=Mb*Vb0y-Ma*(2*nx*ny*DV0x*nn+2*ny*ny*DV0y*nn-Vb0y);
		 Vb1y=-Vb1y*temp;
	 	 
	 	 (*objeta).vitesse.x=Va1x; 
	 	 (*objeta).vitesse.y=Va1y;
	 	 (*objetb).vitesse.x=Vb1x;
	 	 (*objetb).vitesse.y=Vb1y;
	 	 
	 	 Va1x=(1/M);
	 	 Va1y=(1/M);
	 	 Vb1x=(1/M);
	 	 Vb1y=(1/M);

	 	 temp=Ma*Va0x-Mb*(2*nx*nx*DV0x*nn+2*nx*ny*DV0y*nn-Va0x);
		 Va1x=Va1x*temp;
	
		 temp=Ma*Va0y-Mb*(2*nx*ny*DV0x*nn+2*ny*ny*DV0y*nn-Va0y);
		 Va1y=Va1y*temp;
		 
 	 	 temp=Mb*Vb0x-Ma*(2*nx*nx*DV0x*nn+2*nx*ny*DV0y*nn-Vb0x);
		 Vb1x=-Vb1x*temp;
		 
		 temp=Mb*Vb0y-Ma*(2*nx*ny*DV0x*nn+2*ny*ny*DV0y*nn-Vb0y);
		 Vb1y=-Vb1y*temp;
	 	 
	 	 (*objeta).vitesse.x=Va1x; 
	 	 (*objeta).vitesse.y=Va1y;
	 	 (*objetb).vitesse.x=Vb1x;
	 	 (*objetb).vitesse.y=Vb1y;
	 	 
        }
	 	 */
		  
	 
}

COORD collision(OBJET objeta, OBJET objetb)
{
 	COORD res,dir;
        
    if(objeta.forme==RECTANGLE || objetb.forme==RECTANGLE)
    {
    /*distanceaxe(positionsuivante(objeta).position,positionsuivante(objetb).position,difference(objeta.vitesse,objetb.vitesse))<norme(somme(objeta.dimensions,objetb.dimensions)))*/
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
