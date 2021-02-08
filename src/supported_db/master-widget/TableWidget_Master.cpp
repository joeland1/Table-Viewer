#include "supported_db\master-widget\TableWidget_Master.h"

#include <QWidget>
#include <sstream>

TableWidget_Master::TableWidget_Master(QWidget *parent):QWidget(parent)
{

}

std::string TableWidget_Master::get()
{
  std::ostringstream address;
  address << (void const *)this;
  std::string name = address.str();
  return name;
}
