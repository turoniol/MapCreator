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

void BlockEditor::retype()
{
  if(type == GRASS)
    setType(LEFT);
  else
    setType(GRASS);
  setRotation(typeMap[type]);
}
