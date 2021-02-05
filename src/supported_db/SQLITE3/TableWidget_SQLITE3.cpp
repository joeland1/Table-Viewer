#include "supported_db/master-widget/TableWidget.h"

#include <QLineEdit>
#include <QGridLayout>

//sququery and sqldb should be removed soon
#include <QSqlQuery>
#include <QSqlDatabase>

TableWidget_SQLITE3::TableWidget_SQLITE3(QWidget *parent):TableWidget(parent)
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
      query.prepare("SELECT * FROM ?;");
      query.bindValue(query_pending.value(0).toString());
      query.exec();

      int number_of_rows=query.size();

      while(query.next())
      {
        for(int i=0;i<=number_of_rows;i++)
        {
          QLineEdit *data_entry = new QLineEdit();
          data_entry->setText(query.value(i).toString());
          table_data->addWidget(i,0,table_data->rowCount());
        }
      }
    }
  }
  else
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);
}
