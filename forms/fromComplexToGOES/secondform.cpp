#include "secondform.h"
#include "ui_secondform.h"

SecondForm::SecondForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondForm)
{
    ui->setupUi(this);

    QToolBar* toolbar = new QToolBar(this); // Создаем экземпляр QToolBar
       toolbar->addAction("От комплекса в ГОЭС"); // Добавляем действие в тулбар
       toolbar->addAction("ОТ ГОЭС в комплекс");

       QVBoxLayout* mainLayout = new QVBoxLayout(this); // Создаем вертикальный макет
       mainLayout->setMenuBar(toolbar); // Устанавливаем тулбар в качестве меню-бара макета

       setLayout(mainLayout); // Устанавливаем главный макет в качестве макета для текущего диалогового окна
       connect(toolbar, &QToolBar::actionTriggered, this, &SecondForm::handleAction); // Подключаем сигнал actionTriggered() тулбара к слоту handleAction()

}


SecondForm::~SecondForm()
{
    delete ui;
}

void SecondForm::handleAction(QAction* action)
{
    // Обработка события для каждого действия в тулбаре
    if (action->text() == "От комплекса в ГОЭС")
    {
        emit ToMainWindow();
        this->hide();
    }
    else if (action->text() == "ОТ ГОЭС в комплекс")
    {

    }
}


