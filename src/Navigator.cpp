#include "launch_menu.h"
#include "TableWidget.h"

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

  QTreeWidget *top = new QTreeWidget();
    top->setFrameShape(QFrame::NoFrame);
    //navigator->setMaximumWidth(100);

  layout->setContentsMargins(0,0,0,0);
<<<<<<< HEAD:src/launch_menu.cpp

  table_view_qstackedwidget = new QStackedWidget;
  QWidget *x = new QWidget;
  QLabel *main_label = new QLabel(x);
  main_label->setText("1");
  table_view_qstackedwidget->addWidget(x);

=======
  layout->addWidget(top);
>>>>>>> c184a7e3422e32742169e729cdce349a4c86b757:src/Navigator.cpp

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test");
  db.setDatabaseName("lauch.db");

  if(db.open())
  {
    QSqlQuery query(QSqlDatabase::database("test"));
    query.exec("SELECT name FROM sqlite_master WHERE type = 'table'");

<<<<<<< HEAD:src/launch_menu.cpp
    QTreeWidgetItem *header = new QTreeWidgetItem;
      header->setText(0, "stem");
=======
    QTreeWidgetItem *header = new QTreeWidgetItem();
      header->setText(0, "databse name:connection type");
>>>>>>> c184a7e3422e32742169e729cdce349a4c86b757:src/Navigator.cpp

    while(query.next())
    {
      QTreeWidgetItem *sub = new QTreeWidgetItem;
      QString name = query.value(0).toString();
      sub->setText(0, name);
      header->addChild(sub);
      TableWidget *table_layout = new TableWidget;
      table_layout->setObjectName(name);
      table_view_qstackedwidget->addWidget(table_layout);
    }
<<<<<<< HEAD:src/launch_menu.cpp
    navigator->insertTopLevelItem(0, header);

    connect(navigator, &QTreeWidget::itemClicked,this, [this](QTreeWidgetItem *item, int column){
      TableWidget *target_widget = table_view_qstackedwidget->findChild<TableWidget*>(item->text(0));
      table_view_qstackedwidget->setCurrentWidget(target_widget);
    });

    layout->addWidget(navigator);
    layout->addWidget(table_view_qstackedwidget);
    setLayout(layout);
=======
    top->insertTopLevelItem(0, header);
    layout->addWidget(top);

    db.close()
>>>>>>> c184a7e3422e32742169e729cdce349a4c86b757:src/Navigator.cpp
  }
  else
  {
    QMessageBox::warning(this, tr("Cannot open database"), tr("Please try again."), QMessageBox::Close);
  }

}
