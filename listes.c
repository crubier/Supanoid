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

PTRCELLULE premierecellule(PTRCELLULE origineliste)
{
    PTRCELLULE pcellulecourante;
    
    if(origineliste==NULL) return NULL;

    pcellulecourante=origineliste;
    while((*pcellulecourante).precedent!=NULL)
    {
        pcellulecourante=(*pcellulecourante).precedent;
    }
    return pcellulecourante;
}

PTRCELLULE dernierecellule(PTRCELLULE origineliste)
{
    PTRCELLULE pcellulecourante;
    
    if(origineliste==NULL) return NULL;

    pcellulecourante=origineliste;
    while((*pcellulecourante).suivant!=NULL)
    {
        pcellulecourante=(*pcellulecourante).suivant;
    }
    return pcellulecourante;
}

void ajoutercellule(PTROBJET pobjet, PTRCELLULE* porigineliste)
{
    PTRCELLULE pcellulecreee;
    printf("Ajouter cellule...");
    printf("OK\n");
    pcellulecreee=creercellule(pobjet);
    if((*porigineliste)==NULL)
    {
        printf("Creer liste...");
        *porigineliste=pcellulecreee;
        printf("OK\n");
    }
    else
    {
        liercellules(dernierecellule(*porigineliste),pcellulecreee);
    }
}

void supprimercellule(PTRCELLULE pcellule, PTRCELLULE* porigineliste)
{
    if(pcellule!=NULL)
    {
        if((*pcellule).suivant!=NULL && (*pcellule).precedent!=NULL)
        {
            *porigineliste=premierecellule(*porigineliste);
            (*(*pcellule).precedent).suivant=(*pcellule).suivant;
            (*(*pcellule).suivant).precedent=(*pcellule).precedent;
        }
        else
        {
            if((*pcellule).suivant==NULL && (*pcellule).precedent==NULL)
            {
                *porigineliste=NULL;
            }
            else
            {
                if((*pcellule).suivant==NULL)
                {
                    *porigineliste=premierecellule(*porigineliste);
                    (*(*pcellule).precedent).suivant=(*pcellule).suivant;
                }
                else
                {
                    *porigineliste=premierecellule(*porigineliste);
                    (*(*pcellule).precedent).suivant=(*pcellule).suivant;
                }     
            }
        }
        (*pcellule).precedent=NULL;
        (*pcellule).suivant=NULL;
    }
}

void deplacercellule(PTRCELLULE pcellule, PTRCELLULE* poriginelistea, PTRCELLULE* poriginelisteb)
{
    ajoutercellule((*pcellule).element,poriginelisteb);
    supprimercellule(pcellule,poriginelistea);
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

PTRCELLULE rechercher(char* type, char* nom, int identifiant, PTRCELLULE origineliste)
{
    PTRCELLULE pcellule;
    pcellule=origineliste;
    while((*pcellule).suivant!=NULL)
    {
        if(strcmp((*(*pcellule).element).type,type)==0 && strcmp((*(*pcellule).element).nom,nom)==0 && (*(*pcellule).element).identifiant==identifiant)return pcellule;
        pcellule=(*pcellule).suivant;
    }
    pcellule=origineliste;
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
