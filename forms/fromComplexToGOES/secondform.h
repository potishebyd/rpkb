#ifndef SECONDFORM_H
#define SECONDFORM_H

#include <QDialog>
#include <QLayout>
#include "QToolBar"

namespace Ui {
class SecondForm;
}

class SecondForm : public QDialog
{
    Q_OBJECT
signals:
    void ToMainWindow();
public:
    explicit SecondForm(QWidget *parent = nullptr);
     friend void QLayout::setMenuBar ( QWidget * widget );
    ~SecondForm();


private slots:   
     void handleAction(QAction* action);


private:
    Ui::SecondForm *ui;
    QToolBar* toolbar;
};


#endif // SECONDFORM_H
