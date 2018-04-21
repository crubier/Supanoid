#include "supanoid.h"

PTRCELLULE creercellule(PTROBJET pobjet)
{
    PTRCELLULE res;
    printf("Creer cellule...\n");
    res=malloc(sizeof(CELLULE));
    if(res==NULL)return NULL;
    (*res).element=pobjet;
    (*res).precedent=NULL;
    (*res).suivant=NULL;
    return res;
}

PTRCELLULE dernierecellule(void)
{
    PTRCELLULE pcellulecourante;
    
    printf("Derniere cellule...\n");
    if(origineliste==NULL) return NULL;

    pcellulecourante=origineliste;
    while((*pcellulecourante).suivant!=NULL)
    {
        pcellulecourante=(*pcellulecourante).suivant;
    }
        printf("Derniere cellule...\n");
    return pcellulecourante;
}

BOOLEAN ajoutercellule(PTROBJET pobjet)
{
    PTRCELLULE pcellulecreee;
    printf("Ajouter cellule...\n");
    pcellulecreee=creercellule(pobjet);
    if(origineliste==NULL)
    {
        printf("Creer liste...\n");
        origineliste=pcellulecreee;
        return TRUE;
        printf("He 1 ??\n");
    }
    else
    {
        printf("He 2?? \n");
        return liercellules(dernierecellule(),pcellulecreee);
    }
}

BOOLEAN liercellules(PTRCELLULE cellulea, PTRCELLULE celluleb)
{
    printf("Lier cellules...\n");
    (*cellulea).suivant=celluleb;
    (*celluleb).precedent=cellulea;
    return verifiercellules(cellulea,celluleb);
}

BOOLEAN verifiercellules(PTRCELLULE cellulea, PTRCELLULE celluleb)
{
    printf("Verification lisaison...\n");
    if((*cellulea).suivant==celluleb && (*celluleb).precedent!=cellulea)return FALSE;
    if((*cellulea).precedent==celluleb && (*celluleb).suivant!=cellulea)return FALSE;
    if((*celluleb).suivant==cellulea && (*cellulea).precedent!=celluleb)return FALSE;
    if((*celluleb).precedent==cellulea && (*cellulea).suivant!=celluleb)return FALSE;
    return TRUE;
}

PTRCELLULE rechercher(char* nom, int identifiant)
{
    PTRCELLULE pcellule;
    pcellule=origineliste;
    while((*pcellule).suivant!=NULL)
    {
        if(strcmp((*(*pcellule).element).nom,nom)==0 && (*(*pcellule).element).identifiant==identifiant)return pcellule;
        pcellule=(*pcellule).suivant;
    }
    while((*pcellule).precedent!=NULL)
    {
        if(strcmp((*(*pcellule).element).nom,nom)==0 && (*(*pcellule).element).identifiant==identifiant)return pcellule;
        pcellule=(*pcellule).precedent;
    }
    return NULL;
}

PTRCELLULE elementnumero(int i)
{
    PTRCELLULE pcellule;
    int j;
    while(i!=j && pcellule!=NULL)
    {
        if(j==i)
        {
            return pcellule;
        }
        else
        {
            if(j<i)
            {
                j++;
                pcellule=(*pcellule).precedent;
            }
            else
            {
                j++;
                pcellule=(*pcellule).suivant;
            }
        }
    }
    return NULL;
}
