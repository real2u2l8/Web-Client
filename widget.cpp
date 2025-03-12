#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->csArg = Qt::Unchecked;
    //signal <-> slots
    //socket_.connected(); //Signal Func

    QObject::connect(&socket_, &QAbstractSocket::connected, this, &Widget::doConnected); //2nd arg is MemberFunc pointer <<QT Style Syntax
    QObject::connect(&socket_, &QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    QObject::connect(&socket_, &QIODevice::readyRead, this, &Widget::doReadyRead);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::doConnected()
{
    ui->pteMessage->insertPlainText("Connected ");
}
void Widget::doDisconnected()
{
    ui->pteMessage->insertPlainText("Disconnected");
}
void Widget::doReadyRead()
{
    ui->pteMessage->insertPlainText(socket_.readAll());
}

void Widget::on_pbConnect_clicked()
{
    if (this->csArg == Qt::Unchecked) {
        socket_.connectToHost(ui->leHost->text(), ui->lePort->text().toUShort()); // TCP
    } else if (this->csArg == Qt::Checked) {
        socket_.connectToHostEncrypted(ui->leHost->text(), ui->lePort->text().toUShort()); // SSL/TLS
    }
}

void Widget::on_pbDisconnect_clicked()
{
    socket_.disconnectFromHost();
}

void Widget::on_pbClear_clicked()
{
    ui->pteMessage->clear();
}


void Widget::on_pbSend_clicked()
{
    socket_.write(ui->pteSend->toPlainText().toUtf8());
}


void Widget::on_cbTLS_checkStateChanged(const Qt::CheckState &state) //is TLS?
{
    this->csArg = state;
}
