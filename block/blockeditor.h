#ifndef BLOCKEDITOR_H
#define BLOCKEDITOR_H
#include "block.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class BlockEditor : public Block
{
public:
  BlockEditor();
  void retype();
  void rotate();
};

#endif // BLOCKEDITOR_H
