#include "supanoid.h"

int main(void)
{
    int fini = 0;						
    OBJET balle;
    originelisteactifs=NULL;
    erreur=FALSE;
    DT=0.002;
    
    fenetre=(*lireobjet("fenetre"));
    fenetrepause=(*lireobjet("pause"));

    if(liremonde("monde1")==TRUE)
    {
      
    initialisationgraphiques();
    if(erreur==FALSE)
    {
        printf("Initialisation ok\n");
    }
    else
    {
        printf("Erreurs reperees\n");
    }
    while (!fini) 
    {
              // boucle infinie

        
        switch (getLastKeyPressed())
        { 
            case -1:                     // aucune touche pressée
                break;                     // On ne fait rien 
            case VK_LEFT:
                (*(*originelisteactifs).element).acceleration.x=-SENSIBILITE;
                break;
            case VK_RIGHT:
                (*(*originelisteactifs).element).acceleration.x=SENSIBILITE;
                break;
            case VK_UP:
                (*(*originelisteactifs).element).acceleration.y=-SENSIBILITE; 
                break;
            case VK_DOWN:   
                (*(*originelisteactifs).element).acceleration.y=SENSIBILITE;
                break;
            case VK_ESCAPE:
                fini = 1;      
                break;
            case VK_F1:
                decrire( *(*rechercher("raquette","raquette",0,originelisteactifs)).element  );
                break;
            case VK_F2:
                effacer();
                break;
            case VK_F3:
                DT*=2;
                break;
            case VK_F4:
                DT/=2;
                break;
            case VK_P:
                pause();
                break;
                
        }
               // On patiente 5 ms, ce qui fera un affichage
                                       // de 200 images/s, ce qui est largement suffisant
                                       // multiplier ce délai par 10 sur Sun Solaris
        interactions();
        mouvements();
        effacer();
        dessin();
        paint();                       // On affiche le résultat
        sleepAWhile(1000*DT); 

    }
}
  finish();                       // Cette méthode doit toujours être appelée en fin de programme  

  return 1;
}

