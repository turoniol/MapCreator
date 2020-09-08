#include "scene.h"
#include <QDebug>
#include <QPicture>

bool Scene::createMap(const int width, QString &name)
{
  if(map != nullptr)
    delete map;
  previousBlock = nullptr;
  map = new Map;

  if(map->loadMapFromFile(name, width)) {
      displayMap();
      map->setBlocksNeighbours();
      unsigned y;
      if(this->height() <= map->getGraphicHeight())
        y = map->getGraphicHeight();
      else
        y = this->height();
      setSceneRect(0, 0, this->width(), y);
      calculatePixmapSize(0.8*width);
      return true;
    }
  else
    return false;
}

void Scene::displayMap()
{
  map->displayMap();
  for(auto &obj : map->getMapVector()) {
      this->addItem(&obj);
    }
}

void Scene::saveMap(QString& name)
{
  map->saveMap(name);
}

int Scene::calculatePixmapSize(const int width) const// calculates size of the pixmap of a block
{
  return width/map->getWidth();
}

Scene::~Scene() {
  delete map;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  parent->setMouseTracking(false);
  qreal x = event->scenePos().x(),
      y = event->scenePos().y();

  if(x < map->getGraphicWidth() && y < map->getGraphicHeight() &&
     x >= 0 && y >= 0) {
      Block *block = &map->getBlockByCoordinate(x, y);

      if(event->button() == Qt::LeftButton) {
          Block::BlockType blockType = blocke->getType();
          block->setType(blockType);
          block->setPix();
        }
      else if(event->button() == Qt::RightButton) {
          // TODO
          // automatic block
        }
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  (void)event;
  parent->setMouseTracking(true);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  int x = event->scenePos().x();
  int y = event->scenePos().y();

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
