//#include "QButtonTreeWidget.h"

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

QButtonTreeWidget::QButtonTreeWidget(QWidget *parent):QWidget(parent)
{
  layout = new QGridLayout();
}

void QButtonTreeWidget::addEntry(QString text, bool is_collapsable)
{
  if(is_collapsable)
  {
    QPushButton *collapsor = new QPushButton("collapse");
    QPushbutton *connection_name = new QPushButton("xxx");
  }

  else
  {

  }

}
