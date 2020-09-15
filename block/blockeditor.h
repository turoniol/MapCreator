#ifndef BLOCKEDITOR_H
#define BLOCKEDITOR_H
#include "block.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class BlockEditor : public Block
{
public:
  BlockEditor();
  void setPix();
  void retype();
  void rotate();
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BLOCKEDITOR_H
