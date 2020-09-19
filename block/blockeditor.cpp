#include "blockeditor.h"
#include <QDebug>

BlockEditor::BlockEditor()
{
  rotation = 0;
  type = GRASS;
  previousBlock = nullptr;
}
void BlockEditor::rotate()
{
  if(type >= LEFT && type <= UP) {
      if(type == UP)
        type = LEFT;
      else {
          int t = (int)type;
          t <<= 1;
          type = (BlockType)t;
        }
    }
  rotation = typeMap[type];
  setRotation(rotation);
}

Block *BlockEditor::getPreviousBlock() const
{
  return previousBlock;
}

void BlockEditor::setPreviousBlock(Block *value)
{
  previousBlock = value;
}

void BlockEditor::setPix(BlockType t)
{
  QPixmap pix;
  BlockType ftype = (BlockType)((int)type + (int)t);

  if(ftype == GRASS)
    pix.load(":/images/grassEdit.png");
  else if(ftype == LEFT || ftype == RIGHT || ftype == UP || ftype == DOWN)
    pix.load(":/images/roadEdit.png");
  else if(ftype == UP_LEFT || ftype == UP_RIGHT || ftype == DOWN_LEFT || ftype == DOWN_RIGHT)
    pix.load(":/images/road_centralEdit.png");
  setRotation(ftype);

  setPixmap(pix);
}

void BlockEditor::setPosition(int x, int y, Block::BlockType t)
{
  if (QPointF(x, y) != pos()) {
      qDebug() << x << y << t;
      setPix(t);
      setPos(x, y);
  }
}

void BlockEditor::retype()
{
  if(type == GRASS)
    setType(LEFT);
  else
    setType(GRASS);
  setRotation(typeMap[type]);
}
