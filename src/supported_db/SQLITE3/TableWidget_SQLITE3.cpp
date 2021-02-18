#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"

#include <QLineEdit>
#include <QGridLayout>

//sququery and sqldb should be removed soon
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>

#include <QMessageBox>
#include <QPushButton>
#include <QList>

#include <QVBoxLayout>
#include <QHBoxLayout>
TableWidget_SQLITE3::TableWidget_SQLITE3(QString table_name, QWidget *parent):TableWidget_Master(parent)
{
  //each cell is QLineEdit so that user can change values
  table_data = new QVBoxLayout;
    table_data->setContentsMargins(0,0,0,0);
    table_data->setSpacing(0);
    table_data->setMargin(0);
    table_data->setAlignment(Qt::AlignTop);

  table_data_header = new QHBoxLayout;
    table_data_header->setContentsMargins(0,0,0,0);
    table_data_header->setSpacing(0);
    table_data_header->setMargin(0);
    table_data_header->setAlignment(Qt::AlignLeft);

  //these values will need to be passed during construction, fix.
  //also need to get the databse names somehow before contsruction
  //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test");
  //db.setDatabaseName("lauch.db");

  QSqlDatabase db = QSqlDatabase::database("test");


  QSqlQuery query(QSqlDatabase::database("test"));

  query.exec("PRAGMA table_info("+table_name+")");

  QList<QString> column_names;
  while(query.next())
  {
    QPushButton *column_button = new QPushButton(query.value(1).toString());
      column_button->setContentsMargins(0,0,0,0);
      column_button->setStyleSheet("border: 1px solid black;\
        padding-right: 6px;\
        padding-left: 6px");
    table_data_header->addWidget(column_button);
    column_names.append(query.value(1).toString());
  }

  table_data->addLayout(table_data_header);

  QString db_statement="";
  db_statement.append("SELECT ");
  for(int i=0;i<column_names.size();i++)
  {
    db_statement.append(column_names.at(i));
    if(i!=column_names.size()-1)
      db_statement.append(",");
  }
  db_statement.append(" FROM "+table_name);
  query.exec(db_statement);

  while(query.next())
  {
    QHBoxLayout *data_entry_layout = new QHBoxLayout;
    for(int i=0;i<column_names.size();i++)
    {
      QLineEdit *data_entry = new QLineEdit(query.value(i).toString());
        data_entry->setStyleSheet("border: 1px solid black;\
          padding-right: 6px;\
          padding-left: 6px");
      data_entry_layout->addWidget(data_entry);
    }
    table_data->addLayout(data_entry_layout);
  }

  TableWidget_SQLITE3::sync_column_sizes();
  setLayout(table_data);
}

void TableWidget_SQLITE3::sync_column_sizes()
{
  for(int i=0;i<table_data_header->count();i++)
  {
    //int desired_height = table_data_header->itemAt(i)->widget()->height();
    //int desired_width = table_data_header->itemAt(i)->widget()->sizeHint().width();
    int desired_width = 0;

    for(int j=0;j<table_data->count();j++)
    {
      if(desired_width < table_data->itemAt(j)->layout()->itemAt(i)->widget()->sizeHint().width())
        desired_width = table_data->itemAt(j)->layout()->itemAt(i)->widget()->sizeHint().width();
    }
    //QSize desired_size = table_data_header->itemAt(i)->widget()->size();
    for(int j=0;j<table_data->count();j++)
    {
      QLayout *single_data_entry = table_data->itemAt(j)->layout();
      single_data_entry->itemAt(i)->widget()->setFixedWidth(desired_width);
    }
  }
}

/*
QWidget *test = new QWidget();
new QPushButton(QString::number(data_entry->width()), test);
test->show();
*/
