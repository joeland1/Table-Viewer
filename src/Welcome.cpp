#include "Welcome.h"

#include <QLabel>

//might be removed idk yet
Overview_SQLITE3::Overview_SQLITE3(QWidget *parent):Overview_Master(parent)
{
  test->addWidget(new QLabel("welcome to table viewer"));
}
