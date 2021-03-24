#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"
#include "supported_db/SQLITE3/Overview_SQLITE3.h"
#include "Navigator.h"

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

bool TableWidget_SQLITE3::write_to_db_table(QString path)
{
<<<<<<< HEAD
  QTreeWidgetItem *coresponding_tab_on_treewidget = dynamic_cast<Navigator *>(this->parentWidget()->parentWidget()->parentWidget())->get_selected_tab();
  coresponding_tab_on_treewidget->setText(0,"ajlkfhjaskldjf");
=======
  QList<TreeWidgetItem *> all_tree_widget_tabs = this->parentWidget()->parentWidget()->findChild<QTreeWidget *>()->findChildren<QTreeWidgetItem *>();
  for(TreeWidgetItem *target:all_tree_widget_tabs)
    if(target->data(1,Qt::UserRole)->toString()==QString::fromStdString(this->get()))
    {

    }

>>>>>>> 13d0db21183725a353ad9b3edef7573ac16e3a02
  return true;
  //QTreeWidgetItem *submenu = dynamic_cast<QTreeWidgetItem *>(this->parentWidget()->parentWidget()->findChild<QObject *>(this->objectName()));
  //submenu->setText(0,"winner");
}

bool TableWidget_SQLITE3::write_to_db_all()
{
  Overview_SQLITE3 *overview_tab = dynamic_cast<Overview_SQLITE3 *>(this->parentWidget());
  QList<TableWidget_SQLITE3 *> all_tables = overview_tab->findChildren<TableWidget_SQLITE3 *>();
  overview_tab->write_to_db(all_tables);
}
