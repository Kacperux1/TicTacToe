#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include "gamecell.h"
#include <QGridLayout>
#include "typedefs.h"
#include "QMessageBox"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    QSharedPointer<GameCell> board[N][N];
    QPushButton* buttons[N][N];
    QGridLayout layout;
    Turn turn;

    QWidget *centralWidget;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleButtonClick(int i, int j);
    void checkEnd();
};
#endif // MAINWINDOW_H
