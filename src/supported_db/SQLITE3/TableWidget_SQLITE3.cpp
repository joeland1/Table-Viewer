#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"

#include <QLineEdit>
#include <QGridLayout>

//sququery and sqldb should be removed soon
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>

#include <QMessageBox>
#include <QPushButton>
TableWidget_SQLITE3::TableWidget_SQLITE3(QString table_name, QWidget *parent):TableWidget_Master(parent)
{
  //each cell is QLineEdit so that user can change values
  table_data = new QGridLayout;

  //these values will need to be passed during construction, fix.
  //also need to get the databse names somehow before contsruction
  //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test");
  //db.setDatabaseName("lauch.db");

  QSqlDatabase db = QSqlDatabase::database("test");


    QSqlQuery query(QSqlDatabase::database("test"));

    query.exec("PRAGMA table_info(DISCORD_TOKEN)");
    //query.addBindValue(table_name);
    //query.exec();
    while(query.next())
    {
      table_data->addWidget(new QPushButton(query.value(1).toString()));
    }
    setLayout(table_data);
}
