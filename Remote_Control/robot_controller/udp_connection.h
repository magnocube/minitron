#ifndef UDP_CONNECTION_H
#define UDP_CONNECTION_H

#include <QObject>
#include <QUdpSocket>

class UDP_Connection : public QObject
{
    Q_OBJECT
public:
    explicit UDP_Connection(QString ip = "0.0.0.0");
    void send(QString data);

signals:

public slots:
    void readyRead();

private:
    QUdpSocket * socket;
    QString ipAdress;

};

#endif // UDP_CONNECTION_H
