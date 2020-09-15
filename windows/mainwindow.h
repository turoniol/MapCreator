#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSettings>
#include <QGraphicsView>
#include "scene/scene.h"
#include "block/blockeditor.h"
#include "warningmessage.h"
#include "mapcreatingwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void addScene(const int w, const int h);
  void addEditBlockView(const int w, const int h);
  void setTextEditGeometry();
  void setEditBlockGeometry(unsigned width, unsigned height, unsigned a);
  bool renewComboBox();

protected:
  void resizeEvent(QResizeEvent *event);

private:
  MapCreatingWindow *creatingWindow;
  WarningMessage warningWindow;
  QString fileName;
  int _width, _height;
  QGraphicsScene editBlockScene;
  Ui::MainWindow *ui;
  Scene scene;
  BlockEditor blockArea;

private slots:
  void on_comboBox_currentIndexChanged(int index);
  void on_actionNew_fmap_triggered();
  void on_actionOpen_map_triggered();
  void on_actionSave_map_triggered();
  void on_actionQuit_triggered();
};
#endif // MAINWINDOW_H
