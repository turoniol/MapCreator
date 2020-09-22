#include "blockeditor.h"
#include <QDebug>

BlockEditor::BlockEditor()
{
  setTransformOriginPoint(getPixmapSize()/2, getPixmapSize()/2);
  _type = BlockType::GRASS;
  setRotation(getRotationByType(_type));
}
void BlockEditor::rotate()
{
  if(_type >= BlockType::LEFT && _type <= BlockType::UP) {
      if(_type == BlockType::UP)
        _type = BlockType::LEFT;
      else {
          int t = (int)_type;
          t <<= 1;
          _type = (BlockType)t;
        }
    }
  setRotation(getRotationByType(_type));
}

void BlockEditor::setPix(BlockType itype)
{
  QPixmap pix;
  tempType = _type;

  BlockType t = _type != BlockType::GRASS ? (BlockType)((int)itype + (int)_type) : _type;
  if (isCornerRoad(t))
    tempType = t;

  if (!isLineRoad(tempType) && !isCornerRoad(tempType) && tempType != BlockType::GRASS)
    tempType = BlockType::GRASS;

  if(tempType == BlockType::GRASS)
    pix.load(":/images/grassEdit.png");
  else if(isLineRoad(tempType))
    pix.load(":/images/roadEdit.png");
  else if(isCornerRoad(tempType))
    pix.load(":/images/road_centralEdit.png");
  setPixmap(pix);
  setRotation(getRotationByType(tempType));
}

void BlockEditor::setPosition(int x, int y, Block::BlockType t)
{
  if (QPointF(x, y) != pos()) {
      setPix(t);
      setPos(x, y);
    }
}

Block::BlockType BlockEditor::getTempType() const
{
  return tempType;
}

Block::BlockType BlockEditor::getOpposite(Block::BlockType type)
{
  BlockEditor b;
  b.setType(type);
  b.rotate();
  b.rotate();
  auto t = b.getType();
  return (isLineRoad(t)) ? t : BlockType::GRASS;
}

bool BlockEditor::isLineRoad(Block::BlockType type)
{
  return (type == BlockType::LEFT || type == BlockType::RIGHT ||
          type == BlockType::DOWN || type == BlockType::UP);
}

bool BlockEditor::isCornerRoad(Block::BlockType type)
{
  return type == BlockType::UP_LEFT || type == BlockType::UP_RIGHT ||
      type == BlockType::DOWN_LEFT || type == BlockType::DOWN_RIGHT;
}

void BlockEditor::retype()
{
  if(_type == BlockType::GRASS)
    setType(BlockType::LEFT);
  else
    setType(BlockType::GRASS);
  setRotation(getRotationByType(_type));
}
