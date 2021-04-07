#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"
#include "supported_db/SQLITE3/Overview_SQLITE3.h"
#include "Navigator.h"
#include "supported_db/master-widget/DataEntry_QLineEdit.h"

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
#include <QLabel>

#include <QTreeWidget>
#include <QTreeWidgetItem>
TableWidget_SQLITE3::TableWidget_SQLITE3(QString table_name,QString db_path, QWidget *parent):TableWidget_Master(parent)
{
  this->table_name=table_name;

  master_splitter = new QSplitter();
    master_splitter->setHandleWidth(1);
    master_splitter->setContentsMargins(0,0,0,0);
    master_splitter->setStyleSheet("QSplitter::handle{background: black;}");

  QSqlDatabase db = QSqlDatabase::database(db_path);
  QSqlQuery query(QSqlDatabase::database(db_path));

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
      DataEntry_QLineEdit *data_entry = new DataEntry_QLineEdit(recs.at(j).value(i).toString());
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

}

TableWidget_SQLITE3::~TableWidget_SQLITE3()
{

}
/*
QWidget *test = new QWidget();
new QPushButton(QString::number(data_entry->width()), test);
test->show();
*/
void TableWidget_SQLITE3::display_ctx_menu_qwidget(const QPoint &pos)
{
  QPoint globalPos = this->mapToGlobal(pos);
  QMenu myMenu;
  QAction *save = myMenu.addAction("save");
    connect(save, &QAction::triggered, this, write_to_db_table);
  QAction *save_all = myMenu.addAction("save all");
    connect(save_all, &QAction::triggered, this, write_to_db_all);

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

  QTreeWidgetItem *overview_tab = dynamic_cast<Navigator *>(this->parentWidget()->parentWidget()->parentWidget())->get_selected_tab()->parent();
  Overview_SQLITE3 *overview_widget = dynamic_cast<Overview_SQLITE3 *>(dynamic_cast<Navigator *>(this->parentWidget()->parentWidget()->parentWidget())->get_table_view_qstackedwidget()->findChild<QWidget *>(overview_tab->data(1,Qt::UserRole).toString()));

  QString db_path = overview_widget->get_connection_info();

  {
    bool write_whole_db=false;
    
    QSqlDatabase db = QSqlDatabase::database(db_path);
    QSqlQuery query(QSqlDatabase::database(db_path));

    //select entry, if theres only 1, we can use update
    //int data_entry_count = this->master_splitter->widget(0)->findChild<QVBoxLayout *>()->count()-1;
    QList<QVBoxLayout *> all_vertial_splitters;
    for(int i=0;i<this->master_splitter->count();i++)
      all_vertial_splitters.append(this->master_splitter->widget(i)->findChild<QVBoxLayout *>());

    for(int row=1;row<all_vertial_splitters.at(0)->count();row++)
    {
      QList<DataEntry_QLineEdit *> data_entry;
      QList<QString> column_names;
      for(int column=0;column<all_vertial_splitters.size();column++)
      {
        data_entry.append(dynamic_cast<DataEntry_QLineEdit *>(all_vertial_splitters.at(column)->itemAt(row)->widget()));
        column_names.append(dynamic_cast<QPushButton *>(all_vertial_splitters.at(column)->itemAt(0)->widget())->text());
      }

      bool needs_update = false;
      for(int i=0;i<data_entry.size();i++)
        if(data_entry.at(i)->isUndoAvailable()==true)
          needs_update=true;

      if(needs_update==true)
      {
        //table_name=? and table_name=? ...
        QString table_name_string="";
        //?,? ...
        QString table_name_values="";
        for(int i=0;i<column_names.size();i++)
        {
          table_name_string.append(column_names.at(i)+"=?");
          table_name_values.append("?");
          if(i!=column_names.size()-1)
          {
            table_name_string.append(" and ");
            table_name_values.append(",");
          }
        }
        query.prepare("SELECT COUNT(*) FROM "+this->table_name+" WHERE "+table_name_string);
        for(int i=0;i<column_names.size();i++)
          query.addBindValue(data_entry.at(i)->get_base_text());

        query.exec();
        query.next();
        int amount_of_entries = query.value(0).toInt();
        if(amount_of_entries==1)
        {
          this->parentWidget()->parentWidget()->parentWidget()->setWindowTitle("its 1");
        }
        else
        {
          this->parentWidget()->parentWidget()->parentWidget()->setWindowTitle(QString::number(amount_of_entries));
        }
      }

    }
    //if there are mutliple of the same entry and where cannot be used, update whole table

  }

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
