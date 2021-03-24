#include "supported_db/SQLITE3/Overview_SQLITE3.h"
#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"
#include "Navigator.h"

#include <QLabel>
#include <QGridLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QList>

Overview_SQLITE3::Overview_SQLITE3(QString path, QWidget *parent):Overview_Master(parent)
{
  //each cell is QLineEdit so that user can change values
  this->path = path;

  QVBoxLayout *test = new QVBoxLayout();
  test->addWidget(new QLabel("Version: SQLITE3"));
  setLayout(test);
}

bool Overview_SQLITE3::write_to_db(QList<TableWidget_SQLITE3 *> table_widgets)
{
  for(TableWidget_SQLITE3 *i:table_widgets)
    i->write_to_db_table(path);
  return true;
}
/*
QWidget *test = new QWidget();
new QPushButton(QString::number(data_entry->width()), test);
test->show();
*/
