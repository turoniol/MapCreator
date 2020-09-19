#ifndef MAPCREATINGWINDOW_H
#define MAPCREATINGWINDOW_H

#include <QDialog>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QIntValidator>

class MapCreatingWindow : public QDialog
{
  Q_OBJECT
public:
  MapCreatingWindow(QWidget *parent);
  int getX() const;
  int getY() const;
private:
  // variables
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
};

#endif // MAPCREATINGWINDOW_H
