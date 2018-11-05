#ifndef TESTWEBSOCKET_H
#define TESTWEBSOCKET_H

#include "websocketclient.h"

class TestWebSocket : public QThread
{
    Q_OBJECT
public:
    explicit TestWebSocket(QObject *parent = nullptr);

protected:
    bool saveJson(const QString &name, QJsonObject &json);

signals:

public slots:

private:
    WebSocketClient *mWebSocket;
};

#endif // TESTWEBSOCKET_H
