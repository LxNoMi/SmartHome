#ifndef CONNET_H
#define CONNET_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class connet;
}

class connet : public QWidget
{
    Q_OBJECT

public:
    explicit connet(QWidget *parent = nullptr);
    ~connet();

    qint64 myPort;
    qint64 myPort1;
    QString myIp;

private slots:
    void on_commitButton_clicked();

signals:
    void commited();

private:
    Ui::connet *ui;
};

#endif // CONNET_H
