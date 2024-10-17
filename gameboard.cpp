#include "gameboard.h"

GameBoard::GameBoard(QWidget *parent)
    : QWidget{parent}
{
    int id =1;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            board[i][j]=QSharedPointer<GameCell>::create("field_0"+std::to_string(id++));
            buttons[i][j]= new QPushButton("pushButton_0"+std::to_string(id), this);
            layout->addWidget(buttons[i][j], i, j);

            connect(buttons[i][j], &QPushButton::clicked, board[i][j].data(), &GameCell::ifCLicked());
        }
}
