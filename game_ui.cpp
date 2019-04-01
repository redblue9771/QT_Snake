#include <game_ui.h>
#include <QtGui>
#include <qpushbutton.h>
#include <QWidget>
#include <time.h>
#include <QMessageBox>
#include <QDebug>

#define ROW_COUNT 20
#define COLUMN_COUNT 27
#define SNAKE_UP 1
#define SNAKE_DOWN -1
#define SNAKE_LEFT 2
#define SNAKE_RIGHT -2

extern QWidget *winMain;

QGameWidget :: QGameWidget(QWidget *parent):
    QWidget (parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint); // Disabled window maximize button
    {
        QSettings *settings = new QSettings (":/setting.ini",QSettings::IniFormat);
        settings->setIniCodec(QTextCodec::codecForName ("UTF-8"));
        settings->beginGroup("UI");
        int init_width=settings->value("init_width").toInt();
        int init_height=init_width/16*9;
        setFixedSize(
                    init_width,
                    init_height
                    );
        setWindowTitle(settings->value("main_title").toString());
        delete settings;    // Delete porint}
    }
    setWindowIcon(QIcon(":/favicon.ico"));

    qsrand((unsigned)time(nullptr));
    initGame();

    btn_up=new QPushButton(this);
    btn_up->setIcon(QIcon(":/image/ui_game_back.png"));
    btn_up->setIconSize(QSize(100,37));
    btn_up->setGeometry(780,300,100,37);
    btn_up->setFlat(true);
    connect(btn_up,SIGNAL(clicked()),this,SLOT(goUp()));

    btn_down=new QPushButton(this);
    btn_down->setIcon(QIcon(":/image/ui_game_back.png"));
    btn_down->setIconSize(QSize(100,37));
    btn_down->setGeometry(780,400,100,37);
    btn_down->setFlat(true);
    connect(btn_down,SIGNAL(clicked()),this,SLOT(goDown()));

    btn_left=new QPushButton(this);
    btn_left->setIcon(QIcon(":/image/ui_game_back.png"));
    btn_left->setIconSize(QSize(100,37));
    btn_left->setGeometry(715,350,100,37);
    btn_left->setFlat(true);
    connect(btn_left,SIGNAL(clicked()),this,SLOT(goLeft()));

    btn_right=new QPushButton(this);
    btn_right->setIcon(QIcon(":/image/ui_game_back.png"));
    btn_right->setIconSize(QSize(100,37));
    btn_right->setGeometry(840,350,100,37);
    btn_right->setFlat(true);
    connect(btn_right,SIGNAL(clicked()),this,SLOT(goRight()));

    btn_back=new QPushButton(this);
    btn_back->setIcon(QIcon(":/image/ui_game_back.png"));
    btn_back->setIconSize(QSize(100,37));
    btn_back->setGeometry(840,470,100,37);
    btn_back->setFlat(true);
    connect(btn_back,SIGNAL(clicked()),this,SLOT(toMainUI()));

    btn_recovery=new QPushButton(this);
    btn_recovery->setIcon(QIcon(":/image/ui_game_recovery.png"));
    btn_recovery->setIconSize(QSize(100,37));
    btn_recovery->setGeometry(715,470,100,37);
    btn_recovery->setFlat(true);
    connect(btn_recovery,SIGNAL(clicked()),this,SLOT(initGame()));


    timer_food=new QTimer();
    connect(timer_food, SIGNAL(timeout()), this, SLOT(moveSnake()));
    timer_food->start(500);

    //    label_score=new QLabel();
    //    label_level=new QLabel();
}

void QGameWidget::paintEvent(QPaintEvent *event){

    QPainter pen(this);

    pen.drawImage(0,0,QImage(":/image/ui_game_bg.jpg").scaled(this->width(),this->height()));

    pen.setPen(QColor(100,100,100));
    for(int i=0;i<COLUMN_COUNT;i++){
        for(int j=0;j<ROW_COUNT;j++){
            pen.drawRect(i*25+20,j*25+20,25,25);
        }
    }
    pen.setPen(QColor(255,255,255));
    pen.drawRect(20,20,675,500);

    pen.drawImage(food_x*25+20,food_y*25+20,QImage(":/image/ui_game_food.png").scaled(25,25));

    pen.setBrush(QColor(255,255,255));
    for (int i=0;i<snake.size();i++) {
        pen.drawRect(snake[i].x*25+20,snake[i].y*25+20,25,25);
    }

}

void QGameWidget::moveSnake(){
    int snake_tail=snake.size()-1;
    int snake_tail_x=snake.at(snake_tail).x;
    int snake_tail_y=snake.at(snake_tail).y;

    for(int i=snake_tail;i>0;i--){
        snake[i].x=snake.at(i-1).x;
        snake[i].y=snake.at(i-1).y;
    }

    switch(snake_direction){
    case 1:
        snake[0].y--;
        break;
    case -1:
        snake[0].y++;
        break;
    case 2:
        snake[0].x--;
        break;
    case -2:
        snake[0].x++;
        break;
    }

    if(food_x==snake.at(0).x && food_y==snake.at(0).y){
        getFoodLocation();
        snake.append({snake_tail_x,snake_tail_y});
    }

    update();

    if(snake.at(0).x<1||snake.at(0).x>COLUMN_COUNT-2||snake.at(0).y<1||snake.at(0).y>ROW_COUNT-2){
        timer_food->stop();
    }
}

void QGameWidget::getFoodLocation(){
    food_x=qrand()%(COLUMN_COUNT-1)+1;
    food_y=qrand()%(ROW_COUNT-1)+1;

    for (int i=0;i<snake.size();i++) {
        if(food_x==snake[i].x && food_y==snake[i].y){
            food_x=qrand()%(COLUMN_COUNT-1)+1;
            food_y=qrand()%(ROW_COUNT-1)+1;
            i=0;
        }
    }
}

/**
 * @brief QGameWidget::initGame
 */
void QGameWidget::initGame(){
    snake.clear();
    snake_direction = -2;
    snake.append({5,3});
    snake.append({4,3});
    snake.append({3,3});
    getFoodLocation();
}

void QGameWidget::goUp(){
    if(-snake_direction!=1)
        snake_direction=1;
}

void QGameWidget::goDown(){
    if(-snake_direction!=-1)
        snake_direction=-1;
}

void QGameWidget::goLeft(){
    if(-snake_direction!=2)
        snake_direction=2;
}

void QGameWidget::goRight(){
    if(-snake_direction!=-2)
        snake_direction=-2;
}

void QGameWidget::toMainUI(){
    winMain->show();
    this->close();
}
