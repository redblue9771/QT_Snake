#include <game_rank.h>
#include <QtGui>
#include <qpushbutton.h>
#include <QWidget>
#include <time.h>
#include <QMessageBox>
#include <QDebug>

extern QList<player> player_data;
extern QWidget *winMain;

QRankWidget :: QRankWidget(QWidget *parent):
    QWidget (parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint); // Disabled window maximize button
    setFixedSize(960,540);

    QFont ft;
    ft.setPointSizeF(24);
    ft.setFamily("汉仪综艺体简");
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);


    list_top_name=new QLabel(this);
    list_top_score=new QLabel(this);

    list_top_name->setFont(ft);
    list_top_name->setPalette(pa);
    list_top_name->setGeometry(200,210,212,28);
    list_top_name->setAlignment(Qt::AlignCenter);
    list_top_name->setText(player_data.at(0).name);

    list_top_score->setFont(ft);
    list_top_score->setPalette(pa);
    list_top_score->setGeometry(628,210,84,24);
    list_top_score->setAlignment(Qt::AlignCenter);
    list_top_score->setNum(player_data.at(0).score);


    list_second_name=new QLabel(this);
    list_second_score=new QLabel(this);
    ft.setPointSizeF(22);

    list_second_name->setFont(ft);
    list_second_name->setPalette(pa);
    list_second_name->setGeometry(210,292,196,26);
    list_second_name->setAlignment(Qt::AlignCenter);
    list_second_name->setText(player_data.at(1).name);


    list_second_score->setFont(ft);
    list_second_score->setPalette(pa);
    list_second_score->setGeometry(630,292,77,22);
    list_second_score->setAlignment(Qt::AlignCenter);
    list_second_score->setNum(player_data.at(1).score);

    list_third_name=new QLabel(this);
    list_third_score=new QLabel(this);
    ft.setPointSizeF(20);

    list_third_name->setFont(ft);
    list_third_name->setPalette(pa);
    list_third_name->setGeometry(218,372,176,24);
    list_third_name->setAlignment(Qt::AlignCenter);
    list_third_name->setText(player_data.at(2).name);

    list_third_score->setFont(ft);
    list_third_score->setPalette(pa);
    list_third_score->setGeometry(634,372,70,20);
    list_third_score->setAlignment(Qt::AlignCenter);
    list_third_score->setNum(player_data.at(2).score);

    btn_back=new QPushButton(this);
    btn_back->setIcon(QIcon(":/image/ui_game_back.png"));
    btn_back->setIconSize(QSize(100,37));
    btn_back->setGeometry(830,480,100,37);
    btn_back->setFlat(true);
    connect(btn_back,SIGNAL(clicked()),this,SLOT(toMainUI()));
}

void QRankWidget::toMainUI(){
    winMain->show();
    this->close();
}

void QRankWidget::paintEvent(QPaintEvent *event){

    QPainter pen(this);

    pen.drawImage(0,0,QImage(":/image/ui_rank_bg.jpg").scaled(this->width(),this->height()));
}
