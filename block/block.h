#ifndef BLOCK_H
#define BLOCK_H
#include <QGraphicsItem>

class Block : public QGraphicsPixmapItem
{
public:
  enum BlockType { GRASS, LEFT, DOWN, RIGHT = 4, UP = 8,
                   DOWN_LEFT = DOWN + LEFT, DOWN_RIGHT = DOWN + RIGHT,
                   UP_RIGHT = UP + RIGHT, UP_LEFT = UP + LEFT};
  Block();
  Block(const Block &obj);
  Block operator=(const Block &obj);
  void setPix();
  void setType(const unsigned &value);
  BlockType getType() const;
  QPixmap getPixmap();
  void setHighlight(BlockType type, int rot);
  int getRotation() const;
  BlockType getFutureType(BlockType val);
  void addNeighbour(Block &);
  void fillTypeMap();
  bool isChanged();
  void setChange(bool value);
  static unsigned getPixmapSize();
protected:
  QMap<BlockType, int> typeMap;
  QVector<Block*> neighbours;
  BlockType type;
  bool change;
  int rotation;
  QPixmap pixmap;
};
#endif // BLOCK_H
