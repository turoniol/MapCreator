#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QDir>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QPainter>
#include "map/map.h"
#include "block/blockeditor.h"

class Scene : public QGraphicsScene
{
  Q_OBJECT
private:
  Map *map;
  Block *previousBlock;
  BlockEditor *blocke;
  QWidget *parent;
  int width;
public:
  Scene();
  int calculatePixmapSize(const int width) const;
  bool createMap(const int width, QString& name);
  void displayMap();
  void saveMap(QString &name);
  // QGraphicsScene interface
  void setBlocke(BlockEditor *value, QWidget *parent);
  void createEmptyMap(const int x, const int y);
  ~Scene();
protected:
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

  // QGraphicsScene interface
protected:
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SCENE_H
