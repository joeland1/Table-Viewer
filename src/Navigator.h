#include <QStackedWidget>
#include <QTreeWidget>

class Navigator : public QWidget {

  Q_OBJECT

  public:
    Navigator(QWidget *parent = nullptr);

  private slots:
    void Add_db_slot_SQLITE();
  private:
    QStackedWidget *table_view_qstackedwidget;
    QTreeWidget *navigator;
};
