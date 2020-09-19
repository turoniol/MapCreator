#include "scene.h"
#include <QDebug>
#include <QPicture>

bool Scene::createMap(const int w, const int h, QString &name)
{
  width = w;
  height = h;
  if(map != nullptr)
      delete map;
  previousBlock = nullptr;
  map = new Map;

  if(map->loadMapFromFile(name)) {
      displayMap();
      map->setBlocksNeighbours();
      unsigned y = map->getGraphicHeight(),
          x = map->getGraphicWidth();

      setSceneRect(0, 0, x, y);
      return true;
    }
  else {
      delete map;
      map = nullptr;
      return false;
    }
}

void Scene::createEmptyMap(const int x, const int y)
{
    if(map != nullptr)
      delete map;
    previousBlock = nullptr;
    map = new Map;

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
}

void Scene::saveMap(const QString& name)
{
  if(existMap())
    map->saveMap(name);
}


Scene::~Scene() {
  delete map;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  parent->setMouseTracking(false);
  qreal x = event->scenePos().x(),
      y = event->scenePos().y();

  if (existMap() && x < map->getGraphicWidth() && y < map->getGraphicHeight() &&
     x >= 0 && y >= 0) {
      Block *block = &map->getBlockByCoordinate(x, y);

      if (event->button() == Qt::LeftButton) {
          Block::BlockType blockType = blocke->getType();
          block->setType(blockType);
          block->setPix();
        }
      else if (event->button() == Qt::RightButton) {
          blocke->rotate();
        }
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  (void)event;
  parent->setMouseTracking(true);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Space)
    blocke->retype();
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  int x = 0, y = 0;
  if (existMap()) {
      x = event->scenePos().x();
      y = event->scenePos().y();

      if(x < (int)map->getGraphicWidth() && y < (int)map->getGraphicHeight() &&
         x >= 0 && y >= 0) {
          Block *block = &map->getBlockByCoordinate(x, y);

          block->setHighlight(blocke->getType(), blocke->getRotation());

          if(!parent->hasMouseTracking() && !block->isChanged()) {
              block->setType(blocke->getType());
              block->setPix();
            }

          if(previousBlock == nullptr) {
              previousBlock = block;
            }
          else if(block->pos() != previousBlock->pos()) {
              previousBlock->setPix();
              previousBlock->setChange(false);
              previousBlock = block;
            }

        }
    }
}

void Scene::setBlocke(BlockEditor *value, QWidget *parent)
{
  this->parent = parent;
  blocke = value;
}


Scene::Scene() {
  map = nullptr;
  previousBlock = nullptr;
  blocke = nullptr;
}
