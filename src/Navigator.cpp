#include "launch_menu.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QMessageBox>

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QLabel>

Navigator::Navigator(QWidget *parent):QWidget(parent)
{
  QHBoxLayout *layout = new QHBoxLayout();

  QTreeWidget *top = new QTreeWidget();
    top->setFrameShape(QFrame::NoFrame);
    //navigator->setMaximumWidth(100);

  layout->setContentsMargins(0,0,0,0);
  layout->addWidget(top);

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test");
  db.setDatabaseName("lauch.db");

  if(db.open())
  {
    QSqlQuery query(QSqlDatabase::database("test"));
    query.exec("SELECT name FROM sqlite_master WHERE type = 'table'");

    QTreeWidgetItem *header = new QTreeWidgetItem();
      header->setText(0, "databse name:connection type");

    while(query.next())
    {
      QTreeWidgetItem *sub = new QTreeWidgetItem();
      sub->setText(0, query.value(0).toString());
      header->addChild(sub);
    }
    top->insertTopLevelItem(0, header);
    layout->addWidget(top);

    db.close()
  }
  else
  {
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);
  }

  setLayout(layout);
}
