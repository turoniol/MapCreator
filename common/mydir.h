#ifndef MYDIR_H
#define MYDIR_H

#include <QDir>
#include <QStringList>

class MyDir
{
public:
  MyDir();
  QString mapsPath() const;
  QString path() const;
  QStringList names();
  bool findFile(QString s);
  bool remove(QString name);
  bool isEmpty();
private:
  QDir dir;
  QString _path;
  QString _name;
  QStringList _list;
};

#endif // MYDIR_H
