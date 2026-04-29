#include "inscription.h"
#include "ui_inscription.h"
#include "personne.h"
#include "modification.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QShortcut>

Inscription::Inscription(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);
    connect(ui->inscrire,SIGNAL(clicked()),this,SLOT(inscrire()));
    connect(ui->supprimer , SIGNAL(clicked()),this,SLOT(supprimer()));
    connect(ui->modifier, SIGNAL(clicked()) , this , SLOT(modifier()));

    QShortcut *enregistrer = new QShortcut(QKeySequence("Ctrl+S"), this);
    connect(enregistrer, SIGNAL(activated()),this, SLOT(inscrire()));

    QShortcut *quitter = new QShortcut(QKeySequence("Ctrl+Q"), this);
    connect(quitter, SIGNAL(activated()),this, SLOT(close()));

    QShortcut *supprimer = new QShortcut(QKeySequence("Ctrl+D"), this);
    connect(supprimer, SIGNAL(activated()),this, SLOT(supprimer()));

    QShortcut *modifier = new QShortcut(QKeySequence("Ctrl+M"), this);
    connect(modifier, SIGNAL(activated()),this, SLOT(modifier()));

    charger();
    lister() ;
}


Inscription::~Inscription()
{
    delete ui;
}

void Inscription::inscrire()
{
    Personne p ;
    QString nom , mdp ;

    nom = ui->nom->text();
    mdp = ui->mdp->text();

    p.set_nom(nom);
    p.set_mdp(mdp);

    T.push_back(p);
    ajouter(p);
    lister();

    ui->nom->clear();
    ui->mdp->clear();
}

void Inscription:: ajouter(Personne p)
{
    QFile pf ("inscrits.csv");
    if (pf.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream fichier(&pf);

        fichier << p.get_nom() << ";" << p.get_mdp() <<"\n" ;
        pf.close();
    }
}


void Inscription:: charger ()
{
    Personne p ;
    QString ligne ;
    QFile pf("inscrits.csv");

    if (pf.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream fichier(&pf);
        T.clear();

        while (fichier.atEnd() == false)
        {
            ligne = fichier.readLine();
            QStringList partie = ligne.split(";");
            if (partie.size() >= 2)
            {
                p.set_nom(partie[0]);
                p.set_mdp(partie[1]);
                T.push_back(p);
            }
        }
        pf.close();
    }
}

void Inscription:: supprimer()
{
    QVector <Personne> :: iterator it ;
    int i;
    i=0;
    for (it = T.begin() ; it != T.end() ; ++ it )
    {
        if ((it->get_nom() == ui->nom->text()) && (it->get_mdp() == ui->mdp->text()))
        {
            ui->nom->clear();
            ui->mdp->clear();
            T.erase(T.begin() + i);
            sauvegarder();
            lister();
            return;
        }
        i++;
    }
    ui->nom->clear();
    ui->mdp->clear();
    QMessageBox::information(this , "Suppression" ,"Cette personne n'est pas dans la liste");
}


void Inscription :: sauvegarder()
{
    QVector <Personne> :: iterator it ;
    QFile pf ("inscrits.csv");

    if (pf.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream fichier (&pf);

        for (it = T.begin() ; it != T.end() ; ++ it )
        {
            fichier << it->get_nom() << ";" << it->get_mdp() << "\n" ;
        }
        pf.close();
    }

}


void Inscription::lister()
{
    QVector <Personne> :: iterator it ;

    ui->liste->clear();
    for (it = T.begin() ; it != T.end() ; ++ it )
    {
        ui->liste->addItem(it->get_nom());
    }
}



void Inscription::modifier()
{
    QString nouveauNom , nouveauMdp ;
    QVector <Personne> :: iterator it ;
    Modification modif(this);

    for (it = T.begin() ; it != T.end() ; ++ it )
    {
        if (it->get_nom() == ui->nom->text() && it->get_mdp() == ui->mdp->text())
        {
            if (modif.exec() == QDialog::Accepted)
            {
                nouveauNom = modif.getNom();
                nouveauMdp = modif.getmdp();

                for (it = T.begin() ; it != T.end() ; ++ it )
                {
                    if (it->get_nom() == ui->nom->text() && it->get_mdp() == ui->mdp->text())
                    {
                        it->set_nom(nouveauNom);
                        it->set_mdp(nouveauMdp);
                        break;
                    }
                }

                ui->nom->clear();
                ui->mdp->clear();
                sauvegarder();
                lister();
            }
            else
            {
                ui->nom->clear();
                ui->mdp->clear();
            }
            return;
        }
    }

    ui->nom->clear();
    ui->mdp->clear();
    QMessageBox::information(this , "Modification" ,"Cette personne n'est pas dans la liste");
}
