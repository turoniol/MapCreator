#include "mapcreatingwindow.h"
#include <QDebug>

MapCreatingWindow::MapCreatingWindow(QWidget *parent) : QDialog(parent)
{
  this->parent = parent;
  setFixedSize(200, 175);
  // ptr init
  layout = new QVBoxLayout(this);
  coordinateBox = new QGroupBox(this);

  coordinateBox->setTitle("Map size");
  addFields();
  addButtons();
  connectSlots();
  setStyle();
}

int MapCreatingWindow::getX() const
{
  return ex->text().toInt();
}

int MapCreatingWindow::getY() const
{
  return ey->text().toInt();
}

void MapCreatingWindow::addFields()
{
  boxLayout = new QGridLayout;
  // labels
  lx = new QLabel("Width: ");
  ly = new QLabel("Height: ");
  // text edits
  ex = new QLineEdit;
  ey = new QLineEdit;
  // geometry of widgets
  boxLayout->addWidget(lx, 0, 0);
  boxLayout->addWidget(ex, 0, 1);
  boxLayout->addWidget(ly, 1, 0);
  boxLayout->addWidget(ey, 1, 1);

  ex->setValidator( new QRegExpValidator(QRegExp("[1-9][0-9]")) );
  ey->setValidator( new QRegExpValidator(QRegExp("[1-9][0-9]")) );

  coordinateBox->setLayout(boxLayout);
  layout->addWidget(coordinateBox);
}

void MapCreatingWindow::addButtons()
{
  buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                   QDialogButtonBox::Cancel);
  layout->addWidget(buttonBox);
}

void MapCreatingWindow::setStyle()
{
  setWindowTitle("New map");
  coordinateBox->setStyleSheet("font-size: 16px");
}

void MapCreatingWindow::connectSlots()
{
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
  connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
}

