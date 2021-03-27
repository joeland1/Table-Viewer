#include "supported_db/SQLITE3/Overview_SQLITE3.h"
#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"
#include "Navigator.h"

#include <QLabel>
#include <QGridLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QList>
#include <QString>

Overview_SQLITE3::Overview_SQLITE3(QString path, QWidget *parent):Overview_Master(parent)
{
  //each cell is QLineEdit so that user can change values
  this->path = path;

  QVBoxLayout *test = new QVBoxLayout();
  test->addWidget(new QLabel("Version: SQLITE3"));
  setLayout(test);
}

bool Overview_SQLITE3::write_to_db(QList<QWidget *> table_widgets)
{
  for(int i=0;i<table_widgets.size();i++)
  {
    TableWidget_SQLITE3 *target = dynamic_cast<TableWidget_SQLITE3 *>(table_widgets.at(i));
    //target->write_to_db_table(path);
    target->write_to_db_table();
  }

  return true;
}

QString Overview_SQLITE3::get_connection_info()
{
  return this->path;
}
