#ifndef BLOCK_H
#define BLOCK_H
#include <QGraphicsItem>

class Block : public QGraphicsPixmapItem
{
public:
  enum class BlockType { GRASS, LEFT, DOWN, RIGHT = 4, UP = 8,
                   DOWN_LEFT = DOWN + LEFT, DOWN_RIGHT = DOWN + RIGHT,
                   UP_RIGHT = UP + RIGHT, UP_LEFT = UP + LEFT };
  Block();
  Block(const Block &obj);
  Block operator=(const Block &obj);
  void setPix();
  void setType(const unsigned value);
  void setType(const BlockType val);
  BlockType getType() const;
  QPixmap getPixmap();
  void addNeighbour(Block &);
  void repixNeighbors();
  static unsigned getPixmapSize();
  static int getRotationByType(BlockType type);
  static BlockType getTypeByRotation(int rot);
  bool isEndCornerRoad(const BlockType t);
  bool isLineRoad(const BlockType t);
  bool isCornerRoad(const BlockType t);
protected:
  QVector<Block*> neighbours;
  BlockType _type;
  QPixmap pixmap;
};
#endif // BLOCK_H
