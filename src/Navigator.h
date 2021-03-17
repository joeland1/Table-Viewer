#include <QStackedWidget>
#include <QTreeWidget>
#include <QTreeWidget>

class Navigator : public QWidget {

  Q_OBJECT

  public:
    Navigator(QWidget *parent = nullptr);
    QTreeWidget* get_navigator();

  private slots:
    void Add_db_slot_SQLITE();
  private:
    QStackedWidget *table_view_qstackedwidget;
    QTreeWidget *navigator_tree_widget;
};
