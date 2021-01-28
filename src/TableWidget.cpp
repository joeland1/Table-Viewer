#include "TableWidget.h"

#include <QLineEdit>
#include <QGridLayout>

//sququery and sqldb should be removed soon
#include <QSqlQuery>
#include <QSqlDatabase>

TableWidget::TableWidget(QWidget *parent):QWidget(parent)
{
  table_data = new QGridLayout();
  //each cell is QLineEdit so that user can change values

  //these values will need to be passed during construction, fix.
  //also need to get the databse names somehow before contsruction
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test");
  db.setDatabaseName("lauch.db");

  QSqlQuery query_pending(QSqlDatabase::database("test"));
  query_pending.exec("SELECT name FROM sqlite_master WHERE type = 'table'");

  if(db.open())
  {
    QSqlQuery query(QSqlDatabase::databse("test"));
    while(query_pending.next())
    {
      query.exec("SELECT * FROM "+query_pending.value(0).toString());
      while(query.next())
      {
        table_data
      }
    }
  }
  else
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);
}
