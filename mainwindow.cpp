#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include "map.h"
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowIcon(QIcon(":/images/grass.png"));
  this->setWindowTitle("Map editor");
  this->setMinimumWidth(800);
  this->setMinimumHeight(640);

  QScreen *screen = QGuiApplication::primaryScreen(); // getting of the size of the user`s display
  QRect rec = screen->geometry();
  _width = rec.width();
  _height = rec.height();

  ui->graphicsView->setMouseTracking(true);
  ui->saveButton->setText("Save map");
  ui->loadButton->setText("Load map");
  addEditBlockView(_width, _height); // edit block
  setTextEditGeometry();

  addScene(0.8*_width, _height);
  fileName = "map1";
  QString defaulPath = QDir::currentPath() + "/maps/" + fileName + ".txt";

  scene.createMap(0.8*_width, defaulPath);
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
  ui->saveEdit->setGeometry(width, 0, width/4, sEh);
  ui->saveButton->setGeometry(width, sEh, width/4, sEh);
  ui->loadButton->setGeometry(width, sEh + 0.05*w, width/4, sEh);
  ui->comboBox->setGeometry(width, sEh + 0.1*w, width/4, sEh);

  QString styleSheet = "font-size: " + QString::number(sEh/2) + "px";
  ui->saveEdit->setStyleSheet(styleSheet);
  ui->comboBox->setStyleSheet(styleSheet);
  ui->saveButton->setStyleSheet(styleSheet);
  ui->loadButton->setStyleSheet(styleSheet);
}

void MainWindow::setEditBlockGeometry(unsigned width, unsigned height, unsigned a)
{
  unsigned w = 0.75*a;
  ui->editBlockView->setGeometry(width - w/2 - a/2, height - w/2 - a/2, w, w);
  editBlockScene.setSceneRect(0, 0, w, w);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  (void)event;
  int _width = this->width();
  int _height = this->height();
  unsigned rightAreaWidth = 0.2*_width;

  ui->graphicsView->setGeometry(0, 0, 0.8*_width, _height);
  setEditBlockGeometry(_width, _height, rightAreaWidth);
  setTextEditGeometry();

  unsigned s = ui->editBlockView->width();
  blockArea.setSize(s);
  blockArea.setPix();
}

void MainWindow::loadingFailded() {
  QMessageBox *msg = new QMessageBox(this); // message box
  msg->setText("File doesn't exist");
  msg->setStandardButtons(QMessageBox::Ok);
  msg->show();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_loadButton_clicked()
{
  QString name = ui->saveEdit->toPlainText();
  QString path = QDir::currentPath() + "/maps/" + name + ".txt";

  if(!scene.createMap(0.8*_width, path)) {
      loadingFailded();
    }
}

void MainWindow::on_saveButton_clicked()
{
  QString name = ui->saveEdit->toPlainText();
  QString path = QDir::currentPath() + "/maps/" + name + ".txt";

  scene.saveMap(path);
}
