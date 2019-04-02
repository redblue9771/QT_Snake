#include "widget.h"
#include <QtGui>
#include <QApplication>

QList<user> user_data;
QWidget *winMain;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    winMain = &w;
    w.show();

    QFile file("rank.json");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open error";
    } else {
        qDebug() <<"File open!";
    }
    QByteArray allData = file.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument jsonBody = QJsonDocument::fromJson(allData, &jsonError);
    if (jsonError.error == QJsonParseError::NoError){
        QJsonObject rootObj = jsonBody.object();
        if (jsonBody.isObject()){
            if (rootObj.contains("rank")){
                QJsonValue valueArray = rootObj.value("rank");
                if (valueArray.isArray()){
                    QJsonArray jsonArray = valueArray.toArray();
                    for (int i = 0; i < jsonArray.count();i++){
                        QJsonValue childValue = jsonArray[i];
                        if (childValue.isObject()){
                            QString user_name="";
                            int user_score = 0;
                            QJsonObject  childObject = childValue.toObject();
                            if (childObject.contains("name")){
                                QJsonValue valueJson = childObject.value("name");
                                if (valueJson.isString()){
                                    user_name = valueJson.toString();
                                }
                            }
                            if (childObject.contains("score")){
                                QJsonValue valueJson = childObject.value("score");
                                if (valueJson.isDouble()){
                                    user_score=valueJson.toInt();
                                }
                            }
                            user_data.append({user_name,user_score});
                        }
                    }
                }
            }
        }
    }
    return a.exec();
}
