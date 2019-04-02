#include "widget.h"
#include "game_ui.h"
#include "game_rank.h"
#include <QtGui>
#include <QMessageBox>
#include <qpushbutton.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint); // Disabled window maximize button
    setFixedSize(960,540);
    setWindowIcon(QIcon(":/favicon.ico"));

    int btn_height=71;
    int btn_width=200;

    QPushButton *btn_start=new QPushButton(this);
    btn_start->setIcon(QIcon(":/image/ui_menu_start.png"));
    btn_start->setIconSize(QSize(
                               btn_width,
                               btn_height
                               ));
    btn_start->setFlat(true);
    btn_start->setGeometry(
                600,
                170,
                btn_width,
                btn_height
                );

    connect(btn_start,SIGNAL(clicked()),this,SLOT(toGameUI()));


    QPushButton *btn_rank=new QPushButton(this);
    btn_rank->setIcon(QIcon(":/image/ui_menu_rank.png"));
    btn_rank->setIconSize(QSize(
                              btn_width,
                              btn_height
                              ));
    btn_rank->setFlat(true);
    btn_rank->setGeometry(
                700,
                270,
                btn_width,
                btn_height
                );
    connect(btn_rank,SIGNAL(clicked()),this,SLOT(toRankUI()));

    QPushButton *btn_end=new QPushButton(this);
    btn_end->setIcon(QIcon(":/image/ui_menu_end.png"));
    btn_end->setIconSize(QSize(
                             btn_width,
                             btn_height
                             ));
    btn_end->setFlat(true);
    btn_end->setGeometry(
                600,
                370,
                btn_width,
                btn_height
                );
    connect(btn_end,SIGNAL(clicked()),this,SLOT(close()));
}


/**
 * @brief Widget::paintEvent
 * @param event
 */
void Widget::paintEvent(QPaintEvent *event){
    QPainter pen(this);
    pen.drawImage(0,0,QImage(":/image/ui_main_bg.jpeg").scaled(this->width(),this->height()));
}


/**
 * @brief Widget::closeEvent
 * @param event
 */
void Widget::closeEvent(QCloseEvent *event){
    int flag = QMessageBox::question(
                nullptr,
                "提示",
                "是否要结束游戏？",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::Yes
                );
    if(flag == QMessageBox::Yes){
        event->accept();
    }else{
        event->ignore();
    }
}

/**
 * @brief Widget::toGameUI
 */
void Widget::toGameUI(){
    QGameWidget *gameUI = new QGameWidget();
    gameUI->show();
    this->hide();
}

void Widget::toRankUI(){
    QRankWidget *rankUI = new QRankWidget();
    rankUI->show();
    this->hide();
}

Widget::~Widget()
{

}
