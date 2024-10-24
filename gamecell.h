#ifndef GAMECELL_H
#define GAMECELL_H

#include <QObject>
#include "typedefs.h"
#include <string>
#include <QPushButton>

class GameCell : public QObject
{
    Q_OBJECT
    std::string id;
    CellType type;
    QPushButton* button;
public:
    explicit GameCell(std::string id="0",QObject *parent = nullptr);
    void changeImage(const std::string& filepath);
    ~GameCell();
    void setButton(QPushButton* button);
    void setType(CellType type);
    CellType getType();
signals:
};


#endif // GAMECELL_H
