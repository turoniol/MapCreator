#include "block.h"
#include <QDebug>
int Block::getRotationByType(BlockType type) {
  if (type == BlockType::GRASS) return -360;
  else if (type == BlockType::LEFT) return 0;
  else if (type == BlockType::RIGHT) return 180;
  else if (type == BlockType::DOWN) return 270;
  else if (type == BlockType::UP) return 90;
  else if (type == BlockType::DOWN_LEFT) return 360 + 0;
  else if (type == BlockType::DOWN_RIGHT) return  360 + 270;
  else if (type == BlockType::UP_LEFT) return 360 + 90;
  else if (type == BlockType::UP_RIGHT) return 360 + 180;
  else return -360;
}

Block::BlockType Block::getTypeByRotation(int rot)
{
  if (rot == -360) return BlockType::GRASS;
  else if (rot == 0) return BlockType::LEFT;
  else if (rot == 180) return BlockType::RIGHT;
  else if (rot == 270) return BlockType::DOWN;
  else if (rot == 90) return BlockType::UP;
  else if (rot == 360 + 0) return BlockType::DOWN_LEFT;
  else if (rot == 360 + 270) return  BlockType::DOWN_RIGHT;
  else if (rot == 360 + 90) return BlockType::UP_LEFT;
  else if (rot == 360 + 180) return BlockType::UP_RIGHT;
  else return BlockType::GRASS;
}

unsigned Block::getPixmapSize()
{
  return 60;
}

Block::BlockType Block::getType() const
{
  return _type;
}

QPixmap Block::getPixmap()
{
  QPixmap pix;
  int SIZE = getPixmapSize();
  this->setTransformOriginPoint(SIZE/2, SIZE/2);
  if(_type == BlockType::GRASS)
    pix.load(":/images/grass.png");
  else if(_type == BlockType::LEFT || _type == BlockType::RIGHT ||
          _type == BlockType::UP || _type == BlockType::DOWN)
    pix.load(":/images/road.png");
  else if(_type == BlockType::UP_LEFT || _type == BlockType::UP_RIGHT ||
          _type == BlockType::DOWN_LEFT || _type == BlockType::DOWN_RIGHT)
    pix.load(":/images/road_central.png");
  else
    pix.load(":/images/grass.png");

  return pix;
}

void Block::addNeighbour(Block &obj)
{
  neighbours.push_back(&obj);
}

void Block::setType(const unsigned value)
{
  _type = (BlockType)value;
}

void Block::setType(const Block::BlockType val)
{
  _type = val;
}

void Block::setPix()
{
  pixmap = getPixmap();
  setRotation(getRotationByType(_type));
  setPixmap(pixmap);
}

Block::Block()
{
  _type = BlockType::GRASS;
}

Block::Block(const Block &obj) : QGraphicsPixmapItem()
{
  this->_type = obj._type;
  this->setPos(obj.pos());
}

Block Block::operator=(const Block &obj)
{
  Block block;
  block._type = obj._type;
  block.setPos(obj.pos());
  return block;
}
