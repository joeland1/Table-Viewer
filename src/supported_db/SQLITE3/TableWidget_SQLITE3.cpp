#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"

#include <QLineEdit>
#include <QGridLayout>

//sququery and sqldb should be removed soon
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>

#include <QMessageBox>
#include <QPushButton>
TableWidget_SQLITE3::TableWidget_SQLITE3(QWidget *parent, QString table_name):TableWidget_Master(parent)
{
  //each cell is QLineEdit so that user can change values
  table_data = new QGridLayout;

  //these values will need to be passed during construction, fix.
  //also need to get the databse names somehow before contsruction
  //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test");
  //db.setDatabaseName("lauch.db");

  QSqlDatabase db = QSqlDatabase::database("test");
  QSqlQuery query_pending(QSqlDatabase::database("test"));
  query_pending.exec("SELECT name FROM sqlite_master WHERE type = 'table'");

  if(db.open())
  {
    QSqlQuery query(QSqlDatabase::database("test"));
    while(query_pending.next())
    {
      query.prepare("SELECT * FROM ?");
      setWindowTitle(query_pending.value(0).toString());
      query.addBindValue(query_pending.value(0).toString());

      query.exec();

      int number_of_columns=query.size();

      while(query.next())
      {
        int num_rows_currently = table_data->rowCount();
        for(int i=0;i<=number_of_columns;i++)
        {
          QLineEdit *data_entry = new QLineEdit();
          data_entry->setText(query.value(i).toString());
          table_data->addWidget(data_entry,num_rows_currently,i);
        }
      }
    }
    setLayout(table_data);
  }
  else
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);*/
}
