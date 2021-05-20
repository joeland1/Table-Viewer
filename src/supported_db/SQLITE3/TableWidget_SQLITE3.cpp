#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"
#include "supported_db/SQLITE3/Overview_SQLITE3.h"
#include "Navigator.h"

#include <QLineEdit>
#include <QGridLayout>

//sququery and sqldb should be removed soon
//#include <QSqlQuery>
//#include <QSqlDatabase>
#include <QString>

#include <QMessageBox>
#include <QPushButton>
#include <QList>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QSplitter>

//#include <QSqlRecord>

#include <QAction>
#include <QMenu>
#include <QLabel>

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QtDebug>

#include "libs/SQLITE3/sqlite3.h"
TableWidget_SQLITE3::TableWidget_SQLITE3(QString table_name,QString db_path, QWidget *parent):TableWidget_Master(parent)
{
  this->table_name=table_name;

  this->master_splitter = new QSplitter();
    master_splitter->setHandleWidth(1);
    master_splitter->setContentsMargins(0,0,0,0);
    master_splitter->setStyleSheet("QSplitter::handle{background: black;}");

  //QSqlDatabase db = QSqlDatabase::database(db_path);
  //QSqlQuery query(QSqlDatabase::database(db_path));

  sqlite3 *db;        // database connection
  int rc;             // return code
  char *errmsg;       // pointer to an error string
  sqlite3_stmt *stmt;

  rc = sqlite3_open(db_path.toStdString().c_str(), &db);

  sqlite3_prepare_v3(db, ("PRAGMA table_info("+table_name.toStdString()+")").c_str(), -1, 0, &stmt, NULL);
  //free(query);

  //query.exec("PRAGMA table_info("+table_name+")");

  QList<QString> column_names;
  while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
  {
    column_names.append(QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))));
  }
  sqlite3_finalize(stmt);

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
  //query.exec(db_statement);

  sqlite3_prepare_v3(db, db_statement.toStdString().c_str(), -1, 0, &stmt, NULL);

  //QList<QSqlRecord> recs;
  //while(query.next())
    //recs.append(query.record());

  //first list is the  row, second list is the entries in that row
  QList<QVBoxLayout *> all_columns;
  for(int i=0;i<column_names.size();i++)
  {
    QVBoxLayout *column_layout = new QVBoxLayout();
      column_layout->setAlignment(Qt::AlignTop);
      column_layout->setContentsMargins(0,0,0,0);
      column_layout->setSpacing(0);
    all_columns.append(column_layout);

    QPushButton *column_button = new QPushButton(column_names.at(i));
      column_button->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(column_button, &QPushButton::customContextMenuRequested, this, &TableWidget_SQLITE3::display_ctx_menu_qpushbutton);
      column_button->setStyleSheet("border: 1px solid black;\
        padding-right: 1px;\
        padding-left: 1px;\
        border-right-width: 0px;\
        border-left-width: 0px");
    column_layout->addWidget(column_button);

    QWidget *column_widget = new QWidget();
      column_widget->setLayout(column_layout);
      column_widget->setContentsMargins(0,0,0,0);
    this->master_splitter->addWidget(column_widget);
  }

  while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
  {
    for(int i=0;i<column_names.size();i++)
    {
      QLineEdit *data_entry = new QLineEdit(QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
      all_columns.at(i)->addWidget(data_entry);
    }
  }

  QVBoxLayout *makebig = new QVBoxLayout();
    makebig->addWidget(master_splitter);
    makebig->setContentsMargins(0,0,0,0);
  setLayout(makebig);

  this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &TableWidget_SQLITE3::display_ctx_menu_qwidget);

  sqlite3_close(db);
}

TableWidget_SQLITE3::~TableWidget_SQLITE3()
{

}

void TableWidget_SQLITE3::display_ctx_menu_qwidget(const QPoint &pos)
{
  QPoint globalPos = this->mapToGlobal(pos);
  QMenu myMenu;
  QAction *save = myMenu.addAction("save");
    connect(save, &QAction::triggered, this, [this](){
      if(this->write_to_db_table()==true)
        qInfo() << "writing to db succeeded";

    });
  QAction *save_all = myMenu.addAction("save all");
    connect(save_all, &QAction::triggered, this, [this](){
      //put qinfo notification
    });

  myMenu.exec(globalPos);
  //if(action)
  //  action->trigger();
}

void TableWidget_SQLITE3::display_ctx_menu_qpushbutton(const QPoint &pos)
{
  //we keep this blank so that it overrides the qwidget context menu when clicking a pushbutton
}

bool TableWidget_SQLITE3::write_to_db_table()
{
  qInfo("saving table...");
  QTreeWidgetItem *overview_tab = dynamic_cast<Navigator *>(this->parentWidget()->parentWidget()->parentWidget())->get_selected_tab()->parent();
  Overview_SQLITE3 *overview_widget = dynamic_cast<Overview_SQLITE3 *>(dynamic_cast<Navigator *>(this->parentWidget()->parentWidget()->parentWidget())->get_table_view_qstackedwidget()->findChild<QWidget *>(overview_tab->data(1,Qt::UserRole).toString()));

  QString db_path = overview_widget->get_connection_info();

  sqlite3 *db;        // database connection
  int rc;             // return code
  char *errmsg;       // pointer to an error string

  rc = sqlite3_open(db_path.toStdString().c_str(), &db);

  //QSqlDatabase db = QSqlDatabase::database(db_path);
  //QSqlQuery query(QSqlDatabase::database(db_path));

  //select entry, if theres only 1, we can use update
  //int data_entry_count = this->master_splitter->widget(0)->findChild<QVBoxLayout *>()->count()-1;
  QList<QVBoxLayout *> all_vertial_splitters;
  for(int i=0;i<this->master_splitter->count();i++)
    all_vertial_splitters.append(this->master_splitter->widget(i)->findChild<QVBoxLayout *>());

  QList<QString> column_names;
  for(int column=0;column<all_vertial_splitters.size();column++)
    column_names.append(dynamic_cast<QPushButton *>(all_vertial_splitters.at(column)->itemAt(0)->widget())->text());

  //SELECT * FROM ENABLED_STUFF LIMIT 1 OFFSET 1; -> use this to find target info for where, check that data is different to minimize writes
  //query.exec("UPDATE ENABLED_STUFF SET cog_name='limitwork2' OFFSET 1;");
  QString sql_statement="UPDATE "+this->table_name+" SET ";
  for(int ii=0;ii<column_names.size();ii++)
  {
    sql_statement.append(column_names.at(ii)+"=?");
    if(ii!=column_names.size()-1)
      sql_statement.append(", ");
  }
  sql_statement.append(" LIMIT 1 OFFSET ?;");
  qDebug() << sql_statement;

  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v3(db, sql_statement.toStdString().c_str(), -1, 0, &stmt, NULL);
  if (rc == SQLITE_OK)
    qDebug("prepare work");
  else
    qDebug("prepare failed");

  for(int row=1;row<all_vertial_splitters.at(0)->count();row++)
  {
    QList<QString> data_entry_data;
    
    for(int column=0;column<all_vertial_splitters.size();column++)
      data_entry_data.append(dynamic_cast<QLineEdit *>(all_vertial_splitters.at(column)->itemAt(row)->widget())->text());

    for(int entry_index=0;entry_index<data_entry_data.size();entry_index++)
    {
      std::string s = data_entry_data.at(entry_index).toStdString();
      if(sqlite3_bind_text(stmt, entry_index+1,s.c_str(), -1, SQLITE_TRANSIENT) == SQLITE_OK)
        qDebug("binding succeded");
      else
        qDebug("binding failed");
      qDebug() << "bound"<< data_entry_data.at(entry_index) << "at index" << entry_index+1;
    }
    sqlite3_bind_int(stmt, data_entry_data.size()+1, data_entry_data.size());

    if (sqlite3_step(stmt) == SQLITE_DONE)
      qDebug("success");
    else
      qDebug(sqlite3_errmsg(db));

    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);  
  return true;
}

bool TableWidget_SQLITE3::write_to_db_all()
{
  QList<QWidget *> all_tables;
  QTreeWidgetItem *corresponding_tab_on_treewidget = dynamic_cast<Navigator *>(this->parentWidget()->parentWidget()->parentWidget())->get_selected_tab()->parent();
  for(int i=0;i<corresponding_tab_on_treewidget->childCount();i++)
    all_tables.append(dynamic_cast<Navigator *>(this->parentWidget()->parentWidget()->parentWidget())->get_table_view_qstackedwidget()->findChild<QWidget *>(corresponding_tab_on_treewidget->child(i)->data(1,Qt::UserRole).toString()));

  QTreeWidgetItem *overview_tab = dynamic_cast<Navigator *>(this->parentWidget()->parentWidget()->parentWidget())->get_selected_tab()->parent();
  Overview_SQLITE3 *overview_widget = dynamic_cast<Overview_SQLITE3 *>(dynamic_cast<Navigator *>(this->parentWidget()->parentWidget()->parentWidget())->get_table_view_qstackedwidget()->findChild<QWidget *>(overview_tab->data(1,Qt::UserRole).toString()));
  overview_widget->write_to_db(all_tables);

  return true;
}
