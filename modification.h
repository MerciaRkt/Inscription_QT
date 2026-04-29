#ifndef MODIFICATION_H
#define MODIFICATION_H

#include <QDialog>

namespace Ui {
class Modification;
}

class Modification : public QDialog
{
    Q_OBJECT

public:
    explicit Modification(QWidget *parent = nullptr);
    ~Modification();
    QString getNom();
    QString getmdp();

private:
    Ui::Modification *ui;

private slots:
    void continuer();
    void annuler();

};

#endif // MODIFICATION_H
