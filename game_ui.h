#ifndef GAME_UI_H
#define GAME_UI_H

#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include "custom_type.h"



class QGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QGameWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
protected:
    //   void closeEvent(QCloseEvent *event);

private:
    int food_x;
    int food_y;
    int snake_tail;
    int snake_direction;
    int game_score;
    boolean game_status;

    QList<location> snake;
    QPushButton *btn_start;
    QPushButton *btn_back;
    QPushButton *btn_up;
    QPushButton *btn_down;
    QPushButton *btn_left;
    QPushButton *btn_right;

    void overGame();
    void getFoodLocation();

    QTimer *game_timer;
    QLabel *label_name;
    QLabel *label_score;
    QLabel *label_score_num;

    QInputDialog *input_name;

    user current_user;
private slots:
    void toMainUI();
    void moveSnake();
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    void initGame();
    void toggleGame();

    //    QLabel *label_level;
};

#endif // GAME_UI_H
