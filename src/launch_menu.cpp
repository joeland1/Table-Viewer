#include "launch_menu.h"
//#include "TableWidget.h"
//#include "QButtonTreeWidget.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>

Launch::Launch(QWidget *parent):QWidget(parent)
{
  QHBoxLayout *layout = new QHBoxLayout();

  QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,"ez");
  QTreeWidgetItem *sub = new QTreeWidgetItem();
    sub->setText(0,"sub");

  item->addChild(sub);

  QTreeWidget *navigator = new QTreeWidget();
    navigator->setFrameShape(QFrame::NoFrame);
    navigator->setMaximumWidth(100);
    navigator->insertTopLevelItem(0, item);

  layout->setContentsMargins(0,0,0,0);
  layout->addWidget(navigator);
  setLayout(layout);
}
