#include <game_ui.h>
#include <QtGui>
#include <qpushbutton.h>
#include <QWidget>
#include <time.h>
#include <QMessageBox>
#include <QDebug>

#define ROW_COUNT 20
#define COLUMN_COUNT 27

extern QWidget *winMain;
extern player current_player;
extern QList<player> player_data;

QGameWidget :: QGameWidget(QWidget *parent):
    QWidget (parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint); // Disabled window maximize button
    resize(960,540);
    setMinimumSize(960,540);
    setFixedSize(960,540);
    setWindowIcon(QIcon(":/favicon.ico"));


    qsrand((unsigned)time(nullptr));

    snake.append({5,3,"right","right"});
    snake.append({4,3,"right","right"});
    snake.append({3,3,"right","right"});
    snake.append({2,3,"right","right"});
    snake.append({1,3,"right","right"});
    snake_tail=snake.size()-1;
    getFoodLocation();

    btn_up=new QPushButton(this);
    btn_up->setIcon(QIcon(":/image/ui_game_direction_up.png"));
    btn_up->setIconSize(QSize(40,72));
    btn_up->setGeometry(812,245,40,72);
    btn_up->setFlat(true);
    connect(btn_up,SIGNAL(clicked()),this,SLOT(goUp()));

    btn_down=new QPushButton(this);
    btn_down->setIcon(QIcon(":/image/ui_game_direction_down.png"));
    btn_down->setIconSize(QSize(40,72));
    btn_down->setGeometry(812,355,40,72);
    btn_down->setFlat(true);
    connect(btn_down,SIGNAL(clicked()),this,SLOT(goDown()));

    btn_left=new QPushButton(this);
    btn_left->setIcon(QIcon(":/image/ui_game_direction_left.png"));
    btn_left->setIconSize(QSize(70,40));
    btn_left->setGeometry(735,315,70,40);
    btn_left->setFlat(true);
    connect(btn_left,SIGNAL(clicked()),this,SLOT(goLeft()));

    btn_right=new QPushButton(this);
    btn_right->setIcon(QIcon(":/image/ui_game_direction_right.png"));
    btn_right->setIconSize(QSize(70,40));
    btn_right->setGeometry(852,315,70,40);
    btn_right->setFlat(true);
    connect(btn_right,SIGNAL(clicked()),this,SLOT(goRight()));

    btn_back=new QPushButton(this);
    btn_back->setIcon(QIcon(":/image/ui_game_back.png"));
    btn_back->setIconSize(QSize(100,37));
    btn_back->setGeometry(840,470,100,37);
    btn_back->setFlat(true);
    connect(btn_back,SIGNAL(clicked()),this,SLOT(toMainUI()));

    btn_start=new QPushButton(this);
    btn_start->setIconSize(QSize(100,37));
    btn_start->setGeometry(715,470,100,37);
    btn_start->setFlat(true);
    btn_start->setIcon(QIcon(":/image/ui_game_start.png"));
    game_status=false;
    connect(btn_start,SIGNAL(clicked()),this,SLOT(toggleGame()));


    game_timer=new QTimer();
    connect(game_timer, SIGNAL(timeout()), this, SLOT(moveSnake()));


    QFont ft;
    ft.setPointSizeF(18);
    ft.setFamily("汉仪综艺体简");
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    label_name=new QLabel(this);
    label_name->setFont(ft);
    label_name->setPalette(pa);
    label_name->setText("玩家："+current_player.name);
    label_name->setGeometry(713,60,220,30);


    current_player.score=0;
    label_score=new QLabel(this);
    label_score->setFont(ft);
    label_score->setPalette(pa);
    label_score->setText("法力：");
    label_score->setGeometry(713,120,70,30);

    label_score_num=new QLabel(this);
    label_score_num->setFont(ft);
    label_score_num->setPalette(pa);
    label_score_num->setGeometry(787,120,150,30);
    label_score_num->setNum(current_player.score);

    ft.setPointSizeF(14);
    label_rank=new QLabel(this);
    label_rank->setFont(ft);
    label_rank->setPalette(pa);
    label_rank->setGeometry(713,180,220,30);
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
    pen.drawImage(
                snake.at(snake_tail).x*25+20,
                snake.at(snake_tail).y*25+20,
                QImage(":/image/ui_snake_tail_"+snake.at(snake_tail).current_direction+".png").scaled(25,25)
                );

    for (int i=snake_tail-1;i>0;i--) {
        pen.drawImage(
                    snake.at(i).x*25+20,
                    snake.at(i).y*25+20,
                    QImage(":/image/ui_snake_body_"+snake.at(i).prev_direction+snake.at(i).current_direction+".png").scaled(25,25)
                    );
    }

    pen.drawImage(
                snake.at(0).x*25+20,
                snake.at(0).y*25+20,
                QImage(":/image/ui_snake_head_"+snake.at(0).current_direction+".png").scaled(25,25)
                );
}

void QGameWidget::moveSnake(){
    snake_tail=snake.size()-1;
    location location_tmp=snake.at(snake_tail);

    for(int i=snake_tail;i>0;i--){
        snake[i].x=snake.at(i-1).x;
        snake[i].y=snake.at(i-1).y;
        snake[i].prev_direction=snake.at(i).current_direction;
        snake[i].current_direction=snake.at(i-1).current_direction;
    }

    if(snake.at(0).current_direction =="up" ){
        snake[0].y--;
    }else if(snake.at(0).current_direction =="down" ){
        snake[0].y++;
    }else if(snake.at(0).current_direction =="left" ){
        snake[0].x--;
    }else if(snake.at(0).current_direction =="right" ){
        snake[0].x++;
    }

    if(food_x==snake.at(0).x && food_y==snake.at(0).y){
        getFoodLocation();
        snake.append(location_tmp);
        current_player.score+=100;
        label_score_num->setNum(current_player.score);
        label_rank->setText("还未获得任何名次~");
        for(int i=0;i<player_data.size();i++) {
            if(current_player.score>=player_data.at(i).score){
                label_rank->setText("成功超越第"+QString::number(i+1)+"名！");
                break;
            }
        }
    }

    update();

    if(snake.at(0).x<0||snake.at(0).x>COLUMN_COUNT-1||snake.at(0).y<0||snake.at(0).y>ROW_COUNT-1){
        overGame();
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
    current_player.score=0;
    label_score_num->setNum(current_player.score);
    label_rank->setText("");
    snake.clear();
    snake.append({5,3,"right","right"});
    snake.append({4,3,"right","right"});
    snake.append({3,3,"right","right"});
    snake.append({2,3,"right","right"});
    snake.append({1,3,"right","right"});
    snake_tail=snake.size()-1;
    getFoodLocation();
    update();
}


void QGameWidget::overGame(){
    boolean wirte_flag=false;
    QString message="未能闯进前三名！再接再厉！";

    if(player_data.size()==0){
        player_data.append(current_player);
        wirte_flag=true;
    }else{
        for(int i=0;i<player_data.size();i++) {
            if(current_player.score>=player_data.at(i).score){
                player_data.insert(i,current_player);
                if(player_data.size()>2)
                    player_data.removeLast();
                wirte_flag=true;
                message="恭喜你夺榜第"+QString::number(i+1)+"名！快前往排行榜查看最新排名吧！";
                break;
            }
        }
    }
    // update user data
    if(wirte_flag){
        QFile file("rank.json");
        if(!file.open(QIODevice::ReadWrite)) {
            qDebug() << "File open error";
        } else {
            qDebug() <<"File open!";
        }
        file.resize(0);

        QJsonObject json;
        QJsonArray score_array;
        for(int i=0;i<player_data.size();i++){
            QJsonObject data;
            data.insert("name",player_data.at(i).name);
            data.insert("score",player_data.at(i).score);
            score_array.append(data);
        }

        json.insert("rank", QJsonValue(score_array));

        QJsonDocument jsonDoc;
        jsonDoc.setObject(json);

        file.write(jsonDoc.toJson());
        file.close();
    }


    game_timer->stop();

    QMessageBox::information(
                nullptr,
                "游戏结束",
                message,
                QMessageBox::Yes
                );

    game_status=true;
    toggleGame();
    initGame();

}

void QGameWidget::toggleGame(){
    if(game_status){
        btn_start->setIcon(QIcon(":/image/ui_game_start.png"));
        game_timer->stop();
        game_status=false;
    }else{
        btn_start->setIcon(QIcon(":/image/ui_game_pause.png"));
        game_timer->start(400);
        game_status=true;
    }

}

void QGameWidget::goUp(){
    if(snake.at(0).current_direction!="down")
        snake[0].current_direction="up";
}

void QGameWidget::goDown(){
    if(snake.at(0).current_direction!="up")
        snake[0].current_direction="down";
}

void QGameWidget::goLeft(){
    if(snake.at(0).current_direction!="right")
        snake[0].current_direction="left";
}

void QGameWidget::goRight(){
    if(snake.at(0).current_direction!="left")
        snake[0].current_direction="right";
}

void QGameWidget::toMainUI(){
    winMain->show();
    this->close();
}
