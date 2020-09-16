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
  _height = rec.height();

  ui->verticalLayout->setGeometry(QRect(0,0, _width, _height));
  graphicsView = new GraphicsView(this);
  graphicsView->setMouseTracking(true);
  graphicsView->setGeometry(0, 0, _width, _height);
  ui->verticalLayout->addWidget(graphicsView);

  creatingWindow = new MapCreatingWindow(this, &scene);

  // checking map`s dir
  if(!QDir("maps").exists())
    QDir().mkdir("maps");

  // adding items in combo box
  addScene(_width, _height);

  fileName = "map";
  QString defaulPath = QDir::currentPath() + "/maps/" + fileName + ".txt";
  // map creating
  if(!scene.createMap(_width, defaulPath))
    creatingWindow->show();


  scene.setBlocke(&blockArea, graphicsView);
}

void MainWindow::addScene(const int w, const int h) {
  scene.setSceneRect(0, 0, w, h);
  graphicsView->setScene(&scene);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  (void)event;
  int _width = this->width();
  int _height = this->height();
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
