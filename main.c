#include "supanoid.h"

int main(void)
{
    int fini = 0;						
    OBJET balle;
    origineliste=NULL;
    fenetre=(*lireobjet("fenetre"));

    if(liremonde("monde1")==TRUE)
    {
      
    initialisationgraphiques();
    printf("Initialisation ok\n");
    while (!fini) 
    {
              // boucle infinie
        switch (getLastKeyPressed())
        { 
            case -1:                     // aucune touche pressée
                break;                     // On ne fait rien 
            case VK_LEFT:
                (*(*origineliste).element).vitesse.x-=0.1;
                break;
            case VK_RIGHT:
                (*(*origineliste).element).vitesse.x+=0.1;
                break;
            case VK_UP:
                (*(*origineliste).element).vitesse.y-=0.1; 
                break;
            case VK_DOWN:   
                (*(*origineliste).element).vitesse.y+=0.1;
                break;
            case VK_ESCAPE:
                fini = 1;      
                break;
            case VK_F1:
                decrire((*(*origineliste).element));
                break;
            case VK_F2:
                decrire((*(*origineliste).element));
                break;
        }
        effacer();
        dessin();
        paint();                       // On affiche le résultat
        sleepAWhile(DT*1000);                // On patiente 5 ms, ce qui fera un affichage
                                       // de 200 images/s, ce qui est largement suffisant
                                       // multiplier ce délai par 10 sur Sun Solaris
        interactions();
        mouvements();
        /*rebond(&balle,&balle2,collision(balle,balle2)); 
    	mouvement(&balle);
    	mouvement(&balle2);*/
    }
}
  finish();                       // Cette méthode doit toujours être appelée en fin de programme  

  return 1;
}

