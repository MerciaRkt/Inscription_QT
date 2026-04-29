#ifndef PERSONNE_H
#define PERSONNE_H
#include <QString>

class Personne
{
    private:
        QString nom ;
        QString mdp;

    public:
        Personne();
        void set_nom (QString name);
        void set_mdp (QString password);
        QString get_nom ();
        QString get_mdp();

};

#endif // PERSONNE_H
