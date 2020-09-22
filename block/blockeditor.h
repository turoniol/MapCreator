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
  void setPix(BlockType type);
  void setPosition(int x, int y, BlockType t);
  BlockType getTempType() const;
private:
  BlockType getOpposite(BlockType type);
  BlockType tempType;
  bool isLineRoad(BlockType t);
  bool isCornerRoad(BlockType t);
};

#endif // BLOCKEDITOR_H
