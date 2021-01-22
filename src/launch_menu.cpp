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

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "bot");
  db.setForwardOnly(true);
  db.setDatabaseName("name_for_now.db");

  if(db.open())
  {
    query.exec("SELECT count(*) FROM sqlite_master WHERE TYPE='table';");
    int number_of_tables =  query.next().value(0);

    for(int i=0;i<number_of_tables;i++)
    {

    }
    //QSqlRecord rec = q.record();
  }
  else
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);

  QTreeWidgetItem *header = new QTreeWidgetItem();
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
