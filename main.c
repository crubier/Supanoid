#include "supanoid.h"

int main(void)
{
		
	DT = 0.002;
	origineliste=NULL;														
	raquette=NULL;
	fenetre=NULL;

	strcpy(repertoire,"mondes/supanoid");
	journal=fopen("mondes/supanoid/journal.supanoid","w+");
    executerfichier("monde");

    initialisation();

    while (!fini) 
    {        
        clavier();
        interactions();
        mouvements();
        effacer();
        dessin();
                     
        sleepAWhile((int)(1000*DT));
    }

    cloture();

    return 1;
}
