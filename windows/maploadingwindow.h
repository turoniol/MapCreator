#ifndef MAPLOADINGWINDOW_H
#define MAPLOADINGWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>

#include "common/mydir.h"
#include "warningmessage.h"

class MapLoadingWindow : public QDialog
{
  Q_OBJECT
public:
  MapLoadingWindow(QWidget *parent);
  void show();
  void renew();
  QString name();
private:
  // variables
  QString _current_text;
  MyDir _dir;
  WarningMessage *msg;
  QVBoxLayout *layout;
  QListWidget *list;
  QDialogButtonBox *button;
  // funstions
  void addItem();
signals:
  void choosen();
  void deleted();
};

#endif // MAPLOADINGWINDOW_H
