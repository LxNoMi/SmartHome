#ifndef RECAMARA_H
#define RECAMARA_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class recamara;
}

class recamara : public QWidget
{
    Q_OBJECT

public:
    explicit recamara(QWidget *parent = nullptr);
    ~recamara();

    QLabel *label;

private:
    Ui::recamara *ui;
    QVBoxLayout *vbox;
    QHBoxLayout *hbox;
    QPushButton *pushbutton;
};

#endif // RECAMARA_H
