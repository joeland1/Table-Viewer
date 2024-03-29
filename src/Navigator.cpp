#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"
#include "supported_db/SQLITE3/Overview_SQLITE3.h"
#include "Navigator.h"
#include "Welcome.h"

#include <QHBoxLayout>
#include <QWidget>
//#include <QSqlDatabase>
//#include <QSqlQuery>

#include <QMessageBox>

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QLineEdit>
#include <QStackedWidget>

#include <QLabel>

#include <typeinfo>

#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QSplitter>
#include <QFileDialog>

#include "libs/SQLITE3/sqlite3.h"
Navigator::Navigator(QWidget *parent):QWidget(parent)
{
  qInfo("Application Launched");
  QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

  navigator_tree_widget = new QTreeWidget();
    navigator_tree_widget->setFrameShape(QFrame::NoFrame);
    navigator_tree_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(navigator_tree_widget, &QTreeWidget::itemClicked,this, [this](QTreeWidgetItem *item, int column)
    {
      this->selected_tab = item;
    });

  QMenuBar *master_menu = new QMenuBar();
    QMenu *file_menu = master_menu->addMenu("&File");
    QMenu *add_menu = file_menu->addMenu(tr("&New"));

    QAction *add_db_SQLITE = new QAction("&SQLITE3...");
      connect(add_db_SQLITE, &QAction::triggered, this, &Navigator::Add_db_slot_SQLITE);
      add_menu->addAction(add_db_SQLITE);

  table_view_qstackedwidget = new QStackedWidget;
  table_view_qstackedwidget->addWidget(new Welcome);
    table_view_qstackedwidget->setContentsMargins(0,0,0,0);

    /*layout->addWidget(navigator);
    layout->addWidget(table_view_qstackedwidget);
    layout->setMenuBar(fileMenu);
    setLayout(layout);*/

    QSplitter *split = new QSplitter();
      split->setHandleWidth(1);
      split->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      split->setStyleSheet("QSplitter::handle{background: black;}");
    split->addWidget(navigator_tree_widget);
    split->addWidget(table_view_qstackedwidget);
    layout->addWidget(split);
    layout->setMenuBar(master_menu);
    setLayout(layout);
}

void Navigator::Add_db_slot_SQLITE()
{
  qInfo("added SQLITE file");
  QString filename = QFileDialog::getOpenFileName(this, "Open Document", QDir::rootPath(),"All files (*.*)");

  //connection name is the same as the path
  //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", filename);
  //db.setDatabaseName(filename);

  if(true)//change this later to a check
  {
    //QSqlQuery query(QSqlDatabase::database(filename));
    //query.exec("SELECT name FROM sqlite_master WHERE type = 'table'");

    sqlite3 *db;        // database connection
    int rc;             // return code
    char *errmsg;       // pointer to an error string
    char *query = NULL;
    sqlite3_stmt *stmt;

    rc = sqlite3_open(filename.toStdString().c_str(), &db);

    sqlite3_prepare_v3(db, ("SELECT name FROM sqlite_master WHERE type='table';"), -1, 0, &stmt, NULL);
    //free(query);

    QTreeWidgetItem *header = new QTreeWidgetItem();
      header->setText(0, "databse name:connection type");
    Overview_SQLITE3 *overview_tab = new Overview_SQLITE3(filename, this);
      table_view_qstackedwidget->addWidget(overview_tab);
      overview_tab->setObjectName(QString::fromStdString(overview_tab->get()));

      // 0  caterogry is used for type identification
      //1 category is used for unique identification
    header->setData(0,Qt::UserRole,0);
    header->setData(1,Qt::UserRole,QString::fromStdString(overview_tab->get()));

    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
      QTreeWidgetItem *sub = new QTreeWidgetItem;
      QString name = QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        sub->setText(0, name);
        header->addChild(sub);
      TableWidget_SQLITE3 *table_layout = new TableWidget_SQLITE3(name, filename, this);
        table_layout->setContentsMargins(0,0,0,0);
        table_layout->setObjectName(QString::fromStdString(table_layout->get()));

        sub->setData(0,Qt::UserRole,1);
        sub->setData(1,Qt::UserRole,QString::fromStdString(table_layout->get()));

      table_view_qstackedwidget->addWidget(table_layout);
    }

    navigator_tree_widget->insertTopLevelItem(0, header);

    connect(navigator_tree_widget, &QTreeWidget::itemClicked,this, [this](QTreeWidgetItem *item, int column){
      int type = item->data(0,Qt::UserRole).toInt();
      if(type==0)
      {
        Overview_Master *target_widget = table_view_qstackedwidget->findChild<Overview_Master*>(item->data(1,Qt::UserRole).toString());
        table_view_qstackedwidget->setCurrentWidget(target_widget);
      }
      else
      {
        TableWidget_Master *target_widget = table_view_qstackedwidget->findChild<TableWidget_Master*>(item->data(1,Qt::UserRole).toString());
        table_view_qstackedwidget->setCurrentWidget(target_widget);
      }
    });
  }

  else
  {
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);
  }
}

QTreeWidget* Navigator::get_navigator()
{
  return this->navigator_tree_widget;
}

QTreeWidgetItem* Navigator::get_selected_tab()
{
  return this->selected_tab;
}

QStackedWidget* Navigator::get_table_view_qstackedwidget()
{
  return this->table_view_qstackedwidget;
}

//found this online
/*QString getStringFromUnsignedChar(const unsigned char *str ){
    QString result = "";
    int lengthOfString = strlen( reinterpret_cast<const char*>(str) );

    // print string in reverse order
    QString s;
    for( int i = 0; i < lengthOfString; i++ ){
        s = QString( "%1" ).arg( str[i], 0, 16 );

        // account for single-digit hex values (always must serialize as two digits)
        if( s.length() == 1 )
            result.append( "0" );

        result.append( s );
    }

    return result;
}*/
