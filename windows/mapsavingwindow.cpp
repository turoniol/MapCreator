#include "mapsavingwindow.h"

MapSavingWindow::MapSavingWindow(QWidget *parent) : QDialog(parent)
{
  setFixedSize(200, 150);
  setWindowTitle("Save");

  layout = new QVBoxLayout(this);
  label = new QLabel("Name:");
  button_box = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
  line_edit = new QLineEdit;
  // style
  line_edit->setGeometry(0, 0, this->width(), 50);
  line_edit->setStyleSheet("font-size: 25px");
  label->setGeometry(this->width()/2, 0, this->width(), 50);
  label->setStyleSheet("font-size: 25px;  qproperty-alignment: \'AlignHCenter\';");

  layout->addWidget(label);
  layout->addWidget(line_edit);
  layout->addWidget(button_box);

  line_edit->setValidator(new QRegExpValidator(QRegExp("[0-Z|a-z|A-Z]{1,15}")));
  connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
  connect(button_box, &QDialogButtonBox::accepted, this, &MapSavingWindow::checkedAccept);
}

QString MapSavingWindow::getText()
{
  return line_edit->text();
}

void MapSavingWindow::setText(QString t)
{
  line_edit->setText(t);
}

void MapSavingWindow::checkedAccept()
{
  if (!getText().isEmpty())
    QDialog::accept();
}
