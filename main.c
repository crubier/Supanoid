#include "supanoid.h"

int main(int argc, char *argv[])
{
	
	origineliste=NULL;														
	raquette=NULL;
	fenetre=NULL;
	modefonctionnement=0;

	demanderparametres(argc,argv);
    executerfichier("monde");
    initialisation();
	initialisationgraphique();
    executerfichier("initialisation");
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
