#include "supported_db\master-widget\TableWidget_Master.h"

#include <QWidget>
#include <QLabel>
#include <sstream>
#include <QList>
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

bool TableWidget_Master::refresh_tables()
{
	return false;
}

bool TableWidget_Master::write_to_db_table()
{
  return false;
}

bool TableWidget_Master::write_to_db_all()
{
  return false;
}
