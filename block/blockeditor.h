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
  Block *getPreviousBlock() const;
  void setPreviousBlock(Block *value);
  void setPix(BlockType type);
  void setPosition(int x, int y, BlockType t);
private:
  Block *previousBlock;
};

#endif // BLOCKEDITOR_H
