#include <stdlib.h>

#include "graphic.h"
#include "key.h"

int main(void)
{
  int x=400,y = 400;                     // ordonnée du ballon (haut du ballon)
  int fini = 0;                    // valeur booléenne initialisée à FAUX

  start(800, 800);                 // création d'une fenêtre 800 x 800
  setBackgroundColor(BLACK);       // couleur de fond = NOIR
  setForegroundColor(RED);         // couleur de 1er plan = ROUGE
  clearRect(0, 0, 800, 800);       // la fenêtre est painte entièrement en noir 

  registerKeyPressed(VK_LEFT);       // Enregistrement de la touche Flèche Haut
  registerKeyPressed(VK_RIGHT);     // Enregistrement de la touche Flèche Bas
  registerKeyPressed(VK_UP);       // Enregistrement de la touche Flèche Haut
  registerKeyPressed(VK_DOWN); 

  fillOval(x,y , 40, 40);        // Dessin du ballon de diamètre 40, à l'abscisse
                                   // 400 et à l'ordonnée y (angle gauche-haut)

  while (!fini) {                  // boucle infinie
    switch (getLastKeyPressed()) { // Récupération de la touche pressée en cours
      case -1:                     // aucune touche pressée
        break;                     // On ne fait rien 
      case VK_LEFT:                  // Si la touche pressée est la flèche Haut
        x--;                       // On décrémente y, le ballon ira vers le haut
        break;
      case VK_RIGHT:                // Si la touche pressée est la flèche Bas
        x++;                       // On incrémente y, le ballon ira vers le bas
        break;
     case VK_UP:                  // Si la touche pressée est la flèche Haut
        y--;                       // On décrémente y, le ballon ira vers le haut
        break;
      case VK_DOWN:                // Si la touche pressée est la flèche Bas
        y++;                       // On incrémente y, le ballon ira vers le bas
        break;
      case VK_ESCAPE:              // par défaut la touche "escape" est toujours écoutée
        fini = 1;                  // sortira de la boucle à la prochaine itération
        break;
    }
    clearRect(0, 0, 800, 800);     // On efface la fenêtre (toute en noir donc)
    fillOval(x, y, 40, 40);      // On redessine le ballon à sa nouvelle position
    paint();                       // On affiche le résultat
    sleepAWhile(5);                // On patiente 5 ms, ce qui fera un affichage
                                   // de 200 images/s, ce qui est largement suffisant
                                   // multiplier ce délai par 10 sur Sun Solaris
  }
  finish();                       // Cette méthode doit toujours être appelée en fin de programme  

  return 1;
}

