#include "mainwindow.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    Init();

    ConTo();
}

mainwindow::~mainwindow() //析构
{
    delete ui;
}

//初始化
void mainwindow::Init()
{
    this->BUFSIZE = 614400;
    this->conbool = 0;
    this->myhp = new http(this);

    this->socket = new QTcpSocket(this);
    this->socket_env = new QTcpSocket(this);
    this->myNet = new connet();
    this->rcama = new recamara();
    this->rcama->hide();
    this->movie = new QMovie(":/picture/robort.gif");

    this->player = new QMediaPlayer(this);
    player->setVolume(100);

    this->rCoder = new recorder(this);


    this->myNet->hide();
    this->setWindowTitle("智能管家");
    this->setWindowIcon(QIcon(":/picture/icon.png"));
    ui->robotLabel->setMovie(movie);
    ui->robotLabel->setScaledContents(true);
    ui->camaLabel->setScaledContents(true);
    movie->start();

}

//连接信号与槽
void mainwindow::ConTo()
{
    connect(this->myNet,SIGNAL(commited()), this, SLOT(conOver()));
    QObject::connect(this->socket, &QTcpSocket::readyRead, this, &mainwindow::readData);
    QObject::connect(this->socket_env, &QTcpSocket::readyRead, this, &mainwindow::readData_env);
    QObject::connect(this->myhp, SIGNAL(anwser()), this, SLOT(identify()));
}

void mainwindow::on_conButton_clicked()//点击连接
{
    if(0 == conbool){
        ui->conButton_2->setIcon(QIcon(":/picture/conout1.png"));
        this->myNet->show();
    }
    else{
        ui->conButton_2->setIcon(QIcon(":/picture/conout1.png"));
        conbool = 0;
        this->socket->disconnectFromHost();
        this->socket_env->disconnectFromHost();
    }

}

//连接完成
void mainwindow::conOver()
{
    this->socket->connectToHost(this->myNet->myIp,this->myNet->myPort);
    this->socket_env->connectToHost(this->myNet->myIp, this->myNet->myPort1);
    ui->conButton_2->setIcon(QIcon(":/picture/conin1.png"));
    conbool=1;
}

//发送数据
void mainwindow::sendData(char type, QString name, QString data)
{
    QString text = "";
    text.append(type);
    text.append('#');
    text.append(&name);
    text.append('#');
    text.append(&data);
    this->socket_env->write(data.toUtf8());
    qDebug()<<"发送："<<data;
}

//读取数据
void mainwindow::readData()
{
    static QByteArray BUF;
    static QByteArray buf;

    //读取数据
    buf = socket->readAll();

    //加入缓存
    if( (BUF.size()+buf.size()) >=614400 )
    {
        int len = 614400-BUF.size();
        BUF.append(buf.mid(0, len));
        this->flushcam(BUF);

        buf.remove(0, len);
        BUF.clear();
        BUF = buf;

        qDebug()<<"获得一张图片";
    }
    else {
        BUF.append(buf);
    }

}

//环境数据
void mainwindow::readData_env()
{
    static QByteArray buf_env;

    //接收数据
    buf_env = this->socket_env->readAll();
    qDebug()<<"环境数据："<<buf_env;

    //刷新环境参数
    this->flushenv(buf_env);

}

void mainwindow::on_conButton_2_clicked()
{
    on_conButton_clicked();
}

//开关灯
void mainwindow::on_lightbitton_clicked()
{
    player->setMedia(QUrl::fromLocalFile("../SmartHome/sound/button.wav"));
    player->play();
    static int openlight = 0;
    if(0 == openlight){
        ui->lightlabel->setPixmap(QPixmap(":/picture/lighton.png"));
        ui->lightbitton->setText("OFF");
        openlight = 1;
        //开灯
        sendData('w', "wind", "M0CMD00");
    }
    else {
        ui->lightlabel->setPixmap(QPixmap(":/picture/lightoff.png"));
        ui->lightbitton->setText("ON");
        openlight = 0;
        //关灯
        sendData('w', "wind", "M0CMD01");
    }
}

//开关风扇
void mainwindow::on_windbutton_clicked()
{
    player->setMedia(QUrl::fromLocalFile("../SmartHome/sound/button.wav"));
    player->play();
    static int openwind = 0;
    if(0 == openwind){
        ui->windlabel->setPixmap(QPixmap(":/picture/windon.png"));
        ui->windbutton->setText("OFF");
        openwind = 1;
        //开风扇
        sendData('w', "wind", "M0CMD04");
    }
    else {
        ui->windlabel->setPixmap(QPixmap(":/picture/windoff.png"));
        ui->windbutton->setText("ON");
        openwind = 0;
        //关风扇
        sendData('w', "wind", "M0CMD08");
    }
}

//开关摄像头
void mainwindow::on_camarabutton_clicked()
{
    player->setMedia(QUrl::fromLocalFile("../SmartHome/sound/button.wav"));
    player->play();
    static int opencamara = 0;
    if(0 == opencamara){
        ui->camaralabel->setPixmap(QPixmap(":/picture/camaraon.png"));
        ui->camarabutton->setText("OFF");
        opencamara = 1;
        //开摄像头
        sendData('w', "wind", "V412C00");
    }
    else {
        ui->camaralabel->setPixmap(QPixmap(":/picture/camaraoff.png"));
        ui->camarabutton->setText("ON");
        ui->camaLabel->setPixmap(QPixmap(":/picture/backimg.jpg"));
        this->rcama->label->setPixmap(QPixmap(":/picture/backimg.jpg"));
        opencamara = 0;
        //关摄像头
        sendData('w', "wind", "V412C01");
    }
}

//开关蜂鸣器
void mainwindow::on_alarmbutton_clicked()
{
    player->setMedia(QUrl::fromLocalFile("../SmartHome/sound/button.wav"));
    player->play();
    static int openalarm = 0;
    if(0 == openalarm){
        ui->alarmlabel_2->setPixmap(QPixmap(":/picture/alarmon.png"));
        ui->alarmbutton->setText("OFF");
        openalarm = 1;
        //开
        sendData('w', "wind", "M0CMD02");
    }
    else {
        ui->alarmlabel_2->setPixmap(QPixmap(":/picture/alarmoff.png"));
        ui->alarmbutton->setText("ON");
        openalarm = 0;
        //关
        sendData('w', "wind", "M0CMD03");
    }
}

//放大摄像头
void mainwindow::on_resizebutton_clicked()
{
    this->rcama->show();
}

//居家娱乐
void mainwindow::on_pushButton_clicked(){
    QDesktopServices::openUrl(QUrl(QLatin1String("http://www.hao5.net/001.htm")));
}
void mainwindow::on_pushButton_2_clicked(){
    QDesktopServices::openUrl(QUrl(QLatin1String("https://www.kugou.com/yy/rank/home/1-8888.html?from=rank")));
}
void mainwindow::on_pushButton_3_clicked(){
    QDesktopServices::openUrl(QUrl(QLatin1String("http://www.4399.com/")));
}
void mainwindow::on_pushButton_4_clicked(){
    QDesktopServices::openUrl(QUrl(QLatin1String("http://life.hao123.com/menu")));
}
void mainwindow::on_pushButton_10_clicked(){
    QDesktopServices::openUrl(QUrl(QLatin1String("http://www.cnkang.com/video/article/n_8269.html")));
}
void mainwindow::on_pushButton_9_clicked(){
    QDesktopServices::openUrl(QUrl(QLatin1String("http://ds.eywedu.com/")));
}
void mainwindow::on_pushButton_12_clicked(){
    QDesktopServices::openUrl(QUrl(QLatin1String("http://ds.eywedu.com/")));
}

//系统维护
void mainwindow::on_pushButton_11_clicked()
{
    QMessageBox::about(this, "关于智能管家", "软件名：智能管家系统\n版本号:2.1.0版本\n技术支持：715142109（qq群）\n版权所有:地球村科技有限公司\npowered by:NoMi");
}

//刷新监控
void mainwindow::flushcam(QByteArray buffer)
{
    //播放图片，实现两个地方的图片播放
    ui->camaLabel->setPixmap(QPixmap::fromImage(QImage::fromData(buffer)));
    this->rcama->label->setPixmap(QPixmap::fromImage(QImage::fromData(buffer)));
}

//刷新环境参数
void mainwindow::flushenv(QString env)
{
    QString T = env.mid(1, 4);
    T.append("℃");
    QString H = env.mid(6, 4);
    T.append("%");
    QString L = env.mid(25, 4);
    L.append("cd");
    QString A = env.mid(17, 3);
    A.append("v");
    //更新检测数据

    ui->temprLabel->setText(T);
    ui->waterlabel->setText(H);
    ui->lightLabel->setText(L);
    ui->adclabel->setText(A);

}

//录制音频
void mainwindow::recordvoi()
{
    this->rCoder->beginRcd();
}

//停止录音
void mainwindow::recordend()
{
    this->rCoder->endRcd();
}

//录制音频
void mainwindow::on_pushButton_5_pressed()
{
    player->setMedia(QUrl::fromLocalFile("../SmartHome/sound/start.wav"));
    player->play();
    recordvoi();
    ui->pushButton_5->setIcon(QIcon(":/picture/recordoff.png"));
}

//录制音频
void mainwindow::on_pushButton_5_released()
{
    player->setMedia(QUrl::fromLocalFile("../SmartHome/sound/start.wav"));
    player->play();
    recordend();
    ui->pushButton_5->setIcon(QIcon(":/picture/recordon.png"));
    this->myhp->myPost(rCoder->m_buffer);
}

void mainwindow::on_tvButton_clicked()
{
    player->setMedia(QUrl::fromLocalFile("../SmartHome/sound/button.wav"));
    player->play();
    static int opentv = 0;
    if(0 == opentv){
        ui->tvLabel->setPixmap(QPixmap(":/picture/tvon.png"));
        ui->tvButton->setText("OFF");
        opentv = 1;
        //开LED
        sendData('T', "TV", "M0CMD09");
    }
    else {
        ui->tvLabel->setPixmap(QPixmap(":/picture/tvoff.png"));
        ui->tvButton->setText("ON");
        opentv = 0;
        //关LED
        sendData('w', "wind", "M0CMD0:");
    }
}

//得到识别结果，像服务器请求
void mainwindow::identify()
{
    int flag = 0;

    QString str = myhp ->RESULT;
    qDebug()<<"语音处理："<<str;

    if(str.contains("灯")){
        flag = 1;
        on_lightbitton_clicked();
    }
    if(str.contains("风扇")){
        flag = 1;
        on_windbutton_clicked();
    }
    if(str.contains("摄像头")){
        flag = 1;
        on_camarabutton_clicked();
    }
    if(str.contains("电视")){
        flag = 1;
        on_tvButton_clicked();
    }
    if(str.contains("警报")||str.contains("蜂鸣器")){
        flag = 1;
        on_alarmbutton_clicked();
    }
    if(flag == 0)
    {
        QString S = "SOUND";
        int len = str.length();
        S.append(QString::number(len).sprintf("%02d",len));
        S.append(str);
        sendData('Q', "robot", S);
    }
}
