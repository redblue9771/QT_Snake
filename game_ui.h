#ifndef GAME_UI_H
#define GAME_UI_H

#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

typedef struct location{
    int x;
    int y;
}location;

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
    int snake_head;
    int snake_tail;
    int snake_direction;
    int snake_node;

    QList<location> snake;
    QPushButton *btn_recovery;
    QPushButton *btn_back;
    QPushButton *btn_up;
    QPushButton *btn_down;
    QPushButton *btn_left;
    QPushButton *btn_right;

    QTimer *timer_food;

    void getFoodLocation();

private slots:
    void toMainUI();
    void moveSnake();
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    void initGame();
    //    QLabel *label_score;
    //    QLabel *label_level;
};

#endif // GAME_UI_H
