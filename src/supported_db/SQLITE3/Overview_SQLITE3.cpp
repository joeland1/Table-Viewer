#include "supported_db/SQLITE3/Overview_SQLITE3.h"

#include <QLabel>
#include <QGridLayout>

Overview_SQLITE3::Overview_SQLITE3(QWidget *parent):Overview_Master(parent)
{
  //each cell is QLineEdit so that user can change values
  QVBoxLayout *test = new QVBoxLayout();
  test->addWidget(new QLabel("Version: SQLITE3"));
  setLayout(test);
}

/*
QWidget *test = new QWidget();
new QPushButton(QString::number(data_entry->width()), test);
test->show();
*/
