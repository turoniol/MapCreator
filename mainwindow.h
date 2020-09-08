#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "scene.h"
#include "blockeditor.h"
#include <QGraphicsView>

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
private:
  QString fileName;
  int _width, _height;
  void setEditBlockGeometry(unsigned width, unsigned height, unsigned a);
  QGraphicsScene editBlockScene;
  Ui::MainWindow *ui;
  Scene scene;
  BlockEditor blockArea;

  // QWidget interface
  void loadingFailded();
protected:
  void resizeEvent(QResizeEvent *event);

private slots:
  void on_loadButton_clicked();
  void on_saveButton_clicked();
};
#endif // MAINWINDOW_H
