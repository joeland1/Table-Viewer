#include <QStackedWidget>

class Navigator : public QWidget {

  Q_OBJECT

  public:
    Navigator(QWidget *parent = nullptr);

  private slots:
    void Add_db_slot();
  private:
      QStackedWidget *table_view_qstackedwidget;
};
