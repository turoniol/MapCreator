#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map/map.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowIcon(QIcon(":/images/grass.png"));
  this->setWindowTitle("Map editor");
  this->setMinimumWidth(800); // minimum mainwindow size
  this->setMinimumHeight(640);
  creatingWindow = new MapCreatingWindow(this, &scene);

  // getting the size of the user`s display
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect rec = screen->geometry();
  _width = rec.width();
  _height = rec.height() - ui->graphicsView->height();

  ui->graphicsView->setMouseTracking(true);
  ui->graphicsView->setGeometry(0, 0, _width, _height);

  creatingWindow = new MapCreatingWindow(this, &scene);

  // checking map`s dir
  if(!QDir("maps").exists())
    QDir().mkdir("maps");

  // adding of scene
  addScene();

  fileName = "map";
  QString defaulPath = QDir::currentPath() + "/maps/" + fileName + ".txt";
  // map creating
  if(!scene.createMap(_width, _height, defaulPath))
    creatingWindow->show();


  scene.setBlocke(&blockArea, ui->graphicsView);
}

void MainWindow::addScene() {
  ui->graphicsView->setScene(&scene);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  (void)event;
  int w = this->width();
  int h = this->height() - ui->menubar->height();

  ui->graphicsView->setGeometry(0, 0, w, h);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionNew_fmap_triggered()
{
  creatingWindow->show();
}

void MainWindow::on_actionOpen_map_triggered()
{
//  QString name = " ";

//  if(!name.isEmpty()) {
//      QString path = QDir::currentPath() + "/maps/" + name + ".txt";
//      if(!scene.createMap(_width, path)) {
//          warningWindow.showMessage("File with this name doesn`t exist!");
//        }
//    }
}

void MainWindow::on_actionSave_map_triggered()
{
//  QString name = "" ;

//  if(!name.isEmpty()) {
//      QString path = QDir::currentPath() + "/maps/" + name + ".txt";
//      scene.saveMap(path);
//    }
//  else {
//      warningWindow.showMessage("Invalid filename!");
//    }
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
