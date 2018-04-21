#include "supanoid.h"

int main(void)
{
    int fini = 0;						
    OBJET balle,balle2, rectangle,petitrectangle;
    char* temp;

    balle=creerobjet("Balle",3,vecteur(400,400),vecteur(0,0),vecteur(0,0),vecteur(10,10),"Aucun",NULL,1,1,0.01,1,CERCLE);
    balle2=creerobjet("Balle",4,vecteur(400,300),vecteur(0,0),vecteur(0,0),vecteur(40,40),"Aucun",NULL,1,10,0.02,1,CERCLE);
    petitrectangle=creerobjet("PetitRectangle",6,vecteur(400,600),vecteur(0,0),vecteur(0,0),vecteur(100,10),"Aucun",NULL,1,1000,1,1,RECTANGLE);
    rectangle=creerobjet("Rectangle",0,vecteur(400,500),vecteur(0,0),vecteur(0,0),vecteur(300,100),"Aucun",&petitrectangle,1,1000,1,1,RECTANGLE);

    start(800, 800);                 
    setBackgroundColor(BLACK);        
    clearRect(0, 0, 800, 800);      

    registerKeyPressed(VK_LEFT);       
    registerKeyPressed(VK_RIGHT);     
    registerKeyPressed(VK_UP);       
    registerKeyPressed(VK_DOWN); 
    registerKeyPressed(VK_F1); 
    registerKeyPressed(VK_F2); 

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
                decrire(rectangle);
                break;
        }
        effacer(balle);
    	dessiner(rectangle);
        dessiner(balle);
        dessiner(balle2);
        paint();                       // On affiche le résultat
        sleepAWhile(5);                // On patiente 5 ms, ce qui fera un affichage
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

