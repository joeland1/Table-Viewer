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

#include <QSplitter>

#include <QSqlRecord>
TableWidget_SQLITE3::TableWidget_SQLITE3(QString table_name,QString db_path, QWidget *parent):TableWidget_Master(parent)
{
  master_splitter = new QSplitter();
    master_splitter->setHandleWidth(1);
    master_splitter->setContentsMargins(0,0,0,0);
    master_splitter->setStyleSheet("QSplitter::handle{background: black;}");
  //each cell is QLineEdit so that user can change values

  //these values will need to be passed during construction, fix.
  //also need to get the databse names somehow before contsruction

  QSqlDatabase db = QSqlDatabase::database(db_path);
  QSqlQuery query(QSqlDatabase::database(db_path));

  query.exec("PRAGMA table_info("+table_name+")");

  QList<QString> column_names;
  while(query.next())
  {
    /*QPushButton *column_button = new QPushButton(query.value(1).toString());
      column_button->setContentsMargins(0,0,0,0);
      column_button->setStyleSheet("border: 1px solid black;\
        padding-right: 1px;\
        padding-left: 1px");
    table_data_header->addWidget(column_button);*/
    column_names.append(query.value(1).toString());
  }

  //table_data->addLayout(table_data_header);

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

  QList<QSqlRecord> recs;
  while(query.next())
    recs.append(query.record());

  for(int i=0;i<column_names.size();i++)
  {
    QVBoxLayout *adding_layout = new QVBoxLayout();
    adding_layout->setAlignment(Qt::AlignTop);
    adding_layout->setContentsMargins(0,0,0,0);
    adding_layout->setSpacing(0);

    QPushButton *column_button = new QPushButton(column_names.at(i));
      column_button->setStyleSheet("border: 1px solid black;\
        padding-right: 1px;\
        padding-left: 1px;\
        border-right-width: 0px;\
        border-left-width: 0px");
    adding_layout->addWidget(column_button);

    for(int j=0;j<recs.size();j++)
    {
      QLineEdit *data_entry = new QLineEdit(recs.at(j).value(i).toString());
      data_entry->setStyleSheet("border: 1px solid black;\
        padding-right: 1px;\
        padding-left: 1px;\
        border-right-width: 0px;\
        border-left-width: 0px");
      adding_layout->addWidget(data_entry);
    }

    QWidget *adding_widget = new QWidget();
      adding_widget->setLayout(adding_layout);
      adding_widget->setContentsMargins(0,0,0,0);

    master_splitter->addWidget(adding_widget);
  }
  QVBoxLayout *makebig = new QVBoxLayout();
    makebig->addWidget(master_splitter);
    makebig->setContentsMargins(0,0,0,0);
  setLayout(makebig);

}

void TableWidget_SQLITE3::sync_column_sizes()
{

}

/*
QWidget *test = new QWidget();
new QPushButton(QString::number(data_entry->width()), test);
test->show();
*/
