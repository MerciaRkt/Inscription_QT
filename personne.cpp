#include "personne.h"

Personne::Personne() {}

void Personne:: set_nom(QString name)
{
    nom = name ;
}

void Personne::set_mdp(QString password)
{
    mdp = password ;
}

QString Personne::get_nom()
{
    return(nom) ;
}

QString Personne::get_mdp()
{
    return(mdp) ;
}
