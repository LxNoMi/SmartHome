#include "connet.h"
#include "ui_connet.h"

connet::connet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connet)
{
    ui->setupUi(this);
    ui->ipEdit->setText("192.168.2.11");
    ui->portEdit->setText("56780");
    ui->portEdit1->setText("56789");
    this->setWindowTitle("连接服务器");
}

connet::~connet()
{
    delete ui;
}

void connet::on_commitButton_clicked()
{
    if(ui->ipEdit->text()==""){
        QMessageBox::information(this, "错误提示", "ip地址或端口号不能为空...");
        return;
    }
    this->myIp = ui->ipEdit->text();
    this->myPort = ui->portEdit->text().toInt();
    this->myPort1 = ui->portEdit1->text().toInt();
    this->hide();
    emit commited();
}
