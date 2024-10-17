#ifndef GAMECELL_H
#define GAMECELL_H

#include <QObject>
#include "typedefs.h"
#include <string>

class GameCell : public QObject
{
    Q_OBJECT
    std::string id;
    CellType type;
public:
    explicit GameCell(std::string id="0",QObject *parent = nullptr);

    void ifClicked();

signals:
};

#endif // GAMECELL_H
