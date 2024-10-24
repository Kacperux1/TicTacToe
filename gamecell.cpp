#include "gamecell.h"
#include "typedefs.h"
#include <QFile>

GameCell::GameCell(std::string id,QObject *parent)
    : QObject{parent},type{CellType::blank},id(id)
{
}

void GameCell::changeImage(const std::string &filepath)
{
    QFile file(QString::fromStdString(filepath));
    if (!file.exists()) {
        std::cerr << "File does not exist: " << filepath << std::endl;
        return;
    }

    QPixmap pixmap(QString::fromStdString(filepath));
    if (!pixmap.isNull()) {
        button->setIcon(pixmap);
        button->setIconSize(pixmap.size());
        std::cout << "Image loaded successfully: " << filepath << std::endl;
    } else {
        std::cerr << "Failed to load image: " << filepath << std::endl;
    }
}

GameCell::~GameCell()
{
    delete button;
}

void GameCell::setButton(QPushButton* button)
{
    GameCell::button = button;
}

void GameCell::setType(CellType type)
{
    GameCell::type = type;
}

CellType GameCell::getType()
{
    return GameCell::type;
}

