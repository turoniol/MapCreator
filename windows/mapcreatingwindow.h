#ifndef MAPCREATINGWINDOW_H
#define MAPCREATINGWINDOW_H

#include <QDialog>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QIntValidator>

#include "scene/scene.h"

class MapCreatingWindow : public QDialog
{
  Q_OBJECT
public:
  MapCreatingWindow(QWidget *parent, Scene *scene);
private:
  // variables
  Scene *scene;
  QLabel *lx, *ly;
  QLineEdit *ex, *ey;
  QWidget *parent;
  QVBoxLayout *layout;
  QGridLayout *boxLayout;
  QGroupBox *coordinateBox;
  QDialogButtonBox *buttonBox;

  // functions
  void addFields();
  void addButtons();
  void setStyle();
  void connectSlots();
private slots:
  void acceptClicked();
};

#endif // MAPCREATINGWINDOW_H
