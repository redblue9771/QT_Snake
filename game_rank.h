#ifndef GAME_RANK_H
#define GAME_RANK_H

#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "custom_type.h"

class QRankWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QRankWidget(QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *event);
protected:


private:
    QLabel *list_top_name;
    QLabel *list_top_score;
    QLabel *list_second_name;
    QLabel *list_second_score;
    QLabel *list_third_name;
    QLabel *list_third_score;
    QPushButton *btn_back;

private slots:
    void toMainUI();

};
#endif // GAMERANKING_H
