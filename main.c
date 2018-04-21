#include "supanoid.h"

int main(void)
{
		
	origineliste=NULL;														
	raquette=NULL;
	fenetre=NULL;

	demanderparametres();
    executerfichier("monde");
    initialisation();
	initialisationgraphique();

    while (!fini) 
    {        
        clavier();
        interactions();
        mouvements();
        dessin();                     
        sleepAWhile((int)(1000*DT));
    }

    cloture();
	cloturegraphique();
    return 1;
}
