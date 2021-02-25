#include "supported_db/SQLITE3/Overview_SQLITE3.h"

#include <QLabel>
#include <QGridLayout>

Overview_SQLITE3::Overview_SQLITE3(QString table_name, QWidget *parent):Overview_Master(parent)
{
  //each cell is QLineEdit so that user can change values
  QVBoxLayout *test = new QVBoxLayout();

  test->addWidget(new QLabel("Version: SQLITE3"), this));
  test->addWidget(new QLabel(QString::fromStdString(Overview_Master::get_database_type()), this));

  setLayout(test);
}

/*
QWidget *test = new QWidget();
new QPushButton(QString::number(data_entry->width()), test);
test->show();
*/
