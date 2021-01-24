#include "launch_menu.h"
//#include "TableWidget.h"
//#include "QButtonTreeWidget.h"

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

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test");
  db.setDatabaseName("lauch.db");

  if(db.open())
  {
    QSqlQuery query(QSqlDatabase::database("test"));
    query.exec("SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name != 'android_metadata' AND name != 'sqlite_sequence';");
    query.next();
    setWindowTitle(query.value(0).toString());
    /*for(int i=0;i<number_of_tables;i++)
    {

    }*/
    //QSqlRecord rec = q.record();
  }
  else
  {
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);
  }

  QTreeWidgetItem *header = new QTreeWidgetItem();
    header->setText(0, "ez");
  QTreeWidgetItem *sub = new QTreeWidgetItem();
    sub->setText(0,"sub");

  header->addChild(sub);

  QTreeWidget *navigator = new QTreeWidget();
    navigator->setFrameShape(QFrame::NoFrame);
    navigator->setMaximumWidth(100);
    navigator->insertTopLevelItem(0, header);

  layout->setContentsMargins(0,0,0,0);
  layout->addWidget(navigator);
  setLayout(layout);
}
