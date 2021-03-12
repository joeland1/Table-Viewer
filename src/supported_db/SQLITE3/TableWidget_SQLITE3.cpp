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

#include <QAction>
#include <QMenu>
TableWidget_SQLITE3::TableWidget_SQLITE3(QString table_name,QString db_path, QWidget *parent):TableWidget_Master(parent)
{
  file_location = db_path;

  master_splitter = new QSplitter();
    master_splitter->setHandleWidth(1);
    master_splitter->setContentsMargins(0,0,0,0);
    master_splitter->setStyleSheet("QSplitter::handle{background: black;}");

  QSqlDatabase db = QSqlDatabase::database(file_location);
  QSqlQuery query(QSqlDatabase::database(file_location));

  query.exec("PRAGMA table_info("+table_name+")");

  QList<QString> column_names;
  while(query.next())
  {
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
      column_button->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(column_button, &QPushButton::customContextMenuRequested, this, &TableWidget_SQLITE3::display_ctx_menu_qpushbutton);
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

  this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &TableWidget_SQLITE3::display_ctx_menu_qwidget);

  if (this->write_to_db())
  {
    QWidget *x = new QWidget();
    x->show();
  }
}
/*
QWidget *test = new QWidget();
new QPushButton(QString::number(data_entry->width()), test);
test->show();
*/
void TableWidget_SQLITE3::display_ctx_menu_qwidget(const QPoint &pos)
{
  QMenu contextMenu(tr("Context menu"));

  QAction action1("Remove Data Point");
  contextMenu.addAction(&action1);

   contextMenu.exec(mapToGlobal(pos));
}

void TableWidget_SQLITE3::display_ctx_menu_qpushbutton(const QPoint &)
{

}

bool TableWidget_SQLITE3::write_to_db()
{
  QSqlDatabase db = QSqlDatabase::database(file_location);
  QSqlQuery query(QSqlDatabase::database(file_location));

  

  return true;
}
