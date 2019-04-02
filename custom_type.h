#ifndef CUSTOM_TYPE_H
#define CUSTOM_TYPE_H
#include <QtGui>

typedef struct location{
    int x;
    int y;
    QString current_direction;
    QString prev_direction;
}location;

typedef struct user
{
    QString name;
    int score;
}user;

#endif // CUSTOM_TYPE_H
