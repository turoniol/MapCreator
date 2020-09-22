#ifndef BLOCKEDITOR_H
#define BLOCKEDITOR_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "block.h"
#include "map/map.h"

class BlockEditor : public Block
{
public:
  BlockEditor();
  void retype();
  void rotate();
  void setPreviousBlock(Block *value);
  void setPix(Block * const block);
  void setPosition(int x, int y, Block * const block);
  BlockType getTempType() const;
private:
  BlockType getOpposite(BlockType type);
  BlockType tempType;
};

#endif // BLOCKEDITOR_H
