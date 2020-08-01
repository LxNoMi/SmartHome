#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <connet.h>
#include <recamara.h>
#include <QMovie>
#include <QMediaPlayer>
#include <QDesktopServices>

#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <recorder.h>
#include <QImage>
#include <http.h>
#include <QHostInfo>


namespace Ui {
class mainwindow;
}

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

    void Init();
    void ConTo();
    void sendData(char type, QString name, QString data);
    void flushcam(QByteArray buffer);
    void flushenv(QString env);
    void recordvoi();
    void recordend();

private slots:
    void on_conButton_clicked();
    void conOver(void);
    void readData(void);
    void readData_env(void);
    void on_conButton_2_clicked();
    void on_lightbitton_clicked();
    void on_windbutton_clicked();
    void on_camarabutton_clicked();
    void on_alarmbutton_clicked();
    void on_resizebutton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_5_pressed();
    void on_pushButton_5_released();
    void on_tvButton_clicked();
    void identify();

private:
    Ui::mainwindow *ui;
    QTcpSocket *socket;
    QTcpSocket *socket_env;
    connet *myNet;
    int BUFSIZE;
    QMovie *movie;
    int conbool;
    QMediaPlayer *player;
    recamara *rcama;
    recorder *rCoder;
    http *myhp;
};

#endif // MAINWINDOW_H
