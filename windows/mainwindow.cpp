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

  // getting the size of the user`s display
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect rec = screen->geometry();
  _width = rec.width();
  _height = rec.height() - ui->graphicsView->height();

  // zooming of graphicsView
  viewZoom = new GraphicsViewZoom(ui->graphicsView);
  viewZoom->set_modifiers(Qt::ControlModifier);

  ui->graphicsView->setGeometry(0, 0, _width, _height);

  // checking map`s dir
  if(!QDir("maps").exists())
    QDir().mkdir("maps");

  // declaration of load-save-open pointers
  creatingWindow = new MapCreatingWindow(this);
  savingWindow = new MapSavingWindow(this);
  loadingWindow = new MapLoadingWindow(this);

  // map loading
  if(_dir.isEmpty())
    creatingWindow->show();
  else
    loadingWindow->show();

  ui->graphicsView->setScene(&scene);

  connect(this, &MainWindow::readyToClearWarningWindow, this, &MainWindow::clearWarningWindowPointer);
  // on save map connect
  connect(savingWindow, &QDialog::accepted, this, &MainWindow::saveMap);
  // on create map connect
  connect(creatingWindow, &QDialog::accepted, [this]() {
      scene.createEmptyMap(creatingWindow->getX(), creatingWindow->getY());
      fileName.clear();
      savingWindow->setText(fileName);
  });
  // on open map connect
  connect(loadingWindow, &MapLoadingWindow::choosen, [this]() {
      fileName = loadingWindow->name();
      savingWindow->setText(fileName);
      QString path = _dir.mapsPath() + fileName + ".txt";
      scene.createMap(_width, _height, path);
  });
  // on map saved
  connect(&scene, &Scene::saved, [this](){
      QString name = savingWindow->getText();
      fileName = name;
      savingWindow->setText(fileName);
      loadingWindow->renew();
  });
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  int w = this->width();
  int h = this->height() - ui->menubar->height();

  ui->graphicsView->setGeometry(0, 0, w, h);
  Q_UNUSED(event);
}

void MainWindow::saveMap()
{
  warningWindow = new WarningMessage;
  QString name = savingWindow->getText();
  if (name.isEmpty())
    name = "UNSAVED";

  QString path = _dir.mapsPath() + name + ".txt";
  if (_dir.findFile(QString(name + ".txt")) &&
      (this->fileName != name))
    {
      warningWindow->showMessage("Map with this name exist. Rewrite it?");
      connect(warningWindow, &QMessageBox::rejected, [this](){
          this->savingWindow->show();
          emit readyToClearWarningWindow();
        });
      connect(warningWindow, &QMessageBox::accepted, [this, path]() {
          scene.saveMap(path);
          emit readyToClearWarningWindow();
        });
    }
  else {
      scene.saveMap(path);
      emit readyToClearWarningWindow();
    }

}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::quit();
}

void MainWindow::clearWarningWindowPointer()
{
  delete warningWindow;
  warningWindow = nullptr;
}

MainWindow::~MainWindow()
{
  saveMap();
  delete ui;
}

void MainWindow::on_actionNew_fmap_triggered()
{
  creatingWindow->show();
}

void MainWindow::on_actionOpen_map_triggered()
{
  loadingWindow->show();
}

void MainWindow::on_actionSave_map_triggered()
{
  savingWindow->show();
}
