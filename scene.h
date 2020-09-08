#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QDir>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QPainter>
#include "map.h"
#include "blockeditor.h"

class Scene : public QGraphicsScene
{
  Q_OBJECT
private:
  Map *map;
  Block *previousBlock;
  BlockEditor *blocke;
  QWidget *parent;
public:
  Scene();
  int calculatePixmapSize(const int width) const;
  bool createMap(const int width, QString& name);
  void displayMap();
  void saveMap(QString &name);

  ~Scene();

  // QGraphicsScene interface
  void setBlocke(BlockEditor *value, QWidget *parent);
protected:
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

  // QGraphicsScene interface
protected:
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SCENE_H
