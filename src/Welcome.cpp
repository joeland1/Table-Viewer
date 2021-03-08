#include "Welcome.h"

#include <QLabel>

//might be removed idk yet
Welcome::Welcome(QWidget *parent):Overview_Master(parent)
{
  test->addWidget(new QLabel("welcome to table viewer"));
}
