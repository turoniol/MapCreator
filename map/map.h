#ifndef MAP_H
#define MAP_H
#include <block/block.h>
#include <QVector>
#include <QFile>
#include <QTextStream>

class Map
{
private:
  unsigned width, height; // size of map vector
  unsigned graphicWidth, graphicHeight;

  QVector<Block> map;

public:
  Map();
  bool loadMapFromFile(const QString &file_name);
  void createEmptyMap(int x, int y);
  void saveMap(const QString &file_name);
  unsigned getWidth() const;
  unsigned getHeight() const;
  QVector<Block> &getMapVector();
  Block &getBlockByCoordinate(qreal x, qreal y);
  void displayMap();
  void setBlocksNeighbours();
  unsigned getGraphicWidth() const;
  unsigned getGraphicHeight() const;
};

#endif // MAP_H
