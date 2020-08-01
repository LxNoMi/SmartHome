#ifndef HTTP_H
#define HTTP_H

#include <QWidget>
#include <QNetworkAccessManager>    //加载网络请求头文件
#include <QNetworkReply>
#include <QNetworkRequest>      //加载发送请求头文件
#include <QJsonDocument>
#include <QJsonParseError>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QBuffer>
#include <QFile>

namespace Ui {
class http;
}

class http : public QWidget
{
    Q_OBJECT

public:
    explicit http(QWidget *parent = nullptr);
    ~http();
    void get_access_taken();
    void myPost(QBuffer *m_buffer);

    QString RESULT;

signals:
    void anwser();

private slots:
    void oneProcessFinished(QNetworkReply*);

private:
    Ui::http *ui;
    QNetworkAccessManager *manage;
    QString access_taken;
    QString m_location;

};

#endif // HTTP_H
