#include "udp_connection.h"

UDP_Connection::UDP_Connection(QString ip)
{
    ipAdress = ip;
    // create a QUDP socket
    socket = new QUdpSocket(this);

    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)
    socket->bind(QHostAddress::Any, 4210);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void UDP_Connection::send()
{
    socket->writeDatagram(reinterpret_cast<char*>(&sharedVariables.inputs), sizeof(sharedVariables.inputs) ,QHostAddress(ipAdress), 4210);
}

void UDP_Connection::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;

    memcpy((void*)&sharedVariables.outputs, buffer, sizeof(sharedVariables.outputs));
    qDebug() << "battery: " << sharedVariables.outputs.loopUpdateRate;
    emit udpUpdate();  // will send a signal to the main

}
