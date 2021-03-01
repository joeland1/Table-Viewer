#include "supported_db\master-widget\Overview_Master.h"

#include <QWidget>
#include <sstream>

Overview_Master::Overview_Master(QWidget *parent):QWidget(parent)
{
  database_type=nullptr;
  database_name=nullptr;
}

std::string Overview_Master::get()
{
  std::ostringstream address;
  address << (void const *)this;
  std::string name = address.str();
  return name;
}

void Overview_Master::set_database_type(std::string type)
{
  database_type=type;
}
  std::string Overview_Master::get_database_type()
  {
    return database_type;
  }

void Overview_Master::set_database_name(std::string name)
{
  database_type=name;
}
  std::string Overview_Master::get_database_name()
  {
    return database_name;
  }
