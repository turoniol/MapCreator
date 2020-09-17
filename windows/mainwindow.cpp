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
  _height = rec.height() - ui->menubar->height();

  ui->graphicsView->setMouseTracking(true);
  // adding the edit block
  addEditBlockView(_width, _height);
  // text edit geometry
  setTextEditGeometry();

  creatingWindow = new MapCreatingWindow(this, &scene);

  // checking map`s dir
  if(!QDir("maps").exists())
    QDir().mkdir("maps");

  // adding items in combo box
  addScene(0.8*_width, _height);

  renewComboBox();

  fileName = ui->comboBox->currentText();
  QString defaulPath = QDir::currentPath() + "/maps/" + fileName + ".txt";
  // map creating
  if(!scene.createMap(0.8*_width, defaulPath))
    creatingWindow->show();


  scene.setBlocke(&blockArea, ui->graphicsView);
  ui->saveEdit->setText(fileName);
}

void MainWindow::addScene(const int w, const int h) {
  scene.setSceneRect(0, 0, w, h);
  ui->graphicsView->setScene(&scene);
}

void MainWindow::addEditBlockView(const int w, const int h)
{
  unsigned rightAreaWidth = 0.2*w;
  ui->editBlockView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // scroll bars
  ui->editBlockView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setEditBlockGeometry(w, h, rightAreaWidth);
  ui->editBlockView->setScene(&editBlockScene);
  editBlockScene.addItem(&blockArea);

  unsigned s = ui->editBlockView->width();
  blockArea.setSize(s);
  blockArea.setPix();
}

void MainWindow::setTextEditGeometry()
{
  int w = this->width();
  int width = 0.8*w;

  int sEh = w/20;
  // buttons
  ui->saveEdit->setGeometry(width, 0,
                            width/4, sEh);
  ui->comboBox->setGeometry(ui->saveEdit->x(), ui->saveEdit->height(),
                              ui->saveEdit->width(), ui->saveEdit->height());


  // stylesheet
  QString styleSheet = "font-size: " + QString::number(sEh/2) + "px";
  ui->saveEdit->setStyleSheet(styleSheet);
  ui->comboBox->setStyleSheet(styleSheet);
}

void MainWindow::setEditBlockGeometry(unsigned width, unsigned height, unsigned a)
{
  unsigned w = 0.75*a;
  ui->editBlockView->setGeometry(width - w/2 - a/2, height - w/2 - a/2, w, w);
  editBlockScene.setSceneRect(0, 0, w, w);
}

bool MainWindow::renewComboBox()
{
  QDir directory(QDir::currentPath() + "/maps");
  QStringList list = directory.entryList();
  ui->comboBox->clear();
  if(list.length() == 0) {
      return false;
    }
  for(auto obj : list) {
      if(obj.contains(".txt")) {
          ui->comboBox->addItem(obj.remove(".txt"));
        }
    }
  return true;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  (void)event;
  int _width = this->width();
  int _height = this->height() - ui->menubar->height();

  unsigned rightAreaWidth = 0.2*_width;

  ui->graphicsView->setGeometry(0, 0, 0.8*_width, _height);
  setEditBlockGeometry(_width, _height, rightAreaWidth);
  setTextEditGeometry();

  unsigned s = ui->editBlockView->width();
  blockArea.setSize(s);
  blockArea.setPix();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    (void)index;
    ui->saveEdit->setText(ui->comboBox->currentText());
}

void MainWindow::on_actionNew_fmap_triggered()
{
  creatingWindow->show();
}

void MainWindow::on_actionOpen_map_triggered()
{
  QString name = ui->saveEdit->toPlainText();

  if(!name.isEmpty()) {
      QString path = QDir::currentPath() + "/maps/" + name + ".txt";
      if(!scene.createMap(_width, path)) {
          warningWindow.showMessage("File with this name doesn`t exist!");
        }
    }
}

void MainWindow::on_actionSave_map_triggered()
{
  QString name = ui->saveEdit->toPlainText();

  if(!name.isEmpty()) {
      QString path = QDir::currentPath() + "/maps/" + name + ".txt";
      scene.saveMap(path);
      renewComboBox();
    }
  else {
      warningWindow.showMessage("Invalid filename!");
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
