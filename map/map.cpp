#include "map.h"
#include <QDebug>
bool Map::loadMapFromFile(const QString &file_name)
{
  QFile file(file_name);
  if(file.open(QIODevice::Text | QIODevice::ReadOnly)) {
      QTextStream out(&file);
      out >> width >> height; // reading of size

      graphicWidth = PIXMAP_SIZE*width;
      graphicHeight = PIXMAP_SIZE*height;
      unsigned int type;

      for(unsigned y = 0; y < height; ++y) { // adding parameters of block
          for(unsigned x = 0; x < width; ++x) {
              Block obj;

              out >> type;
              obj.setType(type);
              obj.setSize(PIXMAP_SIZE);

              obj.setPos(x*PIXMAP_SIZE, y*PIXMAP_SIZE);
              map.push_back(obj);
          }
        }
      file.close();
      return true;
  }
  else
    return false;

}

void Map::createEmptyMap(int x, int y)
{
  width = x;
  height = y;
  graphicWidth = PIXMAP_SIZE*width;
  graphicHeight = PIXMAP_SIZE*height;

  for(unsigned y = 0; y < height; ++y) { // adding position of blocks
      for(unsigned x = 0; x < width; ++x) {
          Block obj;
          obj.setSize(PIXMAP_SIZE);
          obj.setPos(x*PIXMAP_SIZE, y*PIXMAP_SIZE);
          map.push_back(obj);
        }
    }
}

void Map::saveMap(QString &file_name)
{
  QFile f(file_name);
  if(f.open(QIODevice::WriteOnly)) {
      QTextStream in(&f);
      in << width << " " << height << " ";
      for(auto obj : map)
        in << obj.getType() << " ";
    }
}

unsigned Map::getWidth() const
{
    return width;
}

unsigned Map::getHeight() const
{
  return height;
}

QVector<Block> &Map::getMapVector()
{
  return map;
}

Block &Map::getBlockByCoordinate(qreal x, qreal y)
{
  unsigned _x = (unsigned)x,
      _y = (unsigned)y,
      modX = _x % PIXMAP_SIZE,
      modY = _y % PIXMAP_SIZE;
  _x -= modX;
  _y -= modY;
  _x /= PIXMAP_SIZE;
  _y /= PIXMAP_SIZE;

  return map[_x + _y*width];
}

void Map::setBlocksNeighbours()
{
  Block* ptr = nullptr;
  int size = (int)PIXMAP_SIZE;
  for(auto &obj : map) {
      int x = obj.x();
      int y = obj.y();

      if(y - size >= 0)
          obj.addNeighbour(getBlockByCoordinate(x, y - PIXMAP_SIZE)); // top
      else
        obj.addNeighbour(*ptr);

      if(x - size >= 0)
        obj.addNeighbour(getBlockByCoordinate(x - PIXMAP_SIZE, y)); // left
      else
        obj.addNeighbour(*ptr);

      if(y + size < (int)graphicHeight)
        obj.addNeighbour(getBlockByCoordinate(x, y + PIXMAP_SIZE)); // down
      else
        obj.addNeighbour(*ptr);

      if(x + size < (int)graphicWidth)
        obj.addNeighbour(getBlockByCoordinate(x + PIXMAP_SIZE, y)); // right
      else
        obj.addNeighbour(*ptr);
  }
}

void Map::displayMap()
{
  for(Block &obj : map) {
      obj.setPix();
  }
}

unsigned Map::getGraphicWidth() const
{
  return graphicWidth;
}

unsigned Map::getGraphicHeight() const
{
  return graphicHeight;
}

Map::Map()
{
  width = 0;
  height = 0;
}

