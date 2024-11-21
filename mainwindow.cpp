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
    int circlesInRow = 0;
    int crossesInRow = 0;
    int circlesInColumn = 0;
    int crossesInColumn = 0;
    CellType winner;
    for(int i=0;i<N;i++)
    {
        circlesInRow = 0;
        crossesInRow = 0;
        circlesInColumn = 0;
        crossesInColumn = 0;
        for(int j=0;j<N;j++) {
            if(board[i][j]->getType() == CellType::blank)
                break;
            else{
                if(board[i][j]->getType() == CellType::cross)
                    crossesInRow++;
                else
                    circlesInRow++;
            }
        }

            for(int j = 0;j < N;j++) {
                if(board[j][i]->getType() == CellType::blank)
                    break;
                if(board[j][i]->getType() == CellType::circle)
                    circlesInColumn++;
                else
                    crossesInColumn++;
            }

        if(crossesInRow == N || crossesInColumn == N){
            gameOver = true;
            winner = CellType::cross;
            break;
        }
        else if(circlesInRow == N || circlesInColumn == N){
            gameOver = true;
            winner = CellType::circle;
            break;
        }
    }

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
        QMessageBox winMessage;
        if(winner == CellType::circle){
       winMessage.setText("Game Over, the circle has won!");
        }
        else
        {
            winMessage.setText("Game Over, the cross has won!");
        }
        winMessage.exec();
        endMessage();
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
        QMessageBox winMessage;
        winMessage.setText("It's a draw!");
        winMessage.exec();
        endMessage();
        return;
    }
    return;
}

void MainWindow::boardReInit()
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j< N; j++){
            board[i][j]->changeImage("blank.png");
            board[i][j]->setType(CellType::blank);
        }
    }
}

void MainWindow::endMessage()
{
    QMessageBox endMessage;
    endMessage.setText("Do you want to play again or exit the game?");

    QPushButton *quitButton = endMessage.addButton("Quit", QMessageBox::RejectRole);
    QPushButton *playAgainButton = endMessage.addButton("Play Again", QMessageBox::AcceptRole);

    endMessage.exec();

    if (endMessage.clickedButton() == quitButton) {
        QApplication::quit();
    } else if (endMessage.clickedButton() == playAgainButton) {
        boardReInit();
    }
}



