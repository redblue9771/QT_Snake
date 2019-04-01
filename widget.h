#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void toGameUI();
};

#endif // WIDGET_H
