#include "block.h"
void Block::fillTypeMap() {
  typeMap[GRASS] = 0;
  typeMap[LEFT] = 0;
  typeMap[RIGHT] = 180;
  typeMap[DOWN] = 270;
  typeMap[UP] = 90;
  typeMap[DOWN_LEFT] = 0;
  typeMap[DOWN_RIGHT] = 270;
  typeMap[UP_LEFT] = 90;
  typeMap[UP_RIGHT] = 180;
}

bool Block::isChanged()
{
  return change;
}

void Block::setChange(bool value)
{
  change = value;
}

unsigned Block::getPixmapSize()
{
  return 60;
}

Block::BlockType Block::getType() const
{
  return type;
}

QPixmap Block::getPixmap()
{
  QPixmap pix;
  fillTypeMap();
  int SIZE = getPixmapSize();
  this->setTransformOriginPoint(SIZE/2, SIZE/2);

  if(type == GRASS)
    pix.load(":/images/grass.png");
  else if(type == LEFT || type == RIGHT || type == UP || type == DOWN)
    pix.load(":/images/road.png");
  else if(type == UP_LEFT || type == UP_RIGHT || type == DOWN_LEFT || type == DOWN_RIGHT)
    pix.load(":/images/road_central.png");
  else
    pix.load(":/images/grass.png");

  return pix;
}

void Block::setHighlight(BlockType type, int rot)
{
  QPixmap pix;
  BlockType ftype = getFutureType(type);

  if(ftype == GRASS)
    pix.load(":/images/grassEdit.png");
  else if(ftype == LEFT || ftype == RIGHT || ftype == UP || ftype == DOWN)
    pix.load(":/images/roadEdit.png");
  else if(ftype == UP_LEFT || ftype == UP_RIGHT || ftype == DOWN_LEFT || ftype == DOWN_RIGHT)
    pix.load(":/images/road_centralEdit.png");
  setRotation(rot);

  setPixmap(pix);
}

int Block::getRotation() const
{
  return typeMap[type];
}

Block::BlockType Block::getFutureType(Block::BlockType val)
{
  int t = (int)type;
  bool vertical = ((val ==  DOWN) || (val == UP));
  bool horizontal = ((val ==  RIGHT) || (val == LEFT));

  if((type == LEFT && vertical) || (type == RIGHT && vertical) ||
     (type == DOWN && horizontal) || (type == UP && horizontal))
    t += (int)val;
  else
    t = (int)val;
  return (BlockType)t;
}

void Block::addNeighbour(Block &obj)
{
  neighbours.push_back(&obj);
}

void Block::setType(const unsigned &value)
{
  type = getFutureType((BlockType)value);
  change = true;
}

void Block::setPix()
{
  pixmap = getPixmap();
  rotation = typeMap[type];
  setRotation(rotation);

  setPixmap(pixmap);
}


Block::Block()
{
  change = false;
  type = GRASS;
}

Block::Block(const Block &obj) : QGraphicsPixmapItem()
{
  this->type = obj.type;
  this->setPos(obj.pos());
}

Block Block::operator=(const Block &obj)
{
  Block block;
  block.type = obj.type;
  block.setPos(obj.pos());
  return block;
}
