#include "supanoid.h"

COORD vecteur(float x, float y)
{
    COORD res;
    res.x=x;
    res.y=y;
    return res;
}
    
COORD somme(COORD a, COORD b)
{
    COORD res;
    res.x=a.x+b.x;
    res.y=a.y+b.y;
    return res;
}

COORD oppose(COORD a)
{
    COORD res;
    res.x=-a.x;
    res.y=-a.y;
    return res;
}

COORD difference(COORD a, COORD b)
{
    return somme(a,oppose(b));
}

COORD inverse(COORD a)
{
    COORD res;
    if(a.x==0 || a.y==0) return a;
    res.x=1/a.x;
    res.y=1/a.y;
    return res;
}

COORD multiplication(COORD a, COORD b)
{
    COORD res;
    res.x=a.x*b.x;
    res.y=a.y*b.y;
    return res;
}

COORD multiplicationscalaire(COORD a, float k)
{
    return multiplication(a,vecteur(k,k));
}

float scalaire(COORD a, COORD b)
{
    float res;
    res=a.x*b.x+a.y*b.y;
    return res;
}

COORD normalisation(COORD a)
{
    if(norme(a)==0)return a;
    return multiplicationscalaire(a,1/norme(a));
}

float distance(COORD a, COORD b)
{
    return norme(difference(a,b));
}

float norme(COORD a)
{
    return sqrt(scalaire(a,a));
}

float distanceaxe(COORD a, COORD b, COORD axe)
{
    return scalaire(difference(a,b),normalisation(axe));
}

COORD arrondi(COORD a)
{
    return vecteur(round(a.x),round(a.y));
}
