#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"
#include "Navigator.h"

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



Navigator::Navigator(QWidget *parent):QWidget(parent)
{
  QHBoxLayout *layout = new QHBoxLayout();

  QTreeWidget *navigator = new QTreeWidget();
    navigator->setFrameShape(QFrame::NoFrame);
    //navigator->setMaximumWidth(100);

  layout->setContentsMargins(0,0,0,0);

  table_view_qstackedwidget = new QStackedWidget;
  QWidget *x = new QWidget;
  QLabel *main_label = new QLabel(x);
  main_label->setText("1");
  table_view_qstackedwidget->addWidget(x);


  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test");
  db.setDatabaseName("lauch.db");

  if(db.open())
  {
    QSqlQuery query(QSqlDatabase::database("test"));
    query.exec("SELECT name FROM sqlite_master WHERE type = 'table'");

    QTreeWidgetItem *header = new QTreeWidgetItem();
      header->setText(0, "databse name:connection type");

    while(query.next())
    {
      QTreeWidgetItem *sub = new QTreeWidgetItem;
      QString name = query.value(0).toString();
      sub->setText(0, name);
      header->addChild(sub);
      TableWidget_SQLITE3 *table_layout = new TableWidget_SQLITE3(name);
      table_layout->setObjectName(QString::fromStdString(table_layout->get()));
      sub->setData(0,Qt::UserRole,QString::fromStdString(table_layout->get()));
      table_view_qstackedwidget->addWidget(table_layout);
    }
    navigator->insertTopLevelItem(0, header);

    connect(navigator, &QTreeWidget::itemClicked,this, [this](QTreeWidgetItem *item, int column){
      TableWidget_Master *target_widget = table_view_qstackedwidget->findChild<TableWidget_Master*>(item->data(0,Qt::UserRole).toString());
      table_view_qstackedwidget->setCurrentWidget(target_widget);
    });

    layout->addWidget(navigator);
    layout->addWidget(table_view_qstackedwidget);
    setLayout(layout);
  }
  else
  {
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);
  }

}
