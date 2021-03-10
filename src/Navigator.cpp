#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"
#include "supported_db/SQLITE3/Overview_SQLITE3.h"
#include "Navigator.h"
#include "Welcome.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

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
Navigator::Navigator(QWidget *parent):QWidget(parent)
{
  QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

  navigator = new QTreeWidget();
    navigator->setFrameShape(QFrame::NoFrame);
    navigator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QMenuBar *master_menu = new QMenuBar();
    QMenu *file_menu = master_menu->addMenu("&File");
    QMenu *add_menu = file_menu->addMenu(tr("&New"));

    QAction *add_db_SQLITE = new QAction("&SQLITE...");
      connect(add_db_SQLITE, &QAction::triggered, this, &Navigator::Add_db_slot_SQLITE);
      add_menu->addAction(add_db_SQLITE);

    QAction *remove_db = new QAction("&Remove");
    master_menu->addAction(remove_db);

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
    split->addWidget(navigator);
    split->addWidget(table_view_qstackedwidget);
    layout->addWidget(split);
    layout->setMenuBar(master_menu);
    setLayout(layout);

}

void Navigator::Add_db_slot_SQLITE()
{
  QString filename = QFileDialog::getOpenFileName(this, "Open Document", QDir::rootPath(),"All files (*.*)");

  //connection name is the same as the path
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", filename);
  db.setDatabaseName(filename);

  if(db.open())
  {
    QSqlQuery query(QSqlDatabase::database(filename));
    query.exec("SELECT name FROM sqlite_master WHERE type = 'table'");

    QTreeWidgetItem *header = new QTreeWidgetItem();
      header->setText(0, "databse name:connection type");
      Overview_SQLITE3 *overview_tab = new Overview_SQLITE3();
      table_view_qstackedwidget->addWidget(overview_tab);
      overview_tab->setObjectName(QString::fromStdString(overview_tab->get()));
      header->setData(0,Qt::UserRole,0);
      header->setData(1,Qt::UserRole,QString::fromStdString(overview_tab->get()));

      while(query.next())
      {
        QTreeWidgetItem *sub = new QTreeWidgetItem;
        QString name = query.value(0).toString();
        sub->setText(0, name);
        header->addChild(sub);
        TableWidget_SQLITE3 *table_layout = new TableWidget_SQLITE3(name, filename);
          table_layout->setContentsMargins(0,0,0,0);
        table_layout->setObjectName(QString::fromStdString(table_layout->get()));
        sub->setData(0,Qt::UserRole,1);
        sub->setData(1,Qt::UserRole,QString::fromStdString(table_layout->get()));
        table_view_qstackedwidget->addWidget(table_layout);
      }
      navigator->insertTopLevelItem(0, header);

      connect(navigator, &QTreeWidget::itemClicked,this, [this](QTreeWidgetItem *item, int column){
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
