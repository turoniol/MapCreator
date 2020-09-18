#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QDir>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>

#include "map/map.h"
#include "block/blockeditor.h"

class Scene : public QGraphicsScene
{
  Q_OBJECT
public:
  Scene();
  bool createMap(const int w, const int h, QString& name);
  void displayMap();
  void saveMap(const QString &name);
  // QGraphicsScene interface
  void setBlocke(BlockEditor *value, QWidget *parent);
  void createEmptyMap(const int x, const int y);
  bool existMap();
  ~Scene();
protected:
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void keyPressEvent(QKeyEvent *event) override;
private:
  Map *map;
  Block *previousBlock;
  BlockEditor *blocke;
  QWidget *parent;
  int width, height;
};

#endif // SCENE_H
