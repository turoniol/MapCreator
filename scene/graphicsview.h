#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>

class GraphicsView : public QGraphicsView
{
  Q_OBJECT
public:
  GraphicsView(QWidget *parent);
};

#endif // GRAPHICSVIEW_H
