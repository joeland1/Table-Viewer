#include <QWidget>
#include <QStackedWidget>

class Navigator : public QWidget {

  Q_OBJECT

  public:
    Navigator(QWidget *parent = nullptr);

  private slots:

  private:
      QStackedWidget *table_view_qstackedwidget;
};
