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

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  int x = event->scenePos().x(),
      y = event->scenePos().y();
  x -= x % Block::getPixmapSize();
  y -= y % Block::getPixmapSize();

  if (existMap() && inScene(x, y) && QPointF(x, y) != editBlock->pos()) {
      editBlock->setPosition(x, y, &map->getBlockByCoordinate(x, y));
      if (event->buttons()  == Qt::LeftButton) {
          changeType(&map->getBlockByCoordinate(x, y));
      }
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (editBlock != nullptr) {
      Block *block = &map->getBlockByCoordinate(editBlock->x(), editBlock->y());

      if (event->button() == Qt::LeftButton) {
          changeType(block);
        }
      else if (event->button() == Qt::RightButton) {
          editBlock->rotate();
          editBlock->setPix(block);
        }
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
  if (editBlock != nullptr) {
      if (event->key() == Qt::Key_Space) {
          editBlock->retype();
          editBlock->setPix(&map->getBlockByCoordinate(editBlock->x(), editBlock->y()));
        }
    }
}

void Scene::changeType(Block *block)
{
  block->setType(editBlock->getTempType());
  block->setPix();
  block->repixNeighbors();
  editBlock->setPix(block);
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
