#include "Welcome.h"

#include <QLabel>

//might be removed idk yet
Welcome::Welcome(QWidget *parent):QWidget(parent)
{
  new QLabel("welcome to table viewer", this);
}
