#include "mydir.h"
#include <QDebug>

MyDir::MyDir()
{
  _name = "/maps/";
  _path = QDir::currentPath() + _name;
  dir.setPath(_path);
}

QString MyDir::mapsPath() const
{
  return _path;
}

QString MyDir::path() const
{
  return QDir::currentPath();
}

QStringList MyDir::names()
{
  QStringList filters;
  filters << "*.txt";
  _list = dir.entryList(filters);
  return _list;
}

bool MyDir::findFile(QString s)
{
  return _list.contains(s);
}

bool MyDir::remove(QString name)
{
  return dir.remove(name);
}

bool MyDir::isEmpty()
{
  QStringList filters;
  filters << "*.txt";
  _list = dir.entryList(filters);
  return _list.isEmpty();
}
