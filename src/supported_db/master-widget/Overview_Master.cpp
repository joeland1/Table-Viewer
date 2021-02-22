#include "supported_db\master-widget\Overview_Master.h"

#include <QWidget>
#include <sstream>

Overview_Master::Overview_Master(QWidget *parent):QWidget(parent)
{

}

std::string Overview_Master::get()
{
  std::ostringstream address;
  address << (void const *)this;
  std::string name = address.str();
  return name;
}
