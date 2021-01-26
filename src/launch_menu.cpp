#include "launch_menu.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QMessageBox>

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QLabel>

Launch::Launch(QWidget *parent):QWidget(parent)
{
  QHBoxLayout *layout = new QHBoxLayout();

  QTreeWidget *navigator = new QTreeWidget();
    navigator->setFrameShape(QFrame::NoFrame);
    //navigator->setMaximumWidth(100);

  layout->setContentsMargins(0,0,0,0);
  layout->addWidget(navigator);

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test");
  db.setDatabaseName("lauch.db");

  if(db.open())
  {
    QSqlQuery query(QSqlDatabase::database("test"));
    query.exec("SELECT count(*) FROM sqlite_master WHERE type = 'table'");
    query.next();
    int number_of_tables = query.value(0).toInt();
    query.exec("SELECT name FROM sqlite_master WHERE type = 'table'");

    QTreeWidgetItem *header = new QTreeWidgetItem();
      header->setText(0, "stem");

    while(query.next())
    {
      QTreeWidgetItem *sub = new QTreeWidgetItem();
      sub->setText(0, query.value(0).toString());
      header->addChild(sub);
    }
    navigator->insertTopLevelItem(0, header);
    layout->addWidget(navigator);

    /*for(int i=0;i<number_of_tables;i++)
    {

    }*/
    //QSqlRecord rec = q.record();
  }
  else
  {
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);
  }

  setLayout(layout);
}
