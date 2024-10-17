#include "gamecell.h"

GameCell::GameCell(std::string id,QObject *parent)
    : QObject{parent},type{CellType::blank},id(id)
{
}

GameCell::ifClicked()
{
    cout<<"dupa"<<endl;
}
