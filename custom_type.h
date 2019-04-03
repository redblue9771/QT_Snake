#ifndef CUSTOM_TYPE_H
#define CUSTOM_TYPE_H
#include <QtGui>

typedef struct location{
    int x;
    int y;
    QString current_direction;
    QString prev_direction;
}location;

typedef struct player
{
    QString name;
    int score;
}player;

#endif // CUSTOM_TYPE_H
