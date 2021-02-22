#include "supported_db/SQLITE3/Overview_SQLITE3.h"

#include <QLabel>

Overview_SQLITE3::Overview_SQLITE3(QString table_name, QWidget *parent):Overview_Master(parent)
{
  //each cell is QLineEdit so that user can change values
  new QLabel("test", this);
}

/*
QWidget *test = new QWidget();
new QPushButton(QString::number(data_entry->width()), test);
test->show();
*/
