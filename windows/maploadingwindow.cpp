#include "maploadingwindow.h"
#include <QPushButton>

MapLoadingWindow::MapLoadingWindow(QWidget *parent) : QDialog(parent)
{
  setFixedSize(300, 350);
  setWindowTitle("Load");

  layout = new QVBoxLayout(this);
  list = new QListWidget(this);
  button = new QDialogButtonBox(QDialogButtonBox::Ok);
  msg = new WarningMessage;
  QPushButton* delete_btn = button->addButton("Delete", QDialogButtonBox::DestructiveRole);

  layout->addWidget(list);
  layout->addWidget(button);
  list->setStyleSheet("font-size: 20px");
  connect(delete_btn, &QPushButton::clicked, [this]() { emit deleted(); });
  connect(button, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(this, &MapLoadingWindow::deleted, [this]() {
      msg->showMessage(QString("Do you really want to delete \n" + name() + "?"));
  });
  connect(list, &QListWidget::itemClicked, [this]() {
      _current_text = list->currentItem()->text();
      emit choosen();
  });
  connect(msg, &QMessageBox::accepted, [this]() {
      _dir.remove(name() + ".txt");
      renew();
  });
}

void MapLoadingWindow::show()
{
  renew();
  QDialog::show();
}

QString MapLoadingWindow::name()
{
  return _current_text.remove(_current_text.size() - 4, 4);
}

void MapLoadingWindow::renew()
{
  list->clear();
  list->addItems(_dir.names());
}

