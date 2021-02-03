#include <QWidget>
#include <QStackedWidget>

class Launch : public QWidget {

  Q_OBJECT

  public:
    Launch(QWidget *parent = nullptr);

  private slots:

  private:
      QStackedWidget *table_view_qstackedwidget;
};
