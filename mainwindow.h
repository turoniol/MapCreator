#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSettings>
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
  void setEditBlockGeometry(unsigned width, unsigned height, unsigned a);
  bool renewComboBox();
  void showWarning(QString message);
private:
  QString fileName;
  int _width, _height;
  QGraphicsScene editBlockScene;
  Ui::MainWindow *ui;
  Scene scene;
  BlockEditor blockArea;

protected:
  void resizeEvent(QResizeEvent *event);

private slots:
  void on_loadButton_clicked();
  void on_saveButton_clicked();
  void on_saveEdit_textChanged();
  void on_comboBox_currentIndexChanged(int index);
};
#endif // MAINWINDOW_H
