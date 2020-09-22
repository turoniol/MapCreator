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
  void createEmptyMap(const int x, const int y);
  bool existMap();
  ~Scene();
//protected:
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void keyPressEvent(QKeyEvent *event) override;
private:
  // variables
  Map *map;
  BlockEditor *editBlock;
  int _width, _height;
  // functions
  void changeType(Block *block);
  bool inScene(qreal x, qreal y);
signals:
  void saved();
};

#endif // SCENE_H
