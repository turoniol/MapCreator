#include "map.h"
#include <QDebug>
bool Map::loadMapFromFile(const QString &file_name)
{
  QFile file(file_name);
  if(file.open(QIODevice::Text | QIODevice::ReadOnly)) {
      QTextStream out(&file);
      out >> width >> height; // reading of size

      int pixmap_size = Block::getPixmapSize();
      graphicWidth = pixmap_size*width;
      graphicHeight = pixmap_size*height;
      unsigned int type;

      for(unsigned y = 0; y < height; ++y) { // adding parameters of block
          for(unsigned x = 0; x < width; ++x) {
              Block obj;
              out >> type;
              obj.setType(type);
              obj.setPos(x*pixmap_size, y*pixmap_size);
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
  int pixmap_size = Block::getPixmapSize();

  width = x;
  height = y;
  graphicWidth = pixmap_size*width;
  graphicHeight = pixmap_size*height;

  for(unsigned y = 0; y < height; ++y) { // adding position of blocks
      for(unsigned x = 0; x < width; ++x) {
          Block obj;
          obj.setPos(x*pixmap_size, y*pixmap_size);
          map.push_back(obj);
        }
    }
}

void Map::saveMap(const QString &file_name)
{
  QFile f(file_name);
  if(f.open(QIODevice::WriteOnly)) {
      QTextStream in(&f);
      in << width << " " << height << " ";
      for(auto obj : map)
        in << (int)obj.getType() << " ";
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
  int pixmap_size = Block::getPixmapSize();
  unsigned _x = (unsigned)x,
      _y = (unsigned)y,
      modX = _x % pixmap_size,
      modY = _y % pixmap_size;
  _x -= modX;
  _y -= modY;
  _x /= pixmap_size;
  _y /= pixmap_size;

  return map[_x + _y*width];
}


void Map::setBlocksNeighbours()
{
  Block* ptr = nullptr;
  int pixmap_size = Block::getPixmapSize();
  for(auto &obj : map) {
      int x = obj.x();
      int y = obj.y();

      if(y - pixmap_size >= 0)
          obj.addNeighbour(getBlockByCoordinate(x, y - pixmap_size)); // top
      else
        obj.addNeighbour(*ptr);

      if(x - pixmap_size >= 0)
        obj.addNeighbour(getBlockByCoordinate(x - pixmap_size, y)); // left
      else
        obj.addNeighbour(*ptr);

      if(y + pixmap_size < (int)graphicHeight)
        obj.addNeighbour(getBlockByCoordinate(x, y + pixmap_size)); // down
      else
        obj.addNeighbour(*ptr);

      if(x + pixmap_size < (int)graphicWidth)
        obj.addNeighbour(getBlockByCoordinate(x + pixmap_size, y)); // right
      else
        obj.addNeighbour(*ptr);
  }
}

void Map::displayMap()
{
  setBlocksNeighbours();
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
  graphicWidth = 0;
  graphicHeight = 0;
  width = 0;
  height = 0;
}

