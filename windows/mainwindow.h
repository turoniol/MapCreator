#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSettings>
#include <QScrollBar>

#include "scene/scene.h"
#include "block/blockeditor.h"
#include "warningmessage.h"
#include "mapcreatingwindow.h"
#include "scene/graphicsviewzoom.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void addScene();

protected:
  virtual void resizeEvent(QResizeEvent *event) override;

private:
  GraphicsViewZoom *viewZoom;
  MapCreatingWindow *creatingWindow;
  WarningMessage warningWindow;
  QString fileName;
  int _width, _height;
  QGraphicsScene editBlockScene;
  Ui::MainWindow *ui;
  Scene scene;
  BlockEditor blockArea;

private slots:
  void on_actionNew_fmap_triggered();
  void on_actionOpen_map_triggered();
  void on_actionSave_map_triggered();
  void on_actionQuit_triggered();

  // QWidget interface

};
#endif // MAINWINDOW_H
