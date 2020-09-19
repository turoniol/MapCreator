#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSettings>
#include <QScrollBar>

#include "scene/scene.h"
#include "warningmessage.h"
#include "mapcreatingwindow.h"
#include "mapsavingwindow.h"
#include "maploadingwindow.h"
#include "scene/graphicsviewzoom.h"
#include "common/mydir.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
protected:
  virtual void resizeEvent(QResizeEvent *event) override;

private:
  MyDir _dir;
  GraphicsViewZoom *viewZoom;
  MapCreatingWindow *creatingWindow;
  MapSavingWindow *savingWindow;
  MapLoadingWindow *loadingWindow;
  WarningMessage *warningWindow;
  QString fileName;
  int _width, _height;
  QGraphicsScene editBlockScene;
  Ui::MainWindow *ui;
  Scene scene;
signals:
  void readyToClearWarningWindow();
private slots:
  void clearWarningWindowPointer();
  void on_actionNew_fmap_triggered();
  void on_actionOpen_map_triggered();
  void on_actionSave_map_triggered();
  void on_actionQuit_triggered();
  void saveMap();

};
#endif // MAINWINDOW_H
