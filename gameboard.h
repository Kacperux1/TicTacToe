#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QSharedPointer>
#include "gamecell.h"
#include <QPushButton>

const int N=3;
class GameBoard : public QWidget
{
    Q_OBJECT
    QSharedPointer<GameCell> board[N][N];
    QPushButton* buttons[N][N];
public:
    explicit GameBoard(QWidget *parent = nullptr);

signals:
};

#endif // GAMEBOARD_H
