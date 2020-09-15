#ifndef WARNINGMESSAGE_H
#define WARNINGMESSAGE_H

#include <QMessageBox>
#include <QIcon>

class WarningMessage : public QMessageBox
{
public:
  WarningMessage();
  void showMessage(QString msg);
};

#endif // WARNINGMESSAGE_H
