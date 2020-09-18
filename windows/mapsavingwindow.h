#ifndef MAPSAVINGWINDOW_H
#define MAPSAVINGWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QFile>
#include <QRegExpValidator>

class MapSavingWindow : public QDialog
{
  Q_OBJECT
public:
  MapSavingWindow(QWidget *parent = nullptr, QString file_name = NULL);
  QString getText();
private:
  // variables
  QVBoxLayout* layout;
  QLabel *label;
  QDialogButtonBox *button_box;
  QLineEdit *line_edit;

private slots:
  void checkedAccept();
};

#endif // MAPSAVINGWINDOW_H
