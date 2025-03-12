#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QSslSocket>
#include <QIODevice>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //QTcpSocket socket_;
    QSslSocket socket_;
    Qt::CheckState csArg;

public slots: //user defined slots
    void setupConnections();
    void doConnected();
    void doDisconnected();
    void doReadyRead();
private slots:
    void on_pbClear_clicked();

    void on_pbDisconnect_clicked();

    void on_pbConnect_clicked();

    void on_pbSend_clicked();

    void on_cbTLS_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
