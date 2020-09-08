#include "blockeditor.h"
#include <QDebug>

BlockEditor::BlockEditor()
{
  rotation = 0;
  size = 60;
  type = GRASS;
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
void BlockEditor::setPix() {
  setTransformOriginPoint(size/2, size/2);
  pixmap = getPixmap();
  pixmap = pixmap.scaled(this->size, this->size, Qt::IgnoreAspectRatio);
  if(type == GRASS)
    setRotation(0);
  setPixmap(pixmap);
}

void BlockEditor::retype()
{
  if(type == GRASS)
    setType(LEFT);
  else
    setType(GRASS);
  setPix();
}

void BlockEditor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if(event->button() == Qt::LeftButton)
    retype();
  else if(event->button() == Qt::RightButton)
      rotate();
}
