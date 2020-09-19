#include "scene.h"
#include <QDebug>
#include <QPicture>

bool Scene::createMap(const int w, const int h, QString &name)
{
  _width = w;
  _height = h;
  if (map != nullptr)
      delete map;
  if (editBlock != nullptr)
    delete editBlock;
  map = new Map;
  editBlock = new BlockEditor();

  if (map->loadMapFromFile(name)) {
      displayMap();
      map->setBlocksNeighbours();
      unsigned y = map->getGraphicHeight(),
          x = map->getGraphicWidth();

      setSceneRect(0, 0, x, y);
      return true;
    }
  else {
      delete map;
      delete editBlock;
      editBlock = nullptr;
      map = nullptr;
      return false;
    }
}

void Scene::createEmptyMap(const int x, const int y)
{
    if(map != nullptr)
      delete map;
    if (editBlock != nullptr)
      delete editBlock;
    map = new Map;
    editBlock = new BlockEditor();

    map->createEmptyMap(x, y);
    displayMap();
    map->setBlocksNeighbours();
    unsigned h = map->getGraphicHeight(),
        w = map->getGraphicWidth();

    setSceneRect(0, 0, w, h);
}

bool Scene::existMap()
{
  if (map == nullptr)
    return false;
  else
    return true;
}

void Scene::displayMap()
{
  map->displayMap();
  for(auto &obj : map->getMapVector()) {
      this->addItem(&obj);
    }
  this->addItem(editBlock);
}

void Scene::saveMap(const QString& name)
{
  if (existMap()) {
      map->saveMap(name);
      emit saved();
    }
}

//void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//  parent->setMouseTracking(false);
//  qreal x = event->scenePos().x(),
//      y = event->scenePos().y();

//  if (existMap() && x < map->getGraphicWidth() && y < map->getGraphicHeight() &&
//     x >= 0 && y >= 0) {
//      Block *block = &map->getBlockByCoordinate(x, y);

//      if (event->button() == Qt::LeftButton) {
//          Block::BlockType blockType = blocke->getType();
//          block->setType(blockType);
//          block->setPix();
//        }
//      else if (event->button() == Qt::RightButton) {
//          blocke->rotate();
//        }
//    }
//}

//void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//  (void)event;
//  parent->setMouseTracking(true);
//}

//void Scene::keyPressEvent(QKeyEvent *event)
//{
//  if (event->key() == Qt::Key_Space)
//    blocke->retype();
//}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
      QGraphicsSceneMouseEvent *mouse_event = (QGraphicsSceneMouseEvent *)event;
      int x = mouse_event->scenePos().x(),
          y = mouse_event->scenePos().y();
      x -= x % Block::getPixmapSize();
      y -= y % Block::getPixmapSize();

      if (existMap() && inScene(x, y))
        editBlock->setPosition(x, y, map->getBlockByCoordinate(x, y).getType());
}

bool Scene::inScene(qreal x, qreal y)
{
  return (x >= 0 && y >= 0) && ( x < map->getGraphicWidth() && y < map->getGraphicHeight());
}

Scene::Scene() {
  map = nullptr;
}


Scene::~Scene() {
  if (map != nullptr)
    delete map;
}
