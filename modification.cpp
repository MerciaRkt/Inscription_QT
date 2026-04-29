#include "modification.h"
#include "ui_modification.h"

Modification::Modification(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Modification)
{
    ui->setupUi(this);
    connect(ui->continuer, SIGNAL(clicked()),this, SLOT(continuer()));
    connect(ui->annuler, SIGNAL(clicked()),this, SLOT(annuler()));
}

Modification::~Modification()
{
    delete ui;
}

QString Modification::getNom()
{
    return (ui->nouveau_nom->text());
}

QString Modification::getmdp()
{
    return (ui->nouveau_mdp->text());
}

void Modification::continuer()
{
    accept();
}

void Modification::annuler()
{
    reject();
}
