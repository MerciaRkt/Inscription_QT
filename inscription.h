#ifndef INSCRIPTION_H
#define INSCRIPTION_H
#include "personne.h"
#include "modification.h"

#include <QMainWindow>
#include <QVector>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Inscription;
    }
        QT_END_NAMESPACE

        class Inscription : public QMainWindow
        {
                Q_OBJECT

            public:
                Inscription(QWidget *parent = nullptr);
                ~Inscription();

            private slots:
                void inscrire();
                void lister();
                void ajouter(Personne p);
                void charger ();
                void supprimer();
                void sauvegarder();
                void modifier();


            private:
                Ui::Inscription *ui;
                QVector<Personne> T ;
                Modification *modif;

        };

#endif // INSCRIPTION_H
