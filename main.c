#include "supanoid.h"

int main(void)
{
    int fini = 0;						
    OBJET balle;
    OBJET balle2, rectangle,petitrectangle;

    balle2=lireobjet("balle");

    balle=lireobjet("balle");
    balle.position.x=400;
    
    rectangle=creerobjet("Rectangle",1,vecteur(400,500),vecteur(0,0),vecteur(0,0),vecteur(300,100),1,1000,1,1,NULL,"aucun",VERT,RECTANGLE);
    
    initialisationgraphiques();

    while (!fini) 
    {
              // boucle infinie
        switch (getLastKeyPressed())
        { 
            case -1:                     // aucune touche pressée
                break;                     // On ne fait rien 
            case VK_LEFT:
                balle.vitesse.x-=0.1;
                break;
            case VK_RIGHT:
                balle.vitesse.x+=0.1;
                break;
            case VK_UP:
                balle.vitesse.y-=0.1; 
                break;
            case VK_DOWN:   
                balle.vitesse.y+=0.1;
                break;
            case VK_ESCAPE:
                fini = 1;      
                break;
            case VK_F1:
                decrire(balle);
                break;
            case VK_F2:
                decrire(balle2);
                break;
        }
        effacer(balle);
    	dessiner(rectangle);
        dessiner(balle);
        dessiner(balle2);
        paint();                       // On affiche le résultat
        sleepAWhile(DT*1000);                // On patiente 5 ms, ce qui fera un affichage
                                       // de 200 images/s, ce qui est largement suffisant
                                       // multiplier ce délai par 10 sur Sun Solaris
        rebond(&balle,&rectangle,collision(balle,rectangle)); 
        rebond(&balle2,&rectangle,collision(balle2,rectangle)); 
        rebond(&balle,&balle2,collision(balle,balle2)); 
    	mouvement(&balle);
    	mouvement(&rectangle);
    	mouvement(&balle2);
    }
  finish();                       // Cette méthode doit toujours être appelée en fin de programme  

  return 1;
}

