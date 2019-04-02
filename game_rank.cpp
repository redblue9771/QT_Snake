#include <game_rank.h>
#include <QtGui>
#include <qpushbutton.h>
#include <QWidget>
#include <time.h>
#include <QMessageBox>
#include <QDebug>

extern QList<user> user_data;

QRankWidget :: QRankWidget(QWidget *parent):
    QWidget (parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint); // Disabled window maximize button
    setFixedSize(960,540);

    //    QJsonObject json;
    //    QJsonObject user_data;
    //    user_data.insert("name","1321");
    //    user_data.insert("score",1321);
    //    QJsonArray score_array;
    //    score_array.append(user_data);
    //    json.insert("rank", QJsonValue(score_array));

    //    QJsonDocument jsonDoc;
    //    jsonDoc.setObject(json);
    //    file.write(jsonDoc.toJson());

}
