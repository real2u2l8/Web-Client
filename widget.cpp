#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->csArg = Qt::Unchecked;

    setupConnections();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setupConnections()
{
    //2nd arg is MemberFunc pointer <<QT Style Syntax
    //signal <-> slots
    //socket_.connected(); //Signal Func
    QObject::connect(&socket_, &QAbstractSocket::connected, this, &Widget::doConnected);
    QObject::connect(&socket_, &QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    QObject::connect(&socket_, &QIODevice::readyRead, this, &Widget::doReadyRead);
}

void Widget::doConnected()
{
    ui->pteMessage->insertPlainText("Connected\n\n");
}
void Widget::doDisconnected()
{
    ui->pteMessage->insertPlainText("Disconnected\n\n");
}
void Widget::doReadyRead()
{
    ui->pteMessage->insertPlainText(socket_.readAll());
}

void Widget::on_pbConnect_clicked()
{
    auto host = ui->leHost->text();
    auto port = ui->lePort->text().toUShort();
    if (this->csArg == Qt::Unchecked) {
        socket_.connectToHost(host, port); // TCP
    } else if (this->csArg == Qt::Checked) {
        socket_.connectToHostEncrypted(host, port); // SSL/TLS
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
