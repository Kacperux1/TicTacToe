#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),turn(Turn::circle)
{
    QGridLayout *layout = new QGridLayout;
    centralWidget = new QWidget(this);
    layout = new QGridLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Inicjalizacja przycisków
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            buttons[i][j] = new QPushButton(" ", this);
            board[i][j]= QSharedPointer<GameCell>::create();
            board[i][j]->setButton(buttons[i][j]);
            board[i][j]->changeImage("blank.png");   // Ustawienie pustego tekstu
            layout->addWidget(buttons[i][j], i, j);

            // Połączenie kliknięcia przycisku z metodą obsługi
            connect(buttons[i][j], &QPushButton::clicked, [this, i, j]() {
                handleButtonClick(i, j);
            });
        }
    }

    setLayout(layout);
}



MainWindow::~MainWindow()
{
    delete ui;
    for(int i=0;i<N;i++)
        delete buttons[i];
    delete buttons;
}

void MainWindow::handleButtonClick(int i, int j) {

    if(board[i][j]->getType() != CellType::blank)
        return;
    if(turn==Turn::circle){
        board[i][j]->changeImage("kolko.png");
        turn=Turn::cross;
        board[i][j]->setType(CellType::circle);
    }
    else{
        turn=Turn::circle;
         board[i][j]->changeImage("cross.png");
        board[i][j]->setType(CellType::cross);
    }
    checkEnd();
}

void MainWindow::checkEnd()
{
    bool gameOver = false;
    int horizontalCircles = 0;
    int horizontalCrosses = 0;
    int verticalCircles = 0;
    int verticalCrosses = 0;
    CellType winner;
    for(int i=0;i<N;i++)
    {
        horizontalCircles = 0;
        horizontalCrosses = 0;
        verticalCircles = 0;
        verticalCrosses = 0;
        for(int j=0;j<N;j++){

            if(board[i][j]->getType() == CellType::blank)
                break;
            else{
                if(board[i][j]->getType() == CellType::cross)
                    horizontalCrosses++;
                else
                    horizontalCircles++;

                if(board[j][i]->getType() == CellType::circle)
                    verticalCrosses++;
                else
                    verticalCircles++;
            }
        }
        if(horizontalCrosses == N || verticalCrosses == N){
            gameOver = true;
            winner = CellType::cross;
            break;
        }
        else if(horizontalCircles == N || verticalCircles == N){
            gameOver = true;
            winner = CellType::circle;
            break;
        }
    }


    /*if((!gameOver && board[N/2+1][N/2+1]->getType() != CellType::blank) && ((board[N/2+1][N/2+1]->getType() == board[0][0]->getType() && board[N/2+1][N/2+1]->getType() == board[N-1][N-1]->getType()) || (board[N/2+1][N/2+1]->getType() ==board[0][N-1]->getType() && board[N/2+1][N/2+1]->getType() == board[N-1][0]->getType()))){
        gameOver = true;
        winner = board[N/2+1][N/2+1]->getType();
    }
    */
    int diagonalCircles = 0;
    int diagonalCrosses = 0;
    int diagonalCirclesReversed = 0;
    int diagonalCrossesReversed = 0;
    for(int i=1;i<N;i++)
    {
        if(board[i][i]->getType() == CellType::blank)
            break;
        else
            if(board[i][i]->getType() == board [i-1][i-1]->getType())
                if(board[i][i]->getType() == CellType::cross)
                    diagonalCrosses++;
                else
                    diagonalCircles++;

    }
    if(diagonalCrosses == N-1 || diagonalCircles ==N-1){
        gameOver=true;
        if(diagonalCircles>diagonalCrosses)
            winner = CellType::circle;
        else
            winner = CellType::cross;
    }
    if(!gameOver){
    for(int i = 0;i < N;i++){
            if(board[i][N-1-i]->getType() == CellType::blank)
                break;
            else
                    if(board[i][N-1-i]->getType() == CellType::cross)
                        diagonalCrossesReversed++;
                    else
                        diagonalCirclesReversed++;
        }
    }

    if(diagonalCrossesReversed == N || diagonalCirclesReversed ==N){
        gameOver=true;
        if(diagonalCirclesReversed>diagonalCrossesReversed)
            winner = CellType::circle;
        else
            winner = CellType::cross;
    }
    if(gameOver){
        QMessageBox endingMessage;
        if(winner == CellType::circle){
        endingMessage.setText("Game Over, the circle has won!");
        }
        else
        {
            endingMessage.setText("Game Over, the cross has won!");
        }
        endingMessage.exec();
        return;
    }
    int blankFields=0;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            if(board[i][j]->getType() == CellType::blank)
                blankFields++;
        }
    if(blankFields == 0 && gameOver==false){
        QMessageBox endingMessage;
        endingMessage.setText("It's a draw!");
        endingMessage.exec();
        return;
    }
    return;

}

