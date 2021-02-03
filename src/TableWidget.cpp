#include "TableWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

TableWidget::TableWidget(QWidget *parent):QWidget(parent)
{
  new QLabel("table has not been loaded", this);
}

bool TableWidget::load_data()
{
  return true;
}
