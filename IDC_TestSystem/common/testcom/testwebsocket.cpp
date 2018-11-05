#include "testwebsocket.h"

TestWebSocket::TestWebSocket(QObject *parent) : QThread(parent)
{
    mWebSocket = new WebSocketClient();
    mWebSocket->open();
}


bool TestWebSocket::saveJson(const QString &name, QJsonObject &json)
{
    QJsonDocument jsonDoc(json);
    QByteArray ba = jsonDoc.toJson();
    QFile file("F:/" + name+".json");
    bool ret = file.open(QIODevice::WriteOnly);
    if(ret) {
        file.write(ba);
        file.close();
    } else {
        qDebug() << "write json file failed";
    }

    return ret;
}
