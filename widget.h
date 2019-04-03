#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QInputDialog>
#include "custom_type.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);
private:
    QInputDialog *input_name;
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void toGameUI();
    void toRankUI();

};

#endif // WIDGET_H
