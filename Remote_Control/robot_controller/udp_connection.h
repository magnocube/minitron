#ifndef UDP_CONNECTION_H
#define UDP_CONNECTION_H

#include <QObject>
#include <QUdpSocket>

class UDP_Connection : public QObject
{
    Q_OBJECT
public:
    explicit UDP_Connection(QObject *parent = nullptr);
    void send(QString data);

signals:

public slots:
    void readyRead();

private:
    QUdpSocket * socket;
};

#endif // UDP_CONNECTION_H
