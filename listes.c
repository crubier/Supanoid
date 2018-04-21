#include "supanoid.h"

PTRCELLULE creercellule(PTROBJET pobjet)
{
    PTRCELLULE res;
    printf("Creer cellule...");
    res=malloc(sizeof(CELLULE));
    if(res==NULL)return NULL;
    (*res).element=pobjet;
    (*res).precedent=NULL;
    (*res).suivant=NULL;
    printf("OK\n");
    return res;
}

PTRCELLULE premierecellule(void)
{
    PTRCELLULE pcellulecourante;
    
    if(originelisteactifs==NULL) return NULL;

    pcellulecourante=originelisteactifs;
    while((*pcellulecourante).precedent!=NULL)
    {
        pcellulecourante=(*pcellulecourante).precedent;
    }
    return pcellulecourante;
}

PTRCELLULE dernierecellule(void)
{
    PTRCELLULE pcellulecourante;
    
    if(originelisteactifs==NULL) return NULL;

    pcellulecourante=originelisteactifs;
    while((*pcellulecourante).suivant!=NULL)
    {
        pcellulecourante=(*pcellulecourante).suivant;
    }
    return pcellulecourante;
}

void ajoutercellule(PTROBJET pobjet, PTRCELLULE origine)
{
    PTRCELLULE pcellulecreee;
    printf("Ajouter cellule...");
    printf("OK\n");
    pcellulecreee=creercellule(pobjet);
    if(origine==NULL)
    {
        printf("Creer liste...");
        origine=pcellulecreee;
        printf("OK\n");
        return TRUE;
    }
    else
    {
        return liercellules(dernierecellule(),pcellulecreee);
    }
}

void supprimercellule(PTRCELLULE pcellule, PTRCELLULE origine)
{
    if(pcellule!=NULL)
    {
        if((*pcellule).suivant!=NULL && (*pcellule).precedent!=NULL)
        {
            (*(*pcellule).precedent).suivant=(*pcellule).suivant;
            (*(*pcellule).suivant).precedent=(*pcellule).precedent;
        }
        else
        {
            if((*pcellule).suivant==NULL && (*pcellule).precedent==NULL)
            {
                origine=NULL;
            }
            else
            {
                if((*pcellule).suivant==NULL)
                {
                    (*(*pcellule).precedent).suivant=(*pcellule).suivant;
                }
                else
                {
                    (*(*pcellule).precedent).suivant=(*pcellule).suivant;
                }     
            }
        }
        (*pcellule).precedent=NULL;
        (*pcellule).suivant=NULL;
    }
}

BOOLEAN liercellules(PTRCELLULE cellulea, PTRCELLULE celluleb)
{
    printf("Lier cellules...");
    (*cellulea).suivant=celluleb;
    (*celluleb).precedent=cellulea;
    printf("OK\n");
    return verifiercellules(cellulea,celluleb);
}

BOOLEAN verifiercellules(PTRCELLULE cellulea, PTRCELLULE celluleb)
{
    printf("Verification lisaison...");
    if((*cellulea).suivant==celluleb && (*celluleb).precedent!=cellulea)return FALSE;
    if((*cellulea).precedent==celluleb && (*celluleb).suivant!=cellulea)return FALSE;
    if((*celluleb).suivant==cellulea && (*cellulea).precedent!=celluleb)return FALSE;
    if((*celluleb).precedent==cellulea && (*cellulea).suivant!=celluleb)return FALSE;
    printf("OK\n");
    return TRUE;
}

PTRCELLULE rechercher(char* type, char* nom, int identifiant)
{
    PTRCELLULE pcellule;
    pcellule=originelisteactifs;
    while((*pcellule).suivant!=NULL)
    {
        if(strcmp((*(*pcellule).element).type,type)==0 && strcmp((*(*pcellule).element).nom,nom)==0 && (*(*pcellule).element).identifiant==identifiant)return pcellule;
        pcellule=(*pcellule).suivant;
    }
    while((*pcellule).precedent!=NULL)
    {
        if(strcmp((*(*pcellule).element).type,type)==0 && strcmp((*(*pcellule).element).nom,nom)==0 && (*(*pcellule).element).identifiant==identifiant)return pcellule;
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
