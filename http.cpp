#include "http.h"
#include "ui_http.h"

http::http(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::http)
{
    ui->setupUi(this);
    this->hide();

    this->m_location = "D:\\recoder.wav";
    this->manage = new QNetworkAccessManager(this);       //分配空间
    this->access_taken = "24.98b2aaafb8a25299e9d59f6aa3315913.2592000.1575008009.282335-17648787";
    connect(manage,SIGNAL(finished(QNetworkReply*)),this,SLOT(oneProcessFinished(QNetworkReply*)));

    //get_access_taken(); /*该函数用于获取access_taken, 每月调用一次刷新access_taken*/
}

http::~http()
{
    delete ui;
}

//绑定完成信号函数
void http::oneProcessFinished(QNetworkReply *reply)
{
    QString str = reply->readAll();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(str.toUtf8(), &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
        return;
    }
    QJsonObject rootObj = jsonDoc.object();

    if(rootObj.contains("access_token")){
        this->access_taken = rootObj.value("access_token").toString();
        qDebug()<<"获取到：access_token为："<<this->access_taken;
    }
    else {
        //实现其他数据
        QString result = ((rootObj.value("result").toArray()).at(0)).toString();
        qDebug()<<"识别结果:"<< result;
        RESULT = result;
        QMessageBox::information(this, "识别结果", result);
        emit anwser();
    }
}

void http::get_access_taken()
{
    qDebug()<<"开始获取access_taken";
    QString url = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=GExs1RKuX2CBffTS6KMwhb4n&client_secret=T4SPq49aLPKFmcbQgGjoE5AMG7Gak6A8";     //获取地址
    manage->get(QNetworkRequest(QUrl(url)));
}

void http::myPost(QBuffer *m_buffer)
{
    qDebug()<<"语音识别";
    const auto &sendData = m_buffer->data();

    //封装请求
    QNetworkRequest request(QUrl("http://vop.baidu.com/server_api"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json")); //设置格式头

    QJsonObject json;
    json.insert("format", "pcm");
    json.insert("rate", "16000");
    json.insert("channel", "1");
    json.insert("cuid", "50-7B-9D-F8-A8-23");
    json.insert("token", access_taken);
    qDebug()<<"key:"<<QString(access_taken);
    json.insert("dev_pid", "1536");
    json.insert("speech", QString(sendData.toBase64()));
    json.insert("len", sendData.size());

    //发起请求
    manage->post(request, QJsonDocument(json).toJson());
}
