#include "warningmessage.h"

WarningMessage::WarningMessage()
{
  setWindowIcon(QIcon(":/images/build1.png"));
  setStyleSheet("font-size: 20px");
  setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
}

void WarningMessage::showMessage(QString msg)
{
  setText(msg);
  show();
}
