#include "recamara.h"
#include "ui_recamara.h"

recamara::recamara(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recamara)
{
    ui->setupUi(this);

    this->vbox = new QVBoxLayout();
    this->hbox = new QHBoxLayout();
    this->label = new QLabel();
    this->pushbutton = new QPushButton();


    this->label->setPixmap(QPixmap(":/picture/backimg.jpg"));
    this->label->setScaledContents(true);
    this->pushbutton->setText("+");

    this->vbox->addWidget(this->label);
    this->vbox->addWidget(this->pushbutton);
    ui->groupBox->setLayout(vbox);


}

recamara::~recamara()
{
    delete ui;
}
