#ifndef TESTWEBSOCKET_H
#define TESTWEBSOCKET_H

#include "websocketclient.h"
#include "testconfig.h"

class TestWebSocket : public QThread
{
    Q_OBJECT
public:
    explicit TestWebSocket(QObject *parent = nullptr);
    void init(sTestConfigItem *item) { mItem = item;}
    void saveTestData();
protected:
    bool saveJson(const QString &name, QJsonObject &json);
    void toJson(sTestConfigItem *item, QJsonObject &obj);
    void devUut(sSerialNumItem &item, QJsonObject &json);
    void devInfo(sSerialNumItem &item, QJsonObject &json);
    void itemNum(sTestProgress &item, QJsonObject &json);
    void objData(const sTestDataItem &item, QJsonObject &obj);
    void listData( QList<sTestDataItem> &items, QJsonObject &json);

private:
    WebSocketClient *mWebSocket;
    sTestConfigItem *mItem;
};

#endif // TESTWEBSOCKET_H
