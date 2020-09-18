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
  savingWindow = new MapSavingWindow(this, fileName);

  // getting the size of the user`s display
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect rec = screen->geometry();
  _width = rec.width();
  _height = rec.height() - ui->graphicsView->height();

  // zooming of graphicsView
  viewZoom = new GraphicsViewZoom(ui->graphicsView);
  viewZoom->set_modifiers(Qt::ControlModifier);

  ui->graphicsView->setMouseTracking(true);
  ui->graphicsView->setGeometry(0, 0, _width, _height);

  creatingWindow = new MapCreatingWindow(this, &scene);

  // checking map`s dir
  if(!QDir("maps").exists())
    QDir().mkdir("maps");

  directory.setPath(QDir::currentPath() + "/maps/");
  // adding of scene
  addScene();

  listOfFileNames = directory.entryList();

  fileName = "map";

  QString defaulPath = directory.path() + '/' + fileName + ".txt";
  // map creating
  if(!scene.createMap(_width, _height, defaulPath))
    creatingWindow->show();

  scene.setBlocke(&blockArea, ui->graphicsView);

  connect(savingWindow, &QDialog::accepted, this, &MainWindow::saveMap);
  connect(this, &MainWindow::readyToClearWarningWindow, this, &MainWindow::clearWarningWindowPointer);
}

void MainWindow::addScene() {
  ui->graphicsView->setScene(&scene);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  int w = this->width();
  int h = this->height() - ui->menubar->height();

  ui->graphicsView->setGeometry(0, 0, w, h);
  Q_UNUSED(event);
}

void MainWindow::clearWarningWindowPointer()
{
  delete warningWindow;
  warningWindow = nullptr;
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
  savingWindow->show();
}

void MainWindow::saveMap()
{
  warningWindow = new WarningMessage;
  QString name = savingWindow->getText();
  QString path = directory.path() + "/" + name + ".txt";
  if (listOfFileNames.contains(QString(name + ".txt")) &&
      (this->fileName != name))
    {
      warningWindow->showMessage("Map with this name exist. Rewrite it?");
      connect(warningWindow, &QMessageBox::rejected, [this](){
          this->savingWindow->show();
          emit this->readyToClearWarningWindow();
        });
      connect(warningWindow, &QMessageBox::accepted, [this, path]() {
          this->scene.saveMap(path);
          emit this->readyToClearWarningWindow();
        });
    }
  else
    scene.saveMap(path);
}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::quit();
}
