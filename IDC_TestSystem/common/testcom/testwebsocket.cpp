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



void TestWebSocket::saveTestData()
{
    sTestConfigItem  *item = mItem;
    if(item->serialNum.isSave && (item->progress.finishNum>5))
    {
        QJsonObject json;
        toJson(item, json);
        saveJson("saveTest", json);

        mWebSocket->sendMessage(json);
    }

    item->logItems.clear();
}

void TestWebSocket::toJson(sTestConfigItem  *item,QJsonObject &obj)
{
    obj.insert("company", "CLEVER");
    obj.insert("version", 2);

    devUut(item->serialNum, obj);
    devInfo(item->serialNum, obj);
    itemNum(item->progress, obj);
    listData(item->logItems, obj);
}


void TestWebSocket::devUut(sSerialNumItem &item, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("devtype", item.name);
    obj.insert("sn", item.sn);

    obj.insert("barcode", item.barCode);
    obj.insert("purpose", item.purpose);
    obj.insert("batch", item.batch);

    obj.insert("op", item.op);
    obj.insert("cn", item.cn);
    obj.insert("testdate", item.date.toString("yyyy-dd-MM"));

    json.insert("dev_uut", QJsonValue(obj));
}

void TestWebSocket::devInfo(sSerialNumItem &item, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("df",  item.spec);
    obj.insert("line", item.line);
    obj.insert("loop", item.loop);
    obj.insert("output", item.output);

    json.insert("dev_info", QJsonValue(obj));
}

void TestWebSocket::itemNum(sTestProgress &item, QJsonObject &json)
{
    QJsonObject obj;
    obj.insert("all",  item.allNum);
    obj.insert("finish", item.finishNum);
    obj.insert("pass", item.okNum);
    obj.insert("err", item.errNum);

    json.insert("item_num", QJsonValue(obj));
}

void TestWebSocket::objData(const sTestDataItem &item, QJsonObject &obj)
{
    obj.insert("uid", item.id);
    obj.insert("testitem", item.item);
    obj.insert("describe", item.subItem);
    obj.insert("expect", item.expect);
    obj.insert("measured", item.measured);
    obj.insert("status", item.status);
}


void TestWebSocket::listData(QList<sTestDataItem> &items, QJsonObject &json)
{
    QJsonArray jsonArray;
    QString modeStr = "line";

    int num = items.size();
    for(int i=0; i<num; ++i)
    {
        QJsonObject subObj;
        objData(items.at(i), subObj);
        jsonArray.append(subObj);
    }

    if(num > 0) json.insert(QString("item_list"), QJsonValue(jsonArray));
}
